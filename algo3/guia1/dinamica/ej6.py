import math

class custom:
    def __init__(self, target, billetesGastados):
        self.t = target
        self.q = billetesGastados

    def __lt__(self, other):
        if self.t < other.t:
            return True
        if self.t > other.t:
            return False
        if self.q < other.q:
            return True
        return False

    def __str__(self):
        return f"Exceso: {self.t}, Billetes: {self.q}"


def ej6BT(billetes, indice, data):
    if data.t <= 0:
        return custom(-data.t, data.q)
    if indice == len(billetes):
        return custom(math.inf, data.q)
    
    dataSinGastar = ej6BT(billetes, indice+1, data) 
    
    dataGastando = ej6BT(billetes, indice+1, custom(data.t-billetes[indice], data.q+1)) 
    return min(dataSinGastar, dataGastando)

billetes = [3,3,6,10,20,20]
N = len(billetes)
target = 14


#Necesito una matriz donde las filas son el indice y las columnas son el target y la profundidad es la cantidad de billetes
memo = [[custom(None, None) for _ in range(0, target+1)] for _ in range(0, N+1)]


def ej6PD(memo, billetes, indice, data):
    if data.t < 0:
        return custom(-data.t, data.q)

    if indice == len(billetes):
        return custom(math.inf, data.q)
    
    if memo[indice][data.t].t == None:
        memo[indice][data.t] = min(ej6PD(memo, billetes, indice+1, custom(data.t, data.q)), ej6PD(memo, billetes, indice+1, custom(data.t-billetes[indice], data.q+1)))
    return memo[indice][data.t]


res = ej6PD(memo, billetes, 0, custom(target,0))
print(f"PD {res}")
res = ej6BT(billetes, 0, custom(target,0))
print(f"BT {res}")