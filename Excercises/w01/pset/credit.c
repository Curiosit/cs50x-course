#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
long get_number(void);
void luhn_check(long);

int main(void)
{
    // Get the credit card number
    long n = get_number();

    // check the card
    luhn_check(n);
}

long get_number(void)
{
    long n;
    char str[16];
    int len;
    do
    {
        n = get_long("Number: ");

        snprintf(str, sizeof(str), "%ld", n);

        len = strlen(str);
    }
    while (n < 0);
    return n;
}

void luhn_check(long n)
{

    char arr[16];
    int rc = sprintf(arr, "%ld", n);
    printf("%i ", rc);
    if (rc < 0)
    {
        // error
    }
    int sum = 0;
    int e = 1;
    for (int i = (rc - 1); i >= 0; i--)
    {

        int value;
        value = arr[i] - '0';
        if (e % 2 == 0)
        {
            printf("even! ");
            printf("digit value %i ", value);

            int num = value * 2;
            printf("digit value x2 %i ", num);
            while (num != 0)
            {
                sum += num % 10;
                num = num / 10;
            }
            printf("total sum %i \n", sum);
        }
        else
        {
            printf("odd! ");
            printf("digit value %i ", value);
            sum += value;
            printf("total sum %i \n", sum);
        }
        printf("e %i ", e);
        e++;
        printf("e %i ", e);
        // printf("%i \n", sum);
    }
    printf("%i \n", sum);
    if (sum % 10 == 0)
    {
        printf("yes!");
        int count = 0;
        long m = n;
        while (m != 0)
        {
            m = m / 10;
            count++;
        }
        printf("Num digits %i \n", count);

        int firstTwoDigits = n / pow(10, count - 2);

        printf("First two %i \n", firstTwoDigits);
        if (count == 15)
        {
            switch (firstTwoDigits)
            {
                case 34:
                case 37:
                    printf("AMEX\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            }
        }
        else if (count == 16)
        {
            switch (firstTwoDigits)
            {
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    printf("MASTERCARD\n");
                    break;
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                    printf("VISA\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            }
        }
        else if (count == 13)
        {
            switch (firstTwoDigits)
            {
                case 40:
                case 41:
                case 42:
                case 43:
                case 44:
                case 45:
                case 46:
                case 47:
                case 48:
                case 49:
                    printf("VISA\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    // printf("%i \n", sum);
}
