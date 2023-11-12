import cs50


def coleman_liau(letters, words, sentences):
    L = letters * (100 / words)
    S = sentences * (100 / words)
    result = 0.0588 * L - 0.296 * S - 15.8
    return result


def main():
    text_to_check = cs50.get_string("Text: ")

    letters = sum(c.isalpha() for c in text_to_check)
    spaces = sum(c.isspace() for c in text_to_check)
    words = spaces + 1
    sentences = sum((c in [".", "!", "?"]) for c in text_to_check)

    result = coleman_liau(letters, words, sentences)
    grade = round(result, 0)
    if result < 1:
        print("Before Grade 1\n")
    elif result <= 15:
        print(f"Grade {grade}\n")
    else:
        print("Grade 16+\n")
    return


if __name__ == "__main__":
    main()
