from cs50 import get_float
import sys

while True:  # get change amount
    change = get_float("Change owed: ")
    change = int(change * 100)  # convert to cents

    if change >= 0:  # positive value received
        break

coins_val = [25, 10, 5, 1]  # coin values
total_coins = 0  # total number of coins used in change

for i in range(5):  # greedy algorithm

    if change == 0:  # change amount has been paid
        print(total_coins)  # print number of coins used
        sys.exit()

    num_coins = int(change / coins_val[i])  # check how many of the current coin [i] fits into change
    total_coins += num_coins  # update total coins use
    change = change - (num_coins * coins_val[i])  # update remaining change value