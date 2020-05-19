from cs50 import get_string

def main():
    text = get_string("Text :")

    letter = count_letters(text)
    word = count_words(text)
    sentence = count_sentences(text)

    av_letterword = letter / word * 100
    av_sentenceword = sentence / word * 100
    index = (0.0588 * av_letterword) - (0.296 * av_sentenceword) - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")

def count_letters(text):
    letter_sum = 0
    n = len(text)

    for i in range(n):
        if (65 <= ord(text[i]) and ord(text[i]) <= 90) or (97 <= ord(text[i]) and ord(text[i]) <= 122):
            letter_sum += 1

    return letter_sum

def count_words(text):
    word_sum = 1
    n = len(text)

    for i in range(n):
        if ord(text[i]) == 32:
            word_sum += 1

    return word_sum

def count_sentences(text):
    sentence_sum = 0
    n = len(text)

    for i in range(n):
        if ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63:
            sentence_sum += 1

    return sentence_sum

main()