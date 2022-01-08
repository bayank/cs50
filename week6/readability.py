from cs50 import get_string
from cs50 import get_float
from cs50 import get_int


def main():
    # Get x text
    text = get_string("Text: ")

    # Call the letter, word, and snetence counter functions and store the result in ints.
    num_letters = letters(text)
    num_words = words(text)
    num_sen = sen(text)

    # print(f"{letters(text)}")
    # print(f"{words(text)}")
    # print(f"{sen(text)}")

    l = (num_letters / num_words) * 100
    s = (num_sen / num_words) * 100

    # formula for the readability index
    # Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text
    index = 0.0588 * l - 0.296 * s - 15.8
    # print(f"l is: {l}", end="\n")
    # print(f"s is: {s}", end="\n")
    # print(f"index is: {index}", end="\n")
    grade = round(index)

    if grade < 1:
        print("Before Grade 1", end="\n")
    elif grade >= 16:
        print("Grade 16+", end="\n")
    else:
        print(f"Grade {grade}", end="\n")


def letters(x):
    count = 0
    # Check if the letter is uppercase
    for i in x:
        if i.isupper():
            count += 1
        # check is the letter is lowercase
        elif i.islower():
            count += 1
     # if not upper or lower, then it must be a special char and worth 0
    return count


def words(x):
    count = 1
    # Check if there is a space
    for i in x:
        if i.isspace():
            count += 1
    return count


def sen(x):
    count = 0

    # Check if the char is .!?
    for i in x:
        if i in ('.', '?', '!'):
            count += 1
    return count


if __name__ == "__main__":
    main()