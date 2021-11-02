import math

global contador
contador = 0

global soluciones
soluciones = 0

def getScore(p1, p2):
    if p1 == 'juampi' and p2 == 'flor':
        return 10
    if p1 == 'juampi' and p2 == 'fandi':
        return 6
    if p1 == 'juampi' and p2 == 'ludmi':
        return 4
    if p1 == 'juampi' and p2 == 'martin':
        return 6
    if p1 == 'juampi' and p2 == 'ger':
        return 5
    if p1 == 'flor' and p2 == 'fandi':
        return 8
    if p1 == 'flor' and p2 == 'ludmi':
        return 7
    if p1 == 'flor' and p2 == 'martin':
        return 6
    if p1 == 'flor' and p2 == 'ger':
        return 5
    if p1 == 'fandi' and p2 == 'ludmi':
        return 4
    if p1 == 'fandi' and p2 == 'martin':
        return 8
    if p1 == 'fandi' and p2 == 'ger':
        return 7
    if p1 == 'ludmi' and p2 == 'martin':
        return 2
    if p1 == 'ludmi' and p2 == 'ger':
        return 8.5
    if p1 == 'martin' and p2 == 'ger':
        return 5
    print(p1, p2)
    print("ERROR")
    exit(1)
    
def getScoreOfTeam(sol, players):
    score = 0

    for i in range(len(players)):
        if sol[i] == 1:
            for j in range(i):
                if sol[j] == 1:
                    score += getScore(players[j], players[i])


    return score

def idealTeamAux(players, teamSize, index, currentSolution, currentWinner, ones):
    global contador
    global soluciones
    contador += 1

    if (len(players) - index) < (teamSize - ones):
        return currentWinner

    
    
    if ones >= teamSize:
        soluciones += 1 
        score = getScoreOfTeam(currentSolution, players)
        if currentWinner < score:
            pass
        return max(currentWinner, score)
    
    if index >= len(players):
        return currentWinner
    
    s1 = idealTeamAux(players, teamSize, index+1, currentSolution, currentWinner, ones)
    currentSolution[index] = 1
    currentWinner = max(currentWinner, s1)
    s2 = idealTeamAux(players, teamSize, index+1, currentSolution, currentWinner, ones+1)
    currentSolution[index] = 0

    return max(currentWinner, max(s1, s2))

def idealTeam(players, teamSize):
    return idealTeamAux(players, teamSize, 0, [0 for x in range(len(players))], -math.inf, 0)


score = idealTeam(['juampi', 'flor', 'fandi', 'ludmi', 'martin', 'ger'], 3)
print(f"Llamados a funcion: {contador}")
print(f"Soluciones visitadas: {soluciones}")
print(f"Puntaje final: {score}")