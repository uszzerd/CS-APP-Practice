# CS:APP Chapter 3 — System Hacking 연습문제

> **범위**: CS:APP 3판 Chapter 3 (Machine-Level Representation of Programs)
> **필요 도구**: GCC, GDB, objdump
> **컴파일 환경**: Linux x86-64

---

## 문제 개요

| # | 유형 | 핵심 개념 | 난이도 |
|---|------|-----------|--------|
| 1 | Exploit + 서술 | Stack frame, buffer overflow | ★★☆ |
| 2 | Reverse Engineering | 어셈블리 분석, leaq/imulq/xorq | ★★☆ |
| 3 | Exploit + 서술 | Return address overwrite | ★★★ |

---

## Problem 1: Login Bypass (Buffer Overflow)

**파일**: `prob1_login.c`

```
gcc -O1 -fno-stack-protector -no-pie -o prob1 prob1_login.c
```

### 배경
`gets()` 함수는 입력 길이를 전혀 검사하지 않는다.
CS:APP 3.10.3절에서 다루는 **out-of-bounds memory reference** 의 가장 기본적인 형태이다.

### 과제

**(A) 서술형** — 아래 질문에 답하라:

1. `login()` 함수의 stack frame (스택 프레임)을 그려라.
   `%rsp`, `password[8]`, `authenticated`, saved `%rbp`, return address 의 위치를 표시할 것.

2. `gets(password)`로 8바이트 이상 입력하면 어떤 일이 발생하는지,
   스택 프레임 그림을 기반으로 설명하라.

3. `gets()` 대신 어떤 함수를 써야 안전한지, 그 이유와 함께 서술하라.

**(B) 실습** — 비밀번호를 모르는 상태에서 "Access Granted!"를 출력시켜라.

**힌트**: `authenticated` 변수가 스택에서 `password` 버퍼와 어떤 상대적 위치에 있는지 GDB로 확인해보자.

```
(gdb) disas login
(gdb) break login
(gdb) run
(gdb) info locals
(gdb) x/32xb $rsp
```

---

## Problem 2: Secret Decoder (Reverse Engineering)

**파일**: `prob2_secret.c`

```
gcc -O1 -S -o prob2_secret.s prob2_secret.c
gcc -O1 -o prob2 prob2_secret.c
```

### 배경
CS:APP 3.5절의 arithmetic operations과 3.6절의 conditional operations을
실제 역산(reverse calculation)에 활용하는 문제이다.

### 과제

**(A) 어셈블리 분석** — `gcc -O1 -S`로 생성된 `check_secret` 함수의 어셈블리를 읽고:

1. 각 명령어가 C 코드의 어떤 연산에 대응하는지 주석을 달아라.
   특히 `leaq`, `imulq`, `xorq`, `cmpq` 에 주목할 것.

2. 컴파일러가 `x * 7`을 어떻게 최적화했는지 설명하라.
   (힌트: `leaq`의 scaled-index addressing mode를 떠올려보자)

**(B) 역산** — "Correct!"를 출력하는 입력값 `x`를 수학적으로 구하라.

변환 과정을 역순으로 추적하면 된다:

```
c == 0x1C4  이므로
b ^ 0xFF == 0x1C4  →  b = ?
a + 13 == b        →  a = ?
x * 7 == a         →  x = ?
```

**(C) 검증** — GDB에서 `check_secret`에 breakpoint를 걸고,
레지스터 값이 (B)의 계산 과정과 일치하는지 확인하라.

```
(gdb) break check_secret
(gdb) run
(gdb) stepi
(gdb) info registers
```

---

## Problem 3: Hidden Function (Return Address Overwrite)

**파일**: `prob3_hidden.c`

```
gcc -O1 -fno-stack-protector -no-pie -o prob3 prob3_hidden.c
```

### 배경
CS:APP 3.10.4절의 핵심 — **return address (반환 주소)**를 덮어써서
프로그램의 control flow (제어 흐름)를 바꾸는 공격이다.
`call`과 `ret` 명령어의 동작 원리를 정확히 이해해야 풀 수 있다.

### 과제

**(A) 정보 수집**

1. `objdump -d prob3 | grep secret_func` 으로 `secret_func`의 시작 주소를 찾아라.

2. `normal_func`를 disassemble하여 스택 프레임 구조를 파악하라:
   - `buf[16]`이 `%rsp`로부터 몇 바이트 떨어져 있는가?
   - saved `%rbp`는 어디에 있는가?
   - return address는 어디에 있는가?

3. `buf`의 시작부터 return address까지의 **offset (오프셋)**을 계산하라.

**(B) 서술형**

1. `ret` 명령어가 실행될 때 CPU가 하는 일을 정확히 서술하라.
   (CS:APP 3.7.2절 참고)

2. 왜 `-fno-stack-protector` 플래그가 필요한지 설명하라.
   **stack canary (스택 카나리)**가 무엇이고 어떻게 이 공격을 방어하는지 서술하라.

**(C) Exploit** — `secret_func()`이 실행되도록 입력을 구성하라.

Python을 이용한 payload 전달 방법:

```bash
python3 -c "import sys; sys.stdout.buffer.write(b'A'*OFFSET + ADDRESS_BYTES)" | ./prob3
```

여기서 `OFFSET`과 `ADDRESS_BYTES`는 직접 계산해야 한다.
x86-64는 **little-endian**임을 잊지 말 것!

---

## 풀이 가이드라인

### 필수 GDB 명령어 정리

| 명령어 | 용도 |
|--------|------|
| `disas func` | 함수 디스어셈블 |
| `break *0x주소` | 특정 주소에 breakpoint |
| `x/Nxb $rsp` | 스택 메모리 N바이트 hex 출력 |
| `info registers` | 레지스터 확인 |
| `stepi` | 한 명령어 실행 |
| `print $rsp` | 스택 포인터 값 출력 |
| `x/s $rsp+offset` | 스택의 문자열 확인 |

### 제출 형식

각 문제마다:
1. **분석 과정** — 스택 프레임 그림, 어셈블리 주석 등
2. **풀이** — 계산 과정 또는 exploit payload
3. **검증** — GDB 실행 결과 스크린샷 또는 출력 복사

### 주의사항

- 이 문제들은 **교육 목적**으로만 사용할 것
- 보호 기법을 의도적으로 끈 상태(`-fno-stack-protector`, `-no-pie`)에서만 동작함
- 실제 시스템에서는 ASLR, stack canary, NX bit 등이 이런 공격을 방어함

---

## 참고 자료

- CS:APP 3rd Edition, Section 3.10: Combining Control and Data in Machine-Level Programs
- CS:APP 3rd Edition, Section 3.10.3: Out-of-Bounds Memory References and Buffer Overflow
- CS:APP 3rd Edition, Section 3.10.4: Thwarting Buffer Overflow Attacks
