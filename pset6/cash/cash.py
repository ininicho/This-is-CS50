from cs50 import get_float

q = 25
d = 10
n = 5

change = get_float("Change :")
while (change <= 0):
    change = get_float("Change :")

change = int(100 * change)

total = change // q + (change % q) // d + ((change % q) % d) // n + ((change % q) % d) % n

print(f"{total}")