import re

workflows, ratings = open("input.txt").read().split("\n\n")
workflows = workflows.splitlines()
ratings = ratings.splitlines()

flows = {}

for wf in workflows:
    splitter = wf.index("{")

    name = wf[0:splitter]
    flow = wf[splitter + 1:-1]
    flows[name] = flow


#try returning ranges instead of full counts.
def acceptedCombos(name, mins, maxs):
    if name == "A":
        return [{mins[0]: maxs[0]}, {mins[1]: maxs[1]}, {mins[2]: maxs[2]}, {mins[3]: maxs[3]}]
    if name == "R":
        return None
    
    rules = flows[name].split(",")

    combos = [{}, {}, {}, {}]
    for rule in rules:
        tempmins = mins.copy()
        tempmaxs = maxs.copy()

        acs = None
        
        if ":" in rule:
            cond, next = rule.split(":")

            rate_type, val = re.split("<|>", cond)
            val = int(val)
            rate_type = 'xmas'.index(rate_type)

            if ">" in cond:
                tempmins[rate_type] = max(mins[rate_type], val)
                maxs[rate_type] = tempmins[rate_type]

                acs = acceptedCombos(next, tempmins, tempmaxs)
                
            if "<" in cond:
                tempmaxs[rate_type] = min(maxs[rate_type], val)
                mins[rate_type] = tempmaxs[rate_type]

                acs = acceptedCombos(next, tempmins, tempmaxs)

            if acs is not None:
                i = rate_type
                for mn, mx in acs[i].items():
                    if mn in combos[i]:
                        combos[i][mn] = max(combos[i][mn], mx)
                    else:
                        combos[i][mn] = mx
        else:
            acs = acceptedCombos(rule, tempmins, tempmaxs)

            if acs is not None:
                for i in range(4):
                    for mn, mx in acs[i].items():
                        if mn in combos[i]:
                            combos[i][mn] = max(combos[i][mn], mx)
                        else:
                            combos[i][mn] = mx

        # print(name, mins, maxs)
        # print(name, allcombos)

    # print(name, combos)
    return combos


ac = acceptedCombos("in", [1, 1, 1, 1], [4001, 4001, 4001, 4001])
print(ac)
#167409079868000
#157286093772801000
#1129075869468000   