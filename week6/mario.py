from cs50 import get_int

# Validates the input
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# generates the rows
for row in range(height):
    for k in range(height - row - 1):
        print(" ", end="")
    # Generates the number of #'s per row
    for j in range(row + 1):
        print("#", end="")
    print("\n", end="")
