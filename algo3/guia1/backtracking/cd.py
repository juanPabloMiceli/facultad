
global calls
calls = 0


def best(n1, n2):
    if n1 < 0 and n2 < 0:
        return -1
    if n1 < 0:
        return n2
    if n2 < 0:
        return n1
    return min(n1, n2)

def CDAux(songs, k, i):
    global calls
    calls += 1
    if k < 0:
        return k
    if i == (len(songs)):
        return k
    return best(CDAux(songs, k-songs[i], i+1), CDAux(songs, k, i+1))

def CD(songs, k):
    winner = CDAux(songs, k, 0)
    return k - winner


songs = [2, 3, 5, 2, 35, 3,2,1,5,6,7,1,2,44]
k = 15

print(CD(songs, k))
print(f"Calls: {calls}")