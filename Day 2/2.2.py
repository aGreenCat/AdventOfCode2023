import re

sum = 0

f = open("input.txt")
data = f.readlines()
for line in data:
    labels, game = line.split(": ")

    id = labels[5:]
    valid = True

    round = re.split(";\s|,\s|\n", game)

    r = 0
    g = 0
    b = 0

    for show in round:
        if show == "":
            continue

        count, color = show.split(" ")
        count = int(count)

       
        if color == "red":
            r = max(r, count)
        if color == "green":
            g = max(g, count)
        if color == "blue":
            b = max(b, count)

    sum += r * g * b

print(sum)

         

        