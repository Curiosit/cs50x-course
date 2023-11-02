#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_lowercase_string(string s);
bool check_order(string s);
int main(void)
{
    string lowercase_string;
    do
    {
        lowercase_string = get_string("Input lowercase string: ");
    }
    while (check_lowercase_string(lowercase_string));

    bool check = check_order(lowercase_string);

}

bool check_lowercase_string(string s) {
    int x = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if(islower(s[i])) {

        }
        else{

            x++;
        }
    }
    if(x >0) {
        return true;
    }
    else{
        return false;
    }
}
bool check_order(string s)
{
    int x = 0;
    int len = strlen(s);
    for (int i = 1; i < len; i++)
    {
        if (s[i] == (s[i-1]+1))
        {
            printf("%c \n", s[i]);
        }
        else {
            printf("Not in order %c %c \n", s[i-1], s[i]);
            x++;
        }

    }
    if(x >0) {
        printf("No \n");
        return true;
    }
    else{
        printf("Yes \n");
        return false;
    }
}

