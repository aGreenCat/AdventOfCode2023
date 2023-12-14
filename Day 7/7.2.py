from functools import cmp_to_key

f = open("input.txt").read().splitlines()

hands = []

for line in f:
    hand, bid = line.split()
    hands.append((hand, bid))


CARD_ORDER = ['A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J']


def compare(first, second):
    hand1 = first[0]
    hand2 = second[0]

    freq1 = {}
    freq2 = {}

    for char in hand1:
        if char in freq1:
            freq1[char] += 1
        else:
            freq1[char] = 1

    for char in hand2:
        if char in freq2:
            freq2[char] += 1
        else:
            freq2[char] = 1

    joker1 = 0
    if 'J' in freq1:
        joker1 = freq1.pop('J')

    joker2 = 0
    if 'J' in freq2:
        joker2 = freq2.pop('J')

    freq1 = sorted([value for key, value in freq1.items()], reverse=True)
    freq2 = sorted([value for key, value in freq2.items()], reverse=True)
    
    freq1.append(0)
    freq1.append(0)
    freq2.append(0)
    freq2.append(0)

    print(freq1, freq2)

    if freq1[0]+joker1 > freq2[0]+joker2:
        return 1
    elif freq2[0]+joker2 > freq1[0]+joker1:
        return -1
    
    if freq1[1] > freq2[1]:
        return 1
    elif freq2[1] > freq1[1]:
        return -1
    
    for i in range(5):
        if CARD_ORDER.index(hand1[i]) < CARD_ORDER.index(hand2[i]):
            return 1
        elif CARD_ORDER.index(hand2[i]) < CARD_ORDER.index(hand1[i]):
            return -1

    return 0;

hands.sort(key=cmp_to_key(compare))

print(hands)


winnings = 0;
for i, hand in enumerate(hands):
    winnings += (i+1)*int(hand[1])

print(winnings)