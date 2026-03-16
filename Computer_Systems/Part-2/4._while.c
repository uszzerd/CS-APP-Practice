#include <stdio.h>

short loop_wile(short a, short b)
{
    short result = 0;
    while(a > b)
    {
        result += (a * b);
        a--;
    }
    return result;
}

int main()
{
    short a = loop_wile(100,2);
    return 0;
}