workflows, ratings = open("input.txt").read().split("\n\n")
workflows = workflows.splitlines()
ratings = ratings.splitlines()

flows = {}

for wf in workflows:
    splitter = wf.index("{")

    name = wf[0:splitter]
    flow = wf[splitter + 1:-1]
    flows[name] = flow

total = 0
for rating in ratings:
    scores = [int(x[2:]) for x in rating[1:-1].split(",")]

    count = 0

    curr = "in"
    processing = True
    while processing:
        rules = flows[curr].split(",")

        for rule in rules:
            if ':' in rule:
                rate_type = 'xmas'.index(rule[0])

                splitter = rule.index(":")
                
                condition = False
                if rule[1] == '<':
                    condition = scores[rate_type] < int(rule[2:splitter])
                elif rule[1] == '>':
                    condition = scores[rate_type] > int(rule[2:splitter])

                if condition:
                    next = rule[splitter+1:]

                    if next == "A":
                        total += sum(scores)
                        processing = False
                    elif next == "R":
                        processing = False
                               
                    else:
                        curr = next

                    break          
            else:
                if rule == "A":
                    total += sum(scores)                 
                    processing = False
                    break
                if rule == "R":
                    processing = False
                curr = rule

                break


print(total)