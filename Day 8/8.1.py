f = open("input.txt").read().splitlines()
steps = f[0]

adj = {}

for line in f[2:]:
    line = line.split()
    key = line[0]
    left = line[2][1:-1]
    right = line[3][:-1]

    adj[key] = (left, right)

count = 0

curr = "AAA"
index = 0
while curr != "ZZZ":
    i = 0 if steps[index] == 'L' else 1
    curr = adj[curr][i]
    index += 1
    if index >= len(steps):
        index = 0

    count += 1

    print(curr)

print(count)