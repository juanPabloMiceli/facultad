import math

class custom:
    
    def __init__(self, res, list):
        self.res = res
        self.list = list
    
    def __bool__(self):
        return self.res == True
    
    def __str__(self):
        return f"{self.list}"

v = [3,1,5,2,1,2]
N = len(v)
target = 400**2

def solveBT(i, w):
    if w > target:
        return custom(False, [])

    if i == N:
        return custom(w == target, [])
        

    c1 = solveBT(i+1, w+v[i])
    if c1:
        c1.list.insert(0, '+')
        return c1
    c2 = solveBT(i+1, w*v[i])
    if c2:
        c2.list.insert(0, '*')
        return c2
    c3 = solveBT(i+1, math.pow(w, v[i])) 
    if c3:
        c3.list.insert(0, '^')
        return c3
    return custom(False, [])


print(solveBT(1, 3))
