f = open("input.txt").read().split(",")

sum = 0
for sequence in f:
    hash = 0
    for char in sequence:
        hash += ord(char)
        hash *= 17
        hash %= 256

    sum += hash

print(sum)