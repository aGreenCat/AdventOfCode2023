f = open("input.txt").read().splitlines()

sum = 0

for line in f:
    nums = [int(x) for x in line.split()]
    print(nums)
    next = 0

    depth = 0
    while True:
        if depth % 2 ==0: 
            next += nums[0]
        else:
            next -= nums[0]

        diffs = []
        for i in range(len(nums)-1):
            diffs.append(nums[i+1] - nums[i])

        print(diffs)

        done = True
        for diff in diffs:
            if diff != 0:
                done = False
                break
        
        if done:
            break


        
        nums = diffs
        depth += 1

    print(depth, next)
    sum += next

print(sum)