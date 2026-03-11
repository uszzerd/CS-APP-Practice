/* ============================================
 * Problem 1: Login Bypass (Buffer Overflow)
 * 
 * 컴파일: gcc -O1 -fno-stack-protector -no-pie -o prob1 prob1_login.c
 * 
 * 목표: 올바른 비밀번호를 모르는 상태에서 "Access Granted!" 를 출력시켜라.
 * 힌트: 스택 프레임의 지역 변수 배치를 생각해보자.
 * ============================================ */

#include <stdio.h>
#include <string.h>

void login() {
    int authenticated = 0;
    char password[8];

    printf("Enter password: ");
    gets(password);  /* 위험한 함수! 왜 위험한지 생각해보자 */

    if (authenticated) {
        printf("Access Granted!\n");
    } else {
        printf("Access Denied.\n");
    }
}

int main() {
    login();
    return 0;
}
