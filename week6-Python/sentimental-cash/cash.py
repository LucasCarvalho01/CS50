from cs50 import get_float

def main():

    while True:
        value = get_float("Change owed: ")

        if value >= 0:
            break

    value_int = int(value * 100)
    exchange = change(value_int)

    print(exchange)


def change(value):
    coins = {
        "quarters": 0,
        "dimes": 0,
        "nickels": 0,
        "pennies": 0
    }
    total = 0

    while value >= 25:
        value -= 25
        coins["quarters"] += 1

    while value >= 10:
        value -= 10
        coins["dimes"] += 1

    while value >= 5:
        value -= 5
        coins["nickels"] += 1

    while value >= 1:
        value -= 1
        coins["pennies"] += 1

    for coin in coins:
        total += coins[coin]

    return total

if __name__ == "__main__":
    main()
