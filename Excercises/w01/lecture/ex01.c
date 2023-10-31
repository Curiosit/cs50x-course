#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //name
    string name = get_string("What's your name? ");
    //age
    int age = get_int("What's your age? ");
    //phone number
    string phone = get_string("What's your phone number? ");
    printf("Your data: %s, %i years old, phone: %s \n", name, age, phone);
}
