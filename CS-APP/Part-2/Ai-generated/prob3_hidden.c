/* ============================================
 * Problem 3: Hidden Function (Return Address Overwrite)
 * 
 * 컴파일: gcc -O1 -fno-stack-protector -no-pie -o prob3 prob3_hidden.c
 * 
 * 목표: normal_func()만 호출되는 프로그램에서,
 *       secret_func()가 실행되도록 만들어라.
 * 
 * 힌트: 
 *   1) objdump -d prob3 로 secret_func의 주소를 찾아라.
 *   2) normal_func의 스택 프레임 구조를 그려보자.
 *   3) 버퍼로부터 return address까지의 거리를 계산하라.
 * ============================================ */

#include <stdio.h>
#include <string.h>

void secret_func() {
    printf("=== SECRET UNLOCKED ===\n");
    printf("You successfully redirected execution!\n");
}

void normal_func() {
    char buf[16];
    printf("Enter your name: ");
    gets(buf);
    printf("Hello, %s!\n", buf);
}

int main() {
    printf("Welcome to the program.\n");
    normal_func();
    printf("Goodbye.\n");
    return 0;
}
