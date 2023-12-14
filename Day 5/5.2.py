f = open("input.txt").read().splitlines()

seeds = list(map(int, f[0].split(" ")[1::2]))
ranges = list(map(int, f[0].split(" ")[2::2]))

print(seeds)
print(ranges)

for bounds in [(3, 27), (29, 60), (62, 72), (74, 101), (103, 114), (116, 129), (131, 139)]:
    seeds2 = []
    ranges2 = []

    mappings = []
    for line in f[bounds[0]:bounds[1]]:
        line = line.split(" ")
        mappings.append((int(line[0]), int(line[1]), int(line[2])))


    for index, seed in enumerate(seeds):
        seed_range = ranges[index]

        not_added = True

        for mapping in mappings:
            source = mapping[1]
            dest = mapping[0]
            range = mapping[2]

            if seed < source:
                if seed + seed_range > source:
                    seeds.append(seed)
                    ranges.append(source - seed)
                    
                    if seed + seed_range > source + range:
                        #add new seed section and new mapped seed section

                        seeds.append(source+range)
                        ranges.append((seed + seed_range) - (source + range))

                        seeds2.append(dest)
                        ranges2.append(range)
                        
                        not_added = False
                        break
                    else:
                        #add new mapped seed section
                        seeds2.append(dest)
                        ranges2.append((seed+seed_range) - source)

                        not_added = False
                        break
            elif seed < source + range:
                if seed + seed_range > source + range:
                    #add mapped seed section and new seed section
                    seeds.append(source+range)
                    ranges.append((seed + seed_range) - (source + range))
                    
                    diff = seed - source
                    seeds2.append(dest + diff)
                    ranges2.append(source+range-seed)
                    
                    not_added = False
                    break
                else:
                    #add mapped seed section
                    diff = seed - source
                    seeds2.append(dest + diff)
                    ranges2.append(seed_range)
                    
                    not_added = False
                    break
            else:
                continue

        if not_added:
            seeds2.append(seed)
            ranges2.append(seed_range)

    seeds = seeds2
    ranges = ranges2

print(seeds)
print(min(seeds))