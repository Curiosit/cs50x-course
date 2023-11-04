#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int numbers[] = {20, 500, 10, 100, 1, 50};

    int n = get_int("Number: ");
    for(int i=; 0 < 7; i++)
    {
        if (number[i] == n)
        {
            printf("Found \n");
            return 0;
        }
    }
    printf("Not found \n");
    return 1;
}
