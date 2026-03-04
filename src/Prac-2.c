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

// strlen이 return 할 때 size_t = unsigned integer로 반환된다.
// 만약 3 - 5 = ?  로 Neg Overflow로 매우 큰 숫자가 나올 것 이다.
// size_t -> int로 바꾸면 해결 가능
// 혹은 -가 아닌 <, > 형식으로 비교하면 false, true로 정상 작동 가능


// case 3
int tadd_ok(int x, int y)
{
    int temp = x + y;
    if(x < 0 && y < 0 && temp >= 0) // Neg Overflow
        return 0;
    if(x > 0 && y > 0 && temp <= 0) // Pos Overflow
        return 0;
    return 1;
}
// TMIN + TMIN = 0, TMAX + TMAX = 0
// 0 + TMIN = TMIN, Max도 마찬가지 이므로 x와 Y가 서로 부호가 다르다면 Overflow x
// Neg, Pos Overflow일 경우 0, Overflow 없이 연산 가능할 경우 1


// case 4
int tadd_ok(int x, int y)
{
    int sum = x + y;
    return (sum - x == y) && (sum - y == x);
}
// 해당 코드는 아예 overflow를 예상하지 않고 코드를 작성하였다.


// case 5
int tsub_ok(int x, int y)
{
    return tadd_ok(x, -y);
}

// TMIN = -2^(w-1)
// TMAX =  2^(w-1) - 1
// y = TMIN일 경우, tsub_ok에서 -y를 만드는 순간 y == TMIN이 깨지게됨
// two's complement에서 -TMIN = TMIN 이기 때문에 단순 변환은 항상 안전하지 않다.
// 기존 작성한 tadd_ok로는 판별이 불가능함으로 새로 작성해야 한다

int tadd_ok(int x, int y)
{
    int sum = x + y;
    return !(((x ^ sum) & (y ^ sum)) >> 31);
}
// x와 y가 덧셈 후 부호가 sum result와 다르다면 overflow
// int는 32bit 이므로 31bit shift 시 sign bit를 검출할 수 있음

