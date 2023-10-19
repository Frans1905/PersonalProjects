

def parseS(queue):
    
    print("S", end="")
    
    if (queue):
        symbol = queue.pop(0)
    else:
        return (queue, 0)

    retVal = 1
    if (symbol == 'a'):
        
        (queue, retVal) = parseA(queue)
        if (retVal != 0):
            (queue, retVal) = parseB(queue)
    
    elif (symbol == 'b'):
        
        (queue, retVal) = parseB(queue)
        if (retVal != 0):
            (queue, retVal) = parseA(queue)

    else:
        return (queue, 0)

    if (queue):
        return (queue, 0)
    else:
        return (queue, retVal)

def parseA(queue):

    print("A", end="")
    
    if (queue):
        symbol = queue.pop(0)
    else:
        return (queue, 0)
    
    retVal = 1
    if (symbol == 'b'):

        (queue, retVal) = parseC(queue)
        return (queue, retVal)

    elif(symbol == 'a'):
        
        return (queue, retVal)
    
    else:
        return (queue, 0)

def parseB(queue):
    
    print("B", end="")
    
    if (queue):
        symbol = queue[0]
    else:
        return (queue, 1)

    retVal = 1
    if (symbol == 'c'):
        queue.pop(0)
        
        if (queue):
            symbol = queue.pop(0)
        else:
            return (queue, 0)
        if (symbol != 'c'):
            return (queue, 0)
        
        (queue, retVal) = parseS(queue)

        if (queue):
            symbol = queue.pop(0)
        else:
            return (queue, 0)
        if (symbol != 'b'):
            return (queue, 0)

        if (queue):
            symbol = queue.pop(0)
        else:
            return (queue, 0)
        if (symbol != 'c'):
            return (queue, 0)

    

    return (queue, 1)

def parseC(queue):

    print("C", end="")
    
    retVal = 1

    (queue, retVal) = parseA(queue)

    if (retVal == 0):
        return (queue, 0)

    (queue, retVal) = parseA(queue)

    return (queue, retVal)
    

seq = input()

queue = []
for c in seq:
    queue.append(c)

retVal = 1
(queue, retVal) = parseS(queue)
print("")
if (retVal == 0):
    print("NE")
else:
    print("DA")

    
