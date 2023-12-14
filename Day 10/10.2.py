grid = open("input.txt").read().splitlines()
display = [[' ' for j in range(140)] for i in range(140)]


# Specific to test-input
start = (92, 43)
display[start[0]][start[1]] = '-'

prev = start
curr = (92, 44)

while curr != start:
    display[curr[0]][curr[1]] = grid[curr[0]][curr[1]]

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

count = 0

for line in display:
    inside = False

    i = 0
    while i < 140:
        ch = line[i]
        
        if ch == ' ':
            if inside:
                count += 1
                # For visualization purposes
                # line[i] = 'O'
        else:
            if ch in '|':
                inside = not inside
            elif ch in 'FL':
                while line[i] not in 'J7':
                    i += 1

                if (ch == 'F' and line[i] == 'J') or (ch == 'L' and line[i] == '7'):
                    inside = not inside
        i += 1



print(count)

# For visualization purposes
# f = open("text.txt", "w")

# f.writelines([''.join(line) + '\n' for line in display])

# f.close()