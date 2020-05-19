from cs50 import get_string

card = get_string("Input Card Number :")

multi = 0
multi_num = 0
multi_sum = 0
amex = [34,37]
master = [51,52,53,54,55]
n = 0

while (n < len(card)):
  multi = int(card[n])*2
  multi_num = multi // 10 + multi % 10
  multi_sum = multi_sum + multi_num
  n += 2

not_multi = 0
i = 1

while (i < len(card)):
  not_multi = not_multi + int(card[i])
  i += 2

check = multi_sum + not_multi

if check%10 == 0:
    if int(card[0:2]) in amex and len(card) == 15:
        print("AMEX")
    elif int(card[0:2]) in master and len(card) == 16:
        print("MASTERCARD")
    elif int(card[0]) == 4 and (len(card) == 13 or len(card) == 16):
        print("VISA")
    else:
        print("INVALID")
else:
  print("INVALID")