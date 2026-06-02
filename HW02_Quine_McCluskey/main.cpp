#include <map>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class FileHandler { //FileHandler class 생성
public:
    vector<string> minterms; //minterm 들을 저장하는 벡터
    int num;  //minterm의 수

    //파일로부터 minterm 읽어오기
    vector<string> readMinterms(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file " + filename);
        }
        string line;
        string line_2;
        getline(file, line);
        num = stoi(line);
        while (getline(file, line_2)) {
            if (line_2[0] == 'm') {
                minterms.push_back(line_2.substr(2));
            }
        }
        file.close();
        return minterms;
    }

    //결과값 txt에 저장하기
    void writeResult(const string& filename, const vector<string>& results) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to write to file " + filename);
        }
        for (const auto& result : results) {
            file << result << std::endl;
        }
        file.close();
    }

    int getNum()
    {
        return num;
    }
};

class MintermProcessor {
public:
    vector<string> minterms;  // 원본 민터즈 저장
    vector<string> primeImplicants;  // 프라임 임플리컨트 저장
    map<int, set<string>> groups; // 그룹을 비트수에 따라 저장
    vector<string> minimizedExpression;

    MintermProcessor(const vector<string>& minterms_in)
    {
        minterms = minterms_in;
    }
    // 두 interm 사이에 오직 하나의 bit 만 차이나는지 확인
    int singleBitDifference(const string& a, const string& b) {
        int count = 0, pos = -1;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                count++;
                pos = i;
                if (count > 1) return -1; // 1개 이상의 차이는 거부
            }
        }
        return count == 1 ? pos : -1; // 정확히 1개의 차이만 있어야 함
    }

    // prime implicant 생성 로직
    void generatePrimeImplicants() {
        cout << "Generating prime implicants..." << endl;

        // minterm을 그룹화
        for (const auto& minterm : minterms) { //초기 그룹화->비트수에 따라 그룹핑
            int count = std::count(minterm.begin(), minterm.end(), '0');
            groups[count].insert(minterm);
        }

        bool done = false;
        while (!done) {
            map<int, set<string>> newGroups;
            set<string> used;
            done = true;

            for (auto it = groups.begin(); it != prev(groups.end()); ++it) {
                for (const auto& elem1 : it->second) {
                    for (const auto& elem2 : next(it)->second) {
                        int pos = singleBitDifference(elem1, elem2);
                        if (pos != -1) {
                            done = false;
                            used.insert(elem1);
                            used.insert(elem2);
                            string combined = elem1;
                            combined[pos] = '-';
                            newGroups[it->first].insert(combined);
                        }
                    }
                }
            }

            // 더 이상 결합할 수 없는 요소들을 프라임 임플리컨트로 추가
            for (const auto& group : groups) {
                for (const auto& elem : group.second) {
                    if (used.find(elem) == used.end()) {
                        primeImplicants.push_back(elem);
                    }
                }
            }

            groups = move(newGroups);
        }
    }

    // prime implicant가 민텀을 커버하는지 검사
    bool covers(const string& implicant, const string& minterm) {
        for (int i = 0; i < implicant.size(); i++) {
            if (implicant[i] != '-' && implicant[i] != minterm[i]) {
                return false;
            }
        }
        return true;
    }


    void minimizeFunction() {
        cout << "Minimizing function..." << endl;

        // 각 민텀을 포함하는 프라임 임플리컨트의 집합을 저장하는 맵
        map<string, set<string>> coverageMap;

        // 프라임 임플리컨트 추출
        for (const auto& implicant : primeImplicants) {
            for (const auto& minterm : minterms) {
                if (covers(implicant, minterm)) {
                    coverageMap[minterm].insert(implicant);
                }
            }
        }

        // 모든 민텀을 커버하는 필수 프라임 임플리컨트 선택
        set<string> essentialImplicants;
        for (const auto& pair : coverageMap) {
            if (pair.second.size() == 1) { // 하나의 프라임 임플리컨트만이 민텀을 커버하는 경우
                essentialImplicants.insert(*pair.second.begin());
            }
        }

        // 최소화된 표현에 필수 프라임 임플리컨트 추가
        minimizedExpression.assign(essentialImplicants.begin(), essentialImplicants.end());
    }



    // 최소화된 불리언 표현 결과 반환
    const  vector<string>& getMinimizedExpression() {
        return minimizedExpression;
    }

};

int main() {
    FileHandler fileHandler;
    //MintermProcessor* processor; 
    vector<string> minterms;

    try {
        // 파일로부터 minterm 읽어오기
        minterms = fileHandler.readMinterms("input_minterm.txt");

        int number_ = fileHandler.getNum();

        // MintermProcessor 클래스 인스턴스 생성
        MintermProcessor processor(minterms);

        // 프라임 임플리컨트 생성
        processor.generatePrimeImplicants();

        // 함수 최소화
        processor.minimizeFunction();

        // 최소화된 불리언 표현 결과를 얻음
        const vector<string>& minimizedExpression = processor.getMinimizedExpression();

        // 최소화된 표현을 출력
        /*cout << "Minimized Expression:" << endl;
        for (const auto& term : minimizedExpression) {
            cout << term << endl;
        }*/

        fileHandler.writeResult("result.txt", minimizedExpression);

        return 0;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;  // 오류가 발생했을 경우 1을 반환합니다.
    }

    //delete processor;
    return 0;
}