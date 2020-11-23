count = 0
clocksCorrect = False

while not clocksCorrect:
    count += 1

    if (count % 2 == 1 and 
        count % 3 == 1 and
        count % 5 == 2 and 
        count % 7 == 5 and
        count % 9 == 1 and 
        count % 11 == 6 and 
        count % 13 == 3 and 
        count % 17 == 7): 
        clocksCorrect = True

print(count)

