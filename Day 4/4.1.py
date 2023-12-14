f = open("input.txt").read().splitlines()

totalPoints = 0;

for line in f:
    line = line[10:]
    winNums, myNums = line.split(" | ")

    winNums = winNums.split()
    myNums = myNums.split()

    count = 0;
    for winningNum in winNums:
        if winningNum in myNums:
            count += 1
    
    if count != 0:
        totalPoints += 2**(count-1)

print(totalPoints)