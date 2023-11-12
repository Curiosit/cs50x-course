import cs50


def get_sum(n):
    sum = 0
    for digit in str(n):
        sum += int(digit)
    return sum


def luhn_check(number):
    string = str(number)
    reversed = string[::-1]
    odd = 0
    sum_odd = 0
    sum_even = 0
    # print(reversed)
    for char in reversed:
        if odd % 2 == 0:
            sum_even += int(char)
        else:
            temp = 2 * (int(char))
            sum_odd += get_sum(temp)

        odd += 1

    sum = sum_odd + sum_even
    # print (sum)
    rest = sum % 10
    # print(rest)
    if rest == 0:
        return True
    else:
        return False


def main():
    number = cs50.get_int("Number: ")

    digit_length = len(str(number))
    if digit_length not in [13, 15, 16]:
        print("INVALID\n")
        return
    result = luhn_check(number)
    if result == False:
        print("INVALID\n")
        return

    two_digits = int(str(number)[:2])
    one_digit = int(str(number)[:1])
    # print(two_digits)
    # print(one_digit)
    if two_digits in [51, 52, 53, 54, 55]:
        print("MASTERCARD\n")
    elif two_digits in [34, 37]:
        print("AMEX\n")
    elif one_digit == 4:
        print("VISA\n")
    else:
        print("INVALID\n")

    return


if __name__ == "__main__":
    main()
