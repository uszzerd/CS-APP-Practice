#include <stdio.h>

// case 1
float sum_elements(float a[], unsigned length)
{
    int i;
    float result = 0;
    for (i = 0; i<=length-1;i++)
        result += a[i];
    return result;
}
// length는 unsigned 이기에 length - 1 = Neg Overflow가 발생한다.
// 1. i <= length - 1 부분에서 implicit 하게 signed int로 바뀌길 기도하거나
// 2. unsigned 가 아닌 signed로 입력을 받으면 된다.


// case 2
size_t strlen(const char *s);
int strlonger(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}

int main(int argc, char** argv)
{
    char* i = argv[0];
    char* j = argv[1];

    printf("%d\n", strlonger(i,j));
    return 0;
}
// strlen이 return 할 때 size_t = unsigned integer로 반환된다.
// 만약 3 - 5 = ?  로 Neg Overflow로 매우 큰 숫자가 나올 것 이다.
// size_t -> int로 바꾸면 해결 가능
// 혹은 -가 아닌 <, > 형식으로 비교하면 false, true로 정상 작동 가능


