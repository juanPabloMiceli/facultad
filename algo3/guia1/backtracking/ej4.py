import math

def getScore(groupsArray, students, groups):
    goal = sum(students)/groups
    # print(f"Goal: {goal}")
    groupsScore = [0 for x in range(groups)]
    for group, force in zip(groupsArray, students):
        if group == -1:
            break
        groupsScore[group] += force
    # print(f"Scores: {groupsScore}")
    result = 0
    for score in groupsScore:
        result += (score-goal)**2
    return result

def availableGroups(k, currentSolution):
    res = []
    groups = len(currentSolution)//k
    groupsCount = [0 for x in range(groups)]

    for group in currentSolution:
        if group == -1:
            break
        groupsCount[group] += 1
    
    for index in range(len(groupsCount)):
        groupCount = groupsCount[index]
        if groupCount < k:
            res.append(index)
    return res

        

def particionarAux(students, k, index, currentSolution, winnerSolution):
    if index == len(students):
        score = getScore(currentSolution, students, len(students)//k)
        if score < winnerSolution:
            print(score)
            print(currentSolution)
        return min(score, winnerSolution)

    for elem in availableGroups(k, currentSolution):
        currentSolution[index] = elem
        score = particionarAux(students, k, index + 1, currentSolution, winnerSolution)
        winnerSolution = min(score, winnerSolution)
        currentSolution[index] = -1
    return winnerSolution


def particionar(students, k):
    return particionarAux(students, k, 0, [-1 for x in range(len(students))], math.inf)

print(particionar([1,2,3,4,5,6,7,8,9,10], 2))
