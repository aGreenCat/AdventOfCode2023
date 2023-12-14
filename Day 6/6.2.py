TOTAL_TIME = 59688274
BEST_DIST = 543102016641022

def findProduct(num):
    return num * (TOTAL_TIME-num)


low = 1
high = TOTAL_TIME//2

mid = (high + low) // 2

while mid != low:
    if findProduct(mid) == BEST_DIST:
        break

    if findProduct(mid) > BEST_DIST:
        high = mid
    else:
        low = mid

    mid = (high + low) // 2

print(mid)

print((TOTAL_TIME//2 - mid) * 2 - (1 - TOTAL_TIME%2))