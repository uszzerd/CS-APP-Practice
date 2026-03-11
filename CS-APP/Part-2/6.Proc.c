#include <stdio.h>

// callee: x, y 받아서 결과를 포인터로 저장
void compute(int x, int y, int *result) {
    *result = x * y + x;   // 역참조로 값 저장
}

// callee2: 포인터로 값 받아서 2배
int double_val(int *p) {
    return *p * 2;         // 역참조
}

// caller
int main() {
    int a = 5, b = 3;
    int result = 0;

    compute(a, b, &result);      // &result → rdx로 전달
    int final = double_val(&result);  // &result → rdi로 전달

    return final;
}

/*
1. calling convention
2. pointer dereference
3. stack variable address
4. return register
*/