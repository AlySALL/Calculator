#include <stdio.h>
#include <stdlib.h>

int addition(int number1, int number2)
    {
        return number1+number2;
    }
int main()
{
    printf("la somme est : %d\n",addition(1,4));
    return 0;
}