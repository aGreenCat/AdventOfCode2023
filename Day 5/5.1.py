f = open("input.txt").read().splitlines()

seeds = f[0].split(" ")[1:]
seeds2 = [x for x in seeds]

for line in f[3:27]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

temp = seeds2
seeds2 = seeds
seeds = temp

for line in f[29:60]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

temp = seeds2
seeds2 = seeds
seeds = temp

for line in f[62:72]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

temp = seeds2
seeds2 = seeds
seeds = temp

for line in f[74:101]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

temp = seeds2
seeds2 = seeds
seeds = temp

for line in f[103:114]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

temp = seeds2
seeds2 = seeds
seeds = temp

for line in f[116:129]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

temp = seeds2
seeds2 = seeds
seeds = temp

for line in f[131:139]:
    line = line.split(" ")
    if len(line) != 3:
        continue

    for i in range(len(seeds)):
        seed = int(seeds[i])

        if seed < int(line[1]):
            continue

        diff = seed - int(line[1])
        if diff < int(line[2]):
            seeds2[i] = int(line[0]) + diff

print(seeds2)
print(min(seeds2))