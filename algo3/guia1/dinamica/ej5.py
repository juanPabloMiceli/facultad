def ssFB(arr, i, k):
    if k == 0:
        return True
    if k < 0 or i == len(arr):
        return False
    return ssFB(arr, i+1, k) or ssFB(arr, i+1,k-arr[i])


# print(memo)

def printMatriz(arr):
    if len(arr) > 0:
        print("["+str(arr[0]))
        for i in range(1,len(arr)):
            if i < len(arr)-1:
                print(" "+str(arr[i]))
                continue
            else:
                print(" "+str(arr[i])+"]")

    else:
        print("[]")
        return

def ssPD(memo, arr, i, k):
    if k < 0:
        return False
    # print("k: "+str(k)+"i: "+str(i))
    if memo[k][i] == None:
        memo[k][i] = ssPD(memo, arr, i+1, k) or ssPD(memo, arr, i+1, k-arr[i])

    return memo[k][i]


#Fila = k
#Columna = indice
arr = [1,2,3,4,5]
N = len(arr)
for i in range(0,20):    
    memo = [[None for _ in range(0,N+1)] for _ in range(0,i+1)]
    for row in range(len(memo)):
        memo[row][N] = False  #Si llegue al final del array return false
    for col in range(len(memo[0])):
        memo[0][col] = True   #Si k vale cero encontre solucion
    
    # printMatriz(memo)
    print("i: "+str(i)+" "+str(ssPD(memo, arr, 0, i)))