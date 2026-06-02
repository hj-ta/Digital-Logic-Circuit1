# Quine-McCluskey Algorithm

디지털논리회로1 2차 과제로 진행한 **Quine-McCluskey 알고리즘 기반 부울 함수 최소화 구현** 이다.

이 프로젝트는 주어진 최소항(minterm)을 입력받아, 항들을 단계적으로 결합하고 Prime Implicant를 생성한 뒤, 각 Prime Implicant가 어떤 minterm을 포함하는지 검사하여 논리식을 간소화하는 과정을 C++로 구현.

---

## 프로젝트 개요

Quine-McCluskey 알고리즘은 부울 함수(Boolean Function)를 체계적으로 최소화하기 위한 표 기반 알고리즘이다.

카르노맵(Karnaugh Map)은 변수가 적을 때 직관적으로 사용할 수 있지만, 변수 개수가 많아질수록 직접 묶음을 찾기 어렵다. 반면 Quine-McCluskey 알고리즘은 minterm을 이진수 형태로 정리하고, 한 비트만 다른 항들을 반복적으로 결합하는 방식으로 동작하기 때문에 프로그램으로 구현하기에 적합하다.

이 프로젝트에서는 다음 흐름을 중심으로 알고리즘을 구현.

1. 입력 파일에서 minterm 목록을 읽음
2. 각 minterm을 비트 개수 기준으로 그룹화
3. 인접한 그룹끼리 비교하여 한 비트만 다른 항을 결합
4. 결합된 위치를 `-`로 표시하여 implicant 생성
5. 더 이상 결합할 수 없을 때까지 반복
6. 남은 항들을 Prime Implicant로 추출
7. Prime Implicant가 어떤 minterm을 cover하는지 검사
8. Essential Prime Implicant를 선택하여 간소화 결과 도출

---

## 알고리즘 핵심 아이디어

### 1. Minterm 그룹화

QM 알고리즘의 첫 단계는 minterm을 이진수로 표현한 뒤, 특정 기준에 따라 그룹으로 나누는 것이다.

예를 들어 다음과 같은 minterm들이 있을 때,

```text
0001
0011
0111
```

각 항의 비트 패턴을 기준으로 그룹화하고, 서로 인접한 그룹끼리 비교 한다.

인접한 그룹만 비교하는 이유는 한 비트만 다른 항끼리만 결합할 수 있기 때문이다. 두 항의 차이가 한 비트를 초과하면 하나의 implicant로 묶을 수 없다.

---

### 2. 한 비트 차이 항 결합

두 minterm이 정확히 한 비트만 다르면, 다른 위치를 `-`로 대체하여 하나의 implicant로 결합한다.

예를 들어,

```text
1001
1011
```

두 항은 세 번째 비트만 다르므로 다음과 같이 결합할 수 있다.

```text
10-1
```

여기서 `-`는 해당 위치가 0이든 1이든 상관없다는 의미입니다. 즉, 하나의 implicant가 여러 minterm을 포함할 수 있게 된다.

---

### 3. Prime Implicant 생성

한 번 결합된 implicant들은 다시 다음 단계의 비교 대상이 된다.

즉, 알고리즘은 한 번의 비교로 끝나지 않고 다음 과정을 반복한다.

```text
minterm 그룹화
→ 한 비트 차이 항 결합
→ 새로운 implicant 생성
→ 다시 그룹화 및 비교
→ 더 이상 결합 불가능한 항 추출
```

이 과정에서 다른 항과 더 이상 결합되지 못한 항은 Prime Implicant로 분류됨.

Prime Implicant는 최종 최소 논리식을 구성할 수 있는 후보 항이다.

---

## 구현 구조

프로그램은 크게 두 가지 역할로 나누어 구성.

### FileHandler

`FileHandler`는 입력과 출력 처리를 담당한다.

주요 역할은 다음과 같습니다.

* 입력 파일에서 bit 수를 읽음
* `m`으로 시작하는 minterm 라인을 파싱
* minterm 목록을 벡터에 저장
* 최종 결과를 파일로 출력

즉, 알고리즘 자체와 파일 입출력 로직을 분리하여 코드 구조를 단순화함.

---

### MintermProcessor

`MintermProcessor`는 QM 알고리즘의 핵심 연산을 담당.

주요 역할은 다음과 같습니다.

* minterm 목록 저장
* 한 비트 차이 여부 검사
* minterm 및 implicant 그룹화
* Prime Implicant 생성
* implicant가 특정 minterm을 cover하는지 검사
* coverage 관계를 기반으로 Essential Prime Implicant 선택
* 최종 간소화 결과 반환

이 클래스는 입력된 minterm을 실제 논리식 최소화 대상으로 처리하는 핵심 모듈 이다.

---

## 주요 함수 설명

### singleBitDifference

두 개의 이진 문자열을 비교하여 정확히 한 비트만 다른지 확인한다.

한 비트만 다르면 해당 위치를 반환하고, 두 비트 이상 다르거나 차이가 없으면 결합할 수 없다고 판단한다.

이 함수는 implicant 결합 가능 여부를 판단하는 핵심 로직이다.

---

### generatePrimeImplicants

Prime Implicant를 생성하는 함수이다.

동작 흐름은 다음과 같다.

1. minterm을 그룹화
2. 인접한 그룹끼리 비교
3. 한 비트만 다른 항을 결합
4. 결합된 항은 사용 처리
5. 결합되지 않은 항은 Prime Implicant 후보로 저장
6. 새로 생성된 그룹을 기준으로 반복

이 과정을 통해 최종적으로 더 이상 결합할 수 없는 Prime Implicant 목록을 얻는다.

---

### covers

하나의 implicant가 특정 minterm을 포함하는지 검사한다.

예를 들어,

```text
Implicant: 10-1
Minterm:   1001
```

`-` 위치는 0과 1을 모두 허용하므로, 위 implicant는 해당 minterm을 cover한다고 판단.

이 함수는 Prime Implicant Chart를 구성하기 위한 기반이 된다.

---

### minimizeFunction

생성된 Prime Implicant들이 어떤 minterm을 cover하는지 검사하고, Essential Prime Implicant를 선택한다.

특정 minterm을 오직 하나의 Prime Implicant만 cover한다면, 해당 Prime Implicant는 반드시 최종 식에 포함되어야 한다.

이 과정을 통해 최종 간소화 결과를 구성한다.

---

## 검증 방식

구현 결과는 두 가지 방식으로 검증함.

### 1. 손계산 가능한 예제 검증

작은 입력에 대해서는 직접 QM 알고리즘을 손으로 수행한 뒤, 프로그램의 출력과 비교.

이 과정을 통해 다음 항목을 확인.

* minterm 그룹화가 올바르게 되는지
* 한 비트 차이 항만 결합되는지
* 결합된 위치가 `-`로 올바르게 표시되는지
* Prime Implicant가 정상적으로 추출되는지
* coverage 관계가 올바르게 계산되는지

---

### 2. 대형 입력 테스트

100비트 길이의 minterm을 다수 입력하여 프로그램이 큰 입력에서도 동작하는지 확인하였다.

이 테스트는 단순한 정답 검증보다는 아래 이유들도 있다.

* 긴 이진 문자열 처리 가능 여부 확인
* 많은 minterm 입력에 대한 처리 흐름 확인
* 알고리즘의 시간 복잡도와 입력 크기의 영향을 체감
* 단순 구현을 넘어 효율성 문제를 고려하는 계기 마련

Quine-McCluskey 알고리즘은 입력 규모가 커질수록 연산량이 빠르게 증가할 수 있기 때문에, 큰 테스트케이스를 통해 알고리즘의 실용적 한계를 확인할 수 있었다.
* 그 외에도 다양한 테스트케이스를 이렵하여 검증해보았다.

---

## 기술적 포인트

이 프로젝트에서 중점적으로 구현한 부분은 다음과 같다.

* C++ 기반 파일 입력 처리
* minterm 문자열 파싱
* bit pattern 기반 그룹화
* 한 비트 차이 검출 로직
* `-`를 활용한 implicant 표현
* 반복적 Prime Implicant 생성
* coverage table 기반 Essential Prime Implicant 선택
* 대형 100-bit minterm 입력 테스트

---

## 한계 및 개선 가능성

현재 구현은 QM 알고리즘의 핵심 흐름인 Prime Implicant 생성과 Essential Prime Implicant 선택에 초점을 두었다.

다만 모든 경우에 대해 완전한 최소 커버를 보장하려면, Essential Prime Implicant만으로 cover되지 않는 minterm에 대한 추가 선택 과정이 필요할 수 있다.

향후 개선한다면 다음 기능을 추가할 수 있다.

* Petrick’s Method 기반 최소 cover 선택
* Boolean 변수 표기 형태로 결과 변환
* 중복 minterm 처리 방식 개선
* 테스트케이스 자동 검증
* 함수 단위 리팩토링
* 실행 시간 측정 및 성능 분석
* 다양한 입력 형식 지원

---

## 정리

이 프로젝트는 단순히 QM 알고리즘을 minterm 입력 처리부터 Prime Implicant 생성, coverage 검사, Essential Prime Implicant 선택까지의 흐름을 직접 구현한 과제이다.

특히 작은 예제에 대한 손계산 검증과 100비트 대형 입력 테스트를 함께 수행하면서, 논리회로 이론과 알고리즘 구현 사이의 연결을 경험할 수 있었다.

---

## Notice

이 저장소는 학습 및 포트폴리오 기록용입니다.

과제 제출 목적으로 코드를 복사하거나 재사용하지 말아 주세요.
