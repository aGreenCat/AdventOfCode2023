f = open("input.txt").read().splitlines()

times = f[0].split()[1:]
dists = f[1].split()[1:]


def waysToBeat(time, best_dist):
    count = 0
    num = time//2

    while num * (time-num) > best_dist:
        num -= 1
        count += 1

    return count*2 - (1 - (time%2))



margin = 1

for i in range(4):
    margin *= waysToBeat(int(times[i]), int(dists[i]))

print(margin)