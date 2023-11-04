#include <cs50.h>
#include <stdio.h>
typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{

    person people[2];

    string name = get_string("Number: ");
    
    people[0].name = "Carter";
    people[0].number = "23545";
    people[1].name = "David";
    people[1].number = "57678678";

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



