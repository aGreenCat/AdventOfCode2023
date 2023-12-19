import re

workflows, ratings = open("input.txt").read().split("\n\n")
workflows = workflows.splitlines()
ratings = ratings.splitlines()

flows = {}

for wf in workflows:
    splitter = wf.index("{")

    name = wf[0:splitter]
    flow = wf[splitter + 1:-1]
    flows[name] = flow.split(",")

# print(flows)

#try returning ranges instead of full counts.
def acceptedCombos(name, mins, maxs):
    if name == "A":
        return (maxs[0]-mins[0]) * (maxs[1]-mins[1]) * (maxs[2]-mins[2]) * (maxs[3]-mins[3])
    if name == "R":
        return 0
    
    # print(name, mins, maxs)
    
    combos = 0
    for rule in flows[name]:
        if ":" in rule:
            cond, next = rule.split(":")

            rating_type, val = re.split("<|>", cond)
            val = int(val)
            rating_type = 'xmas'.index(rating_type)
            
            if ">" in cond:
                tmins = mins[:]
                if tmins[rating_type] < val+1:
                    tmins[rating_type] = val+1

                border = tmins[rating_type]

                print(name, next, tmins, maxs)
                combos += acceptedCombos(next, tmins, maxs[:])

                maxs[rating_type] = border
            elif "<" in cond:
                tmaxs = maxs[:]
                if tmaxs[rating_type] > val:
                    tmaxs[rating_type] = val

                border = tmaxs[rating_type]

                print(name, next, mins, tmaxs)
                combos += acceptedCombos(next, mins[:], tmaxs)

                mins[rating_type] = border
            else:
                print("wtf")
                exit()
        else:
            print(name, rule, mins, maxs)
            combos += acceptedCombos(rule, mins, maxs)

    print(name, combos)
    return combos

ac = acceptedCombos("in", [1, 1, 1, 1], [4001, 4001, 4001, 4001])
print(ac)
#167409079868000
#167474394229030