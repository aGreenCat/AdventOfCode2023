grid = open("input.txt").read().splitlines()

start = (92, 43)

#print(grid[start[0]][start[1]])

steps = 1
prev = start
curr = (92, 44)

while curr != start:
    if grid[curr[0]][curr[1]] == '-':
        if prev[1] < curr[1]:
            prev = curr
            curr = (curr[0], curr[1] + 1)
        else:
            prev = curr
            curr = (curr[0], curr[1] - 1)
    elif grid[curr[0]][curr[1]] == '|':
        if prev[0] < curr[0]:
            prev = curr
            curr = (curr[0] + 1, curr[1])
        else:
            prev = curr
            curr = (curr[0] - 1, curr[1])
    elif grid[curr[0]][curr[1]] == 'L':
        if prev[0] == curr[0]:
            prev = curr
            curr = (curr[0] - 1, curr[1])
        else:
            prev = curr
            curr = (curr[0], curr[1] + 1)
    elif grid[curr[0]][curr[1]] == 'J':
        if prev[0] == curr[0]:
            prev = curr
            curr = (curr[0] - 1, curr[1])
        else:
            prev = curr
            curr = (curr[0], curr[1] - 1)
    elif grid[curr[0]][curr[1]] == 'F':
        if prev[0] == curr[0]:
            prev = curr
            curr = (curr[0] + 1, curr[1])
        else:
            prev = curr
            curr = (curr[0], curr[1] + 1)
    elif grid[curr[0]][curr[1]] == '7':
        if prev[0] == curr[0]:
            prev = curr
            curr = (curr[0] + 1, curr[1])
        else:
            prev = curr
            curr = (curr[0], curr[1] - 1)
    elif grid[curr[0]][curr[1]] == '.':
        print("wtf")
        break

    steps += 1

    print(curr)


print(steps//2)