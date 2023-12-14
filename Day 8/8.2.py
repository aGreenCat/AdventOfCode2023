import math 
f = open("input.txt").read().splitlines()
steps = f[0]

adj = {}

starts = []
loops = []
threads = []

for line in f[2:]:
    line = line.split()
    key = line[0]
    left = line[2][1:-1]
    right = line[3][:-1]

    if key[2] == 'A':
        starts.append(key)
        threads.append(key)

    if key[2] == 'Z':
        print(key)

    adj[key] = (left, right)

count = 0

print(threads)

def checkThreads(threads):
    for thread in threads:
        if thread[2] != 'Z':
            return False
    return True

for thread in threads:
    index = 0
    count = 0
    curr = thread
    while True:
        i = 0 if steps[index] == 'L' else 1
        curr = adj[curr][i]

        index += 1
        count += 1
        if index >= len(steps):
            if curr[2] == 'Z':
                loops.append(count)
                break
            index = 0

print(math.lcm(*loops))