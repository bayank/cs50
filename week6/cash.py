from cs50 import get_float

# Validates the input
while True:
    dollars = get_float("Change owed: ")
    # print(dollars)
    if dollars > 0.0:
        break

# converts the dollars into cents
cents = round(dollars * 100)
cents_left = cents
coins = 0

# determine how many quarters
while cents_left >= 25:
    cents_left -= 25
    coins += 1

# determine how many dimes
while cents_left >= 10:
    cents_left -= 10
    coins += 1

# determine how many nickels
while cents_left >= 5:
    cents_left -= 5
    coins += 1

# determine how many pennies
while cents_left >= 1:
    cents_left -= 1
    coins += 1

# print coins which is the total number
print(coins)
