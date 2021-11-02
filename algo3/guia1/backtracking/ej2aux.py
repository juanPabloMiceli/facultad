
def printSquare(square):
    for row in square:
        print(row)

def nextRow(row, col, n):
    if col == n-1:
        return row + 1
    return row

def nextCol(col, n):
    if col == n-1:
        return 0
    return col + 1



def sumaFila(square, fila):
    return sum(square[fila])

def sumaColumna(square, columna):
    res = 0
    for row in square:
        res += row[columna]

    return res

def sumaDiagonal(square, dir):
    res = 0
    if dir == "izq":
        for i in range(len(square)):
            res += square[i][i]
        return res
    
    if dir == "der":
        for i in range(len(square)):
            res += square[i][len(square)-1-i]
        return res

    return -1

def esMagico(square):
    sumaMagica = sumaDiagonal(square, "izq")

    if sumaMagica != sumaDiagonal(square, "der"):
        return False
    
    

    for i in range(len(square)):
        if sumaMagica != sumaFila(square, i):
            return False

        if sumaMagica != sumaColumna(square, i):
            return False

    return True

def getSquare(n):
    res = []
    for i in range(n):
        aux = []
        for j in range(n):
            aux.append(0)
        res.append(aux)
    return res