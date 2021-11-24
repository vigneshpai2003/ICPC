from math import ceil

r, c = input().split(' ')
r, c = int(r), int(c)


def indexToCoord(x):
    return ceil(x / c), (x - 1) % c + 1


def newPosition(_row, _p):
    return indexToCoord(r * (_p - 1) + _row)


def distance(_i, _j):
    return abs(_i - (r+1) / 2) + abs(_j - (c+1) / 2)


p, i, j, s = 0, 0, 0, 0


def findStablePosition(_p):
    stablePos = None
    maxCount = 0

    for row in range(1, r + 1):
        # for every row calculate stable position and number of iterations required

        pos = newPosition(row, _p)
        count = 1

        while True:
            newPos = newPosition(pos[0], _p)

            if newPos == pos:  # if equilibrium is reached
                # if stablePos has been found before and it is not the same as this
                if stablePos and stablePos != newPos:
                    return 0, 0, 0
                else:
                    stablePos = newPos  # if stablePos not found yet

                if count > maxCount:
                    maxCount = count

                break

            pos = (newPos[0], newPos[1])
            count += 1

    return *stablePos, maxCount


for p_ in range(1, c + 1):
    sol = findStablePosition(p_)

    i_, j_, s_ = findStablePosition(p_)
    if distance(i_, j_) < distance(i, j):
        p, i, j, s = p_, i_, j_, s_


print(p, i, j, s)
