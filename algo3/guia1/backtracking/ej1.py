'''
a) soluciones candidatas: {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}
b) soluciones validas: {0,1,0},{1,0,1}
c) solucion parcial: {}, {0}, {1}, {0,0}, {0,1}, {1,0},{0,1,0},{1,0,1}

e) Convencidisimo
f) Convencidisimo
g)
'''

global counter

def printWinner(C, s):
    res = "["
    for i in range (len(s)):
        if s[i] == "1":
            res = res + " " +str(C[i]) + ","
    res = res[:-1]
    res += ']'
    print(res)

            

counter = 0
def subset_sum(C, i, k, sums, binNumber, step):

    if k < 0:
        return False
    if k > sums[i]:
        return False
    if i == -1:
        if k == 0:
            res = "{0:b}".format(binNumber)
            zeros = "0"*(len(C)-len(res))
            res = zeros + res
            printWinner(C, res)
            return True
        return False

    return subset_sum(C, i-1, k, sums, binNumber + 2**step, step+1) or subset_sum(C, i-1, k-C[i], sums, binNumber, step+1)


def subset_sum_aux(C, i, k):
    #Esto habria que calcularlo en O(n)
    sums = [6, 18, 24] 
    subset_sum(C, i, k, sums, 0, 0)

C = [6, 12, 6]

subset_sum_aux(C, len(C)-1, 12)
