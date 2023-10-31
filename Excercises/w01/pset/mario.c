#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_grid(int n);

int main(void)
{
    // Get size of grid
    int n = get_size();

    // Prints grid of bricks
    print_grid(n);
}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
        char str[16]; 
        snprintf(str, sizeof(str), "%d", n);
    }
    while (n < 1 || strlen(str) >= 13);
    return n;
}

void print_grid(int n)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = (n - i); j > 1; j--)
        {
            printf(" ");
        }
        for (int j = 0; j < (i + 1); j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < (i + 1); j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
