def construct_forest(defs):

    def newNode(datum, operator,left, right):
        return [datum, operator, [left], [right]]

    funcs = []
    operators = []
    operands = []
    trees = []

    for item in defs:
        splittedList = item.split("=")
        funcs.append(splittedList[0].strip())
        rhs = splittedList[1].strip()
        if "*" in rhs:
            splittedRHS = rhs.split("*")
            operands.append((splittedRHS[0].strip(), splittedRHS[1].strip()))
            operators.append("*")

        elif "+" in rhs:
            splittedRHS = rhs.split("+")
            operands.append((splittedRHS[0].strip(), splittedRHS[1].strip()))
            operators.append("+")

        elif "-" in rhs:
            splittedRHS = rhs.split("-")
            operands.append((splittedRHS[0].strip(), splittedRHS[1].strip()))
            operators.append("-")

        elif "^" in rhs:
            splittedRHS = rhs.split("^")
            operands.append((splittedRHS[0].strip(), splittedRHS[1].strip()))
            operators.append("^")
        
    for index, kerem in enumerate(operands):
        if "(" not in kerem[0] and "(" not in kerem[1]:
            trees.append(newNode(funcs[index][0], operators[index], operands[index][0], operands[index][1]))
        elif "(" not in kerem[0] and "(" in kerem[1]:
            trees.append(newNode(funcs[index][0], operators[index], operands[index][0], operands[index][1][0]))
        elif "(" not in kerem[1] and "(" in kerem[0]:
            trees.append(newNode(funcs[index][0], operators[index], operands[index][0][0], operands[index][1]))
        elif "("  in kerem[1] and "(" in kerem[0]:
            trees.append(newNode(funcs[index][0], operators[index], operands[index][0][0], operands[index][1][0]))

    for element in trees:
        if element[2][0].isalpha()  and element[2][0] != "x":
            for i in trees:
                if i[0] == element[2][0]:
                    element[2] = i
                    
     
        if element[3][0].isalpha()  and element[3][0] != "x":
            for i in trees:
                if i[0] == element[3][0]:
                    element[3] = i

        if element[2][0].isalpha()  and element[2][0] != "x" and element[3][0].isalpha()  and element[3][0] != "x":

            for i in trees:
                if i[0] == element[2][0]:
                    element[2] = i
                if i[0] == element[3][0]:
                    element[3] = i

    copyofTrees = trees.copy()
    
    for element in trees:
        if element[2][0].isalpha()  and element[2][0] != "x":
            for i in trees:
                if i[0] == element[2][0]:
                    if i in copyofTrees:
                        copyofTrees.remove(i)
                    
     
        if element[3][0].isalpha()  and element[3][0] != "x":
            for i in trees:
                if i[0] == element[3][0]:
                    if i in copyofTrees:
                        copyofTrees.remove(i)
    
            
    return copyofTrees
    

#input1 = eval(input())
#print(construct_forest(input1))
