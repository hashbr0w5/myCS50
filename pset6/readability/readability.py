from cs50 import get_string

text = get_string("Text: ")  # get text

letter_count = 0
word_count = 1  # account for the last word which will not be recognized because of ending punctuation
sentence_count = 0

for i in text:  # analyze individual char in text
    if i.isalpha():  # detect letter
        letter_count += 1

    elif i == " ":  # detect word
        word_count += 1

    elif i == "." or i == "!" or i == "?":  # detect sentence
        sentence_count += 1

L = letter_count/word_count * 100  # average number of letters per 100 words
S = sentence_count/word_count * 100  # average number of sentences per 100 words

index = 0.0588 * L - 0.296 * S - 15.8  # Coleman-Liau index

# Print Grade level
if round(index) >= 16:
    print("Grade 16+")

elif round(index) < 1:
    print("Before Grade 1")

else:
    print(f"Grade {round(index)}")