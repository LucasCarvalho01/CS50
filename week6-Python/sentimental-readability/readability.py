from cs50 import get_string


def main():
    # Getting the text from the user
    text = get_string("Text: ")

    numLetters = letterCounter(text)
    numWords = wordCounter(text)
    numSentences = sentenceCounter(text)

    grade = Coleman_Liau_alg(numLetters, numWords, numSentences)

    # If then else statements to return the grade to the user
    if grade < 1:
        print("Before Grade 1")

    elif grade >= 16:
        print("Grade 16+")

    else:
        print(f"Grade {grade}")


def letterCounter(text_input):
    counter = 0

    for char in text_input:
        # Checking if char is alphabetical, if so, it's a letter
        if char.isalpha():
            counter += 1

    return counter


def wordCounter(text_input):
    counter = 0

    for char in text_input:
        # Checking for spaces in text
        if ord(char) == 32:
            counter += 1

    # Number of words in a text = num of spaces + 1
    return counter + 1


def sentenceCounter(text_input):
    counter = 0

    for char in text_input:
        # Checking if it is a char that ends a sentence
        if char == '.' or char == '!' or char == '?':
            counter += 1

    return counter


def Coleman_Liau_alg(letters, words, sentences):
    # Implemented based on the Coleman-Liau algorithm to determine the reading level of a text
    L = letters / words * 100
    S = sentences / words * 100

    grade = 0.0588 * L - 0.296 * S - 15.8

    return round(grade)


if __name__ == "__main__":
    main()