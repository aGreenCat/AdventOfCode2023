f = open("input.txt").read().splitlines()

cards = [1 for i in range(len(f))]

for i in range(len(f)):
    line = f[i][10:]
    winNums, myNums = line.split(" | ")

    winNums = winNums.split()
    myNums = myNums.split()

    wins = 0;
    for winningNum in winNums:
        if winningNum in myNums:
            wins += 1

    for j in range(wins):
        cards[i+j+1] += cards[i]

print(sum(cards))
    
    

