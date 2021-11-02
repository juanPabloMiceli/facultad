'''
a) (n^2)!
'''
import time
from ej2aux import *

global counterMq
counterMq = 0

global counterGary
counterGary = 0

global counterSemiGary
counterSemiGary = 0

global counterVirgolini
counterVirgolini = 0

global counterGoat
counterGoat = 0



def cuadradosMagicos(n, model):
    res = getSquare(n)
    

    if model == "Gary":
        return cuadradosMagicosAuxGary(n, res, 0,0)
    if model == "SemiGary":
        return cuadradosMagicosAuxSemiGary(n, res, 0, 0)
    if model == "Mqueen":
        return cuadradosMagicosAuxMqueen(n, res, 0,0)
    if model == "Virgolini":
        return cuadradosMagicosAuxVirgolini(n, res, 0, 0)
    if model == "Goat":
        return cuadradosMagicosAuxGoat(n, res, 0,0)

    print("La cagaste fiera")
    exit(1)




def cuadradosMagicosAuxGary(n, square, i, j, solutions=0):
    global counterGary
    counterGary += 1
    copySquare = list(map(list, square))

    if i == n and j == 0:
        if esMagico(square):
            printSquare(square)
            print("\n")
            return solutions + 1
        return solutions

    for h in range(1, (n*n)+1):
        if not any(h in row for row in square):
            copySquare[i][j] = h
            solutions = cuadradosMagicosAuxGary(n, copySquare, nextRow(i, j, n), nextCol(j, n), solutions)
            if solutions > 0:
                return solutions
    return solutions

def cuadradosMagicosAuxSemiGary(n, square, i, j, solutions=0):
    global counterSemiGary
    counterSemiGary += 1

    if i == n and j == 0:
        if esMagico(square):
            printSquare(square)
            print("\n")
            return solutions + 1
        return solutions

    for h in range(1, (n*n)+1):
        if not any(h in row for row in square):
            square[i][j] = h
            solutions = cuadradosMagicosAuxGary(n, square, nextRow(i, j, n), nextCol(j, n), solutions)
            square[i][j] = 0
    return solutions

def cuadradosMagicosAuxMqueen(n, square, i, j, solutions = 0):
    global counterMq
    counterMq += 1
    copySquare = list(map(list, square))


    # A podar se ha dicho

    if i > 1 and j == 0:
        sumaMagica = sumaFila(square, 0)
        for k in range(1, i):
            if sumaMagica != sumaFila(square, k):
                return solutions

    if i == (n-1) and j > 0:
        sumaMagica = sumaFila(square, 0)
        if sumaMagica != sumaDiagonal(square, "der"):
            return solutions
        for k in range(0, j):
            if sumaMagica != sumaColumna(square, k):
                return solutions

    if i == n and j == 0:
        sumaMagica = sumaFila(square, 0)
        if sumaMagica != sumaDiagonal(square, "izq"):
            return solutions
        printSquare(square)
        print("\n")
        return solutions + 1

    for h in range(1, (n*n)+1):
        if not any(h in row for row in square):
            copySquare[i][j] = h
            solutions = cuadradosMagicosAuxMqueen(n, copySquare, nextRow(i, j, n), nextCol(j, n), solutions)
            if solutions > 0:
                return solutions

    return solutions



def cuadradosMagicosAuxVirgolini(n, square, i, j, solutions=0):
    global counterVirgolini
    counterVirgolini += 1
    

    #A podar se ha dicho
    #Suma de referencia
    sumaMagica = sumaFila(square, 0)

    #Si termine la fila y alguna suma distinto
    if i > 1 and j == 0:
        for k in range(1, i):
            if sumaMagica != sumaFila(square, k):
                return solutions

    #Si termine la diagonal / la suma da distinto
    if i == (n-1) and j == 1:
        if sumaMagica != sumaDiagonal(square, "der"):
            return solutions

    #Si termine la columna y alguna suma da distinto
    if i == (n-1) and j > 0:
        for k in range(0, j):
            if sumaMagica != sumaColumna(square, k):
                return solutions

    #Si hasta ahora la suma ya supero el numero magico en la fila/col
    for k in range(len(square)):
        if sumaFila(square, k) > sumaMagica:
            return solutions
        if sumaColumna(square, k) > sumaMagica:
            return solutions

    #Si hasta ahora las diagonales ya superaron el numero magico
    if sumaDiagonal(square, "izq") > sumaMagica:
        return solutions
    if sumaDiagonal(square, "der") > sumaMagica:
        return solutions


    if i == n and j == 0:
        #Si la diagonal \ no cumple el numero magico 
        if sumaMagica != sumaDiagonal(square, "izq"):
            return solutions
        printSquare(square)
        print("\n")
        return solutions + 1

    for h in range(1, (n*n)+1):
        if not any(h in row for row in square):
            square[i][j] = h
            solutions = cuadradosMagicosAuxVirgolini(n, square, nextRow(i, j, n), nextCol(j, n), solutions)
            square[i][j] = 0
            if solutions > 0:
                return solutions

    return solutions


def cuadradosMagicosAuxGoat(n, square, i, j, solutions=0):
    global counterGoat
    counterGoat += 1
    copySquare = list(map(list, square))


    #A podar se ha dicho
    #Suma de referencia
    sumaMagica = ((n*n*n)+n)/2

    #Si termine la fila y alguna suma distinto
    if i > 0 and j == 0:
        for k in range(0, i):
            if sumaMagica != sumaFila(square, k):
                return solutions

    #Si termine la diagonal / la suma da distinto
    if i == (n-1) and j == 1:
        if sumaMagica != sumaDiagonal(square, "der"):
            return solutions

    #Si termine la columna y alguna suma da distinto
    if i == (n-1) and j > 0:
        for k in range(0, j):
            if sumaMagica != sumaColumna(square, k):
                return solutions

    #Si hasta ahora la suma ya supero el numero magico en la fila/col
    for k in range(len(square)):
        if sumaFila(square, k) > sumaMagica:
            return solutions
        if sumaColumna(square, k) > sumaMagica:
            return solutions

    #Si hasta ahora las diagonales ya superaron el numero magico
    if sumaDiagonal(square, "izq") > sumaMagica:
        return solutions
    if sumaDiagonal(square, "der") > sumaMagica:
        return solutions


    if i == n and j == 0:
        #Si la diagonal \ no cumple el numero magico 
        if sumaMagica != sumaDiagonal(square, "izq"):
            return solutions
        printSquare(square)
        print("\n")
        # print(solutions+1)
        return solutions + 1

    for h in range(1, (n*n)+1):
        if not any(h in row for row in square):
            copySquare[i][j] = h
            solutions = cuadradosMagicosAuxGoat(n, copySquare, nextRow(i, j, n), nextCol(j, n), solutions)
            if solutions > 0:
                return solutions

    return solutions

n = 4

# print("Method: Goat")
# start = time.time()
# print("Cuadrados magicos: {}".format(cuadradosMagicos(n, "Goat")))
# end = time.time()
# print(f"Total time: {end - start}")
# print(f"Total calls: {counterGoat}")

print("\n\nMethod: Virgolini")
start = time.time()
print("Cuadrados magicos: {}".format(cuadradosMagicos(n, "Virgolini")))
end = time.time()
print(f"Total time: {end - start}")
print(f"Total calls: {counterVirgolini}")

# print("\n\nMethod: Mqueen")
# start = time.time()
# print("Cuadrados magicos: {}".format(cuadradosMagicos(n, "Mqueen")))
# end = time.time()
# print(f"Total time: {end - start}")
# print(f"Total calls: {counterMq}")

# print("\n\nMethod: SemiGary")
# start = time.time()
# print("Cuadrados magicos: {}".format(cuadradosMagicos(n, "SemiGary")))
# end = time.time()
# print(f"Total time: {end - start}")
# print(f"Total calls: {counterGary}")


# print("\n\nMethod: Gary")
# start = time.time()
# print("Cuadrados magicos: {}".format(cuadradosMagicos(n, "Gary")))
# end = time.time()
# print(f"Total time: {end - start}")
# print(f"Total calls: {counterGary}")




''' Fuerza bruta
def cuadradosMagicosAux(n, square, i, j):
    global counter
    copySquare = list(map(list, square))

    if i == n and j == 0:
        if esMagico(square):
            counter += 1
            printSquare(square)
            print("\n")
        return

    for h in range(1, (n*n)+1):
        if not any(h in row for row in square):
            copySquare[i][j] = h
            cuadradosMagicosAux(n, copySquare, nextRow(i, j, n), nextCol(j, n))


1) 
'''