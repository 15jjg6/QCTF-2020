import csv

with open('words (1).txt', newline='') as csvfile:
    data = list(csv.reader(csvfile))

data = [x[0] for x in data]


possibleWords = []
for word in data: 
    if len(word) == 5 and word[0] == 's':
        for word2 in data: 
            if len(word2) == 5 and word2[0] == word[1] and word2[2] == 's':
                for word3 in data:
                    if len(word3) == 13 and word3[0] == word[-1] and word3[3] == 't' and word3[6] == 'i':
                        for word4 in data: 
                            if len(word4) == 8 and word4[2] == word2[-1] and word4[5] == word3[4] and word4[-2] == 's' and word4[-1] == 'e':
                                for word5 in data: 
                                    if len(word5) == 9 and word5[0] == word4[0] and word5[1] == 'a':
                                        for word6 in data: 
                                            if len(word6) == 9 and word6[0] == word5[3] and word6[2] == 'r' and word6[5] == word3[7]: 
                                                for word7 in data: 
                                                    if len(word7) == 7 and word7[0] == word5[6] and word7[-2] == word3[-3] and word7[-1] == 't':
                                                        for word8 in data: 
                                                            if len(word8) == 7 and word8[0] == word5[-1] and word8[5] == word3[-1] and word8[6] == 'g': 
                                                                for word9 in data: 
                                                                    if len(word9) == 10 and word9[0] == word5[3] and word9[3] == word6[3] and word9[6] == word7[3] and word9[-2] == word8[3]:
                                                                        print(f"{word}, {word2}, {word3}, {word4}, {word5}, {word6}, {word7}, {word8}, {word9} ")


print("End")
## e, m, s, k, i
##  QFLAG{EMSKI}