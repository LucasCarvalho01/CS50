from cs50 import get_int

while True:
    height = get_int("Height: ")

    if height >= 1 and height <= 8:
        break

hashes = 1
for i in range(height, 0, -1):
    print(" " * (i - 1), end="")
    print("#" * hashes, end="")

    print("  ", end="")

    print("#" * hashes)

    hashes += 1