f = open("input.txt").read().splitlines()

cache = {}

# global funcCalls
# funcCalls = 0

# global cacheHits
# cacheHits = 0

def arrange(counts, size, record):
    # global funcCalls
    # funcCalls += 1

    if size <= 0:
        return 0
    if len(counts) <= 0:
        return 0
    
    count = counts[0]

    places = 0
    hasBroken = -1

    for i in range(size - count + 1):
        possible_places = 0

        if hasBroken != -1 and i > hasBroken:
            break

        possible_arrangement = True
        for j in range(count):
            if record[i+j] == '.':
                possible_arrangement = False
                break
            if hasBroken == -1:
                if record[i+j] == '#':
                    hasBroken = i+j
                    
        if possible_arrangement:
            if len(counts) == 1:
                for k in range(size):
                    if record[k] == '#':
                        if k not in range(i, i+count):
                            possible_arrangement = False
                
                if possible_arrangement:
                    possible_places = 1
            else:
                if i + count < size and record[i+count] == '#':
                    possible_arrangement = False

                if possible_arrangement:
                    if record[i+count+1:] in cache and tuple(counts[1:]) in cache[record[i+count+1:]]:
                        possible_places = cache[record[i+count+1:]][tuple(counts[1:])]
                        # global cacheHits
                        # cacheHits += 1
                    else:
                        possible_places = arrange(counts[1:], size-i-count-1, record[i+count+1:])
                
        places += possible_places
    
    if record in cache:
        cache[record][tuple(counts)] = places
    else:
        cache[record] = {tuple(counts): places}

    return places

total_arrangements = 0

for line in f:
    record, counts = line.split(" ")
    record = record + "?" + record + "?" + record + "?" + record + "?" + record
    counts = [int(x) for x in counts.split(",")]
    counts = counts + counts + counts + counts + counts 

    arrangements = arrange(counts, len(record), record)

    total_arrangements += arrangements

print(total_arrangements)

# print("function calls", funcCalls)
# print("cache hits", cacheHits)