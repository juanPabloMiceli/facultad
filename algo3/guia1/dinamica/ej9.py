import math

matriz = [
    [-2,-3,3],
    [-5,-10,1],
    [10,30,-5]] 

# matriz = [
#     [-10,5],
#     [-1,5]]

def ej9BT(matriz, i, j):
    # current += matriz[i][j]



    if i >= len(matriz) or j >= len(matriz[0]):
        return math.inf


    if i == len(matriz)-1 and j == len(matriz[0])-1:
        if matriz[i][j] >= 0:
            return 1
        return -matriz[i][j]+1
        # return max(-current+1, 1)

    vidaDerecha = ej9BT(matriz, i, j+1)
    vidaIzquierda = ej9BT(matriz, i+1, j)

    vidaNecesaria = min(vidaDerecha, vidaIzquierda)

    vidaNecesaria -= matriz[i][j]
    vidaNecesaria = max(1, vidaNecesaria)
    return vidaNecesaria
    # if i == len(matriz[0])-1:
    #     return ej9BT(matriz, i, j+1, current)
    
    # if j == len(matriz)-1:
    #     return ej9BT(matriz, i+1, j, current)
        

    # return max(ej9BT(matriz, i+1, j, current), ej9BT(matriz, i, j+1, current)) 



# print(ej9BT(matriz, 0, 0))

matrizPD = [
    [-2,-3,3],
    [-5,-10,1],
    [10,30,-5]] 

memo = [[None for _ in range(len(matrizPD[0]))] for _ in range(len(matrizPD))]
def ej9PD(i, j):
    if i >= len(matrizPD) or j >= len(matrizPD[0]):
        return math.inf

    if i == len(matrizPD)-1 and j == len(matrizPD[0])-1:
        return max(0, -matrizPD[i][j]+1)

    if memo[i][j] == None:
        memo[i][j] = max(min(ej9PD(i, j+1), ej9PD(i+1, j)) - matriz[i][j], 1)

    return memo[i][j]

print(ej9PD(0, 0))