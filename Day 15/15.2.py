from collections import OrderedDict

f = open("input.txt").read().split(",")

def hash(s):
    hash = 0
    for char in s:
        hash += ord(char)
        hash *= 17
        hash %= 256

    return hash

boxes = [OrderedDict() for i in range(256)]

for sequence in f:
    if '-' in sequence:
        label = sequence[:-1]

        box = hash(label)

        if label in boxes[box]:
            boxes[box].pop(label)
    elif '=' in sequence:
        label, focal_len = sequence.split('=')

        box = hash(label)

        boxes[box][label] = int(focal_len)
    else:
        print("huh")


sum = 0
for boxnum, box in enumerate(boxes):
    i = 1
    for label, value in box.items():
        sum += (1+boxnum) * i * value
        i += 1

print(sum)