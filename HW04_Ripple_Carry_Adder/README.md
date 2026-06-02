# HW04 - 40-bit Ripple Carry Adder

Verilog HDL을 사용하여 40-bit Ripple Carry Adder를 구현한 디지털논리회로1 4차 과제.

## 주요 내용

* Full Adder의 truth table 작성
* Sum과 Carry-out에 대한 Boolean equation 도출
* Full Adder gate-level 회로 분석
* 1-bit Full Adder 모듈 구현
* 40개의 Full Adder를 연결한 Ripple Carry Adder 구조 설계
* 40-bit 입력 `A`, `B`와 `Cin`을 이용한 덧셈 수행
* 최종 합 `S[39:0]` 및 `Cout` 출력
* Testbench를 통한 입력 케이스 검증
* RTL View 및 waveform 기반 동작 확인

## 구현 개요

Ripple Carry Adder는 여러 개의 Full Adder를 직렬로 연결하여 다중 비트 덧셈을 수행하는 구조이다.
각 비트의 Carry-out이 다음 비트의 Carry-in으로 전달되기 때문에, 하위 비트에서 발생한 carry가 상위 비트로 순차적으로 전파된다.

본 과제에서는 Verilog HDL을 사용하여 1-bit Full Adder를 정의하고, 이를 40-bit 구조로 확장하여 큰 이진수 덧셈을 수행하도록 구현하였다.

## 정리

이 과제는 디지털 회로 이론에서 배운 Full Adder 구조를 Verilog 코드로 직접 구현하고, 시뮬레이션과 RTL View를 통해 동작을 확인한 과제.
조합논리회로의 수식, 회로 구조, HDL 구현, 테스트벤치 검증 과정을 연결해서 경험할 수 있었다.