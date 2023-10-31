#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size = 100;
    int end_size = 200;

    do
    {
        start_size = get_int("Starting population: ");
    }
    while (start_size < 9);
    do
    {
        end_size = get_int("Final population: ");
    }
    while (end_size < start_size);

    int current_size = start_size;
    int year = 0;

    while (current_size < end_size)
    {
        int add = current_size / 3;
        int substract = current_size / 4;

        current_size = current_size + add - substract;

        year++;
    }

    printf("Start size: %i \n", start_size);
    printf("End size: %i \n", end_size);
    printf("Years: %i \n", year);
}
