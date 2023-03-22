from cs50 import get_int

while True:  # get height
    height = get_int("Height: ")

    if 1 <= height <= 8:  # meet height requirements
        break

for i in range(1, height + 1, 1):  # create rows in pyramid
    for j in range(height - i):  # draw spaces
        print(" ", end="")

    for j in range(i):  # draw L hashes
        print("#", end="")

    print("  ", end="")

    for j in range(i):  # draw R hashes
        print("#", end="")

    print()