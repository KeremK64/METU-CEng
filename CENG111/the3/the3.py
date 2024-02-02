def strToLst(N):
    res = []
    for i in range(len(N)):
        res.append(list(N[i]))
    return res


def rotate_matrix( m ):
    res = strToLst(m)
    willReturn =[]
    rotated = [[res[j][i] for j in range(len(m))] for i in range(len(m[0])-1,-1,-1)]
    willReturn = [''.join(inner) for inner in rotated]
    return willReturn

def pattern_search(P,I):
    rotated_270 = rotate_matrix(P)
    rotated_180 = rotate_matrix(rotated_270)
    rotated_90 = rotate_matrix(rotated_180)

    lstP = strToLst(P)
    lst90 = strToLst(rotated_90)
    lst180 = strToLst(rotated_180)
    lst270 = strToLst(rotated_270)

    lstlst1 = [lstP,lst180]
    lstlst2 = [lst90,lst270]
    
    for x in range(len(lstlst1)):
        for i in range(0,len(I) - len(P) + 1):
            for j in range(0,len(I[0]) - len(P[0]) + 1):
                count = 0
                for k in range(len(P)):
                    for m in range(len(P[0])):
                        if lstlst1[x][k][m] == I[i+k][j+m]:
                            count+= 1
                            if count == len(P)*len(P[0]):
                                if x == 0:
                                    return (i,j,0)
                                else:
                                    return (i,j,180)
    
    for x in range(len(lstlst2)):
        for i in range(0,len(I) - len(P[0]) + 1 ):
            for j in range(0,len(I[0]) - len(P) + 1):
                count = 0
                for k in range(len(P[0])):
                    for m in range(len(P)):
                        if lstlst2[x][k][m] == I[i+k][j+m]:
                            count+= 1
                            if count == len(P)*len(P[0]):
                                if x == 0:
                                    return (i,j,90)
                                else:
                                    return (i,j,270)

    return False

