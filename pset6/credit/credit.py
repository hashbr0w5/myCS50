from cs50 import get_string

while True:  # get credit card number
    num = get_string("Number: ")
    num_len = len(num)

    card = ["AMEX", "VISA", "MASTERCARD"]
    dig = num[0:2]  # first 2 digits of card

    if num_len == 15:  # check length
        if dig == "34" or dig == "37":  # check digits
            card_type = card[0]  # AMEX
            break

        else:
            print("INVALID")
            sys.exit()

    elif num_len == 13:
        if num[0] == "4":
            card_type = card[1]  # VISA
            break

        else:
            print("INVALID")
            sys.exit()

    elif num_len == 16:
        if dig == "51" or dig == "52" or dig == "53" or dig == "54" or dig == "55":
            card_type = card[2]  # MASTERCARD
            break

        elif num[0] == "4":
            card_type = card[1]  # VISA
            break

        else:
            print("INVALID")
            sys.exit()

    else:  # invalid length
        print("INVALID")
        sys.exit()


num = int(num)

sum1 = 0  # sum of each digit multipled 2
sum2 = 0  # sum of digits

x = True  # switch for sum2 (TRUE means go ahead with sum2 calculations)

for i in range(num_len):

    tmp = num % 10  # grab last digit

    if x is True:  # sum2 calculations
        sum2 = sum2 + tmp
        x = False  # next calculation is for sum1

    else:  # sum1 claculations
        product = tmp * 2  # get product
        product = str(product)  # convert to str

        if len(product) == 2:  # product has 2 digits
            sum1 = sum1 + int(product[0]) + int(product[1])  # add individual digits

        else:  # product has 1 digit
            sum1 = sum1 + int(product)

        x = True  # next calculation is for sum2

    num = int(num / 10)  # chop off last digit

final_sum = sum1 + sum2

if final_sum % 10 == 0:  # last digit of final sum is 0
    print(card_type)  # card passes Luhn's Algorithm

else:
    print("INVALID")