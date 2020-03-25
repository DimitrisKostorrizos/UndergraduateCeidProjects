def findMax(node,axis):
    maximum = node.node
    searchList = []
    if node.rightChild:
        searchList.append((node.rightChild, axis))
    if node.leftChild:
        searchList.append((node.leftChild,axis))

    while searchList:
        nodes = searchList.pop(0)
        curAxis = nodes[1]
        nodes = nodes[0]
        if nodes.node[axis] > maximum[axis]:
            maximum = nodes.node
        if curAxis == axis:
            if nodes.rightChild:
                searchList.append((nodes.rightChild,not curAxis))
        else:
            if nodes.rightChild:
                searchList.append((nodes.rightChild,not curAxis))
            if nodes.leftChild:
                searchList.append((nodes.leftChild,not curAxis))
    return maximum


def findMin(node, axis):
    minimum = node.node
    searchList = []
    if node.rightChild:
        searchList.append((node.rightChild, axis))
    if node.leftChild:
        searchList.append((node.leftChild, axis))

    while searchList:
        nodes = searchList.pop(0)
        curAxis = nodes[1]
        nodes = nodes[0]
        if nodes.node[axis] < minimum[axis]:
            minimum = nodes.node
        if curAxis == axis:
            if nodes.leftChild:
                searchList.append((nodes.leftChild, not curAxis))
        else:
            if nodes.rightChild:
                searchList.append((nodes.rightChild, not curAxis))
            if nodes.leftChild:
                searchList.append((nodes.leftChild, not curAxis))
    return minimum
