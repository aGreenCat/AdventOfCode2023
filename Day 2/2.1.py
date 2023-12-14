import re

sum = 0

f = open("input.txt")
data = f.readlines()
for line in data:
    labels, game = line.split(": ")

    id = labels[5:]
    valid = True

    round = re.split(";\s|,\s|\n", game)
    
    for show in round:
        if show == "":
            continue

        count, color = show.split(" ")
        count = int(count)

        if color == "red":
            if count > 12:
                valid = False
                print(show)
        if color == "green":
            if count > 13:
                valid = False
                print(show)
        if color == "blue":
            if count > 14:
                valid = False
                print(show)

    if valid:
        print(id)
        sum += int(id)

print(sum)

         

        