from recordtype import recordtype

topLeft = 201
bottomRight = 102
topRight = 202
bottomLeft = 101
levelList = []


def isLeaf(node):
    if node.TopLeftChild is None and node.TopRightChild is None and node.BottomLeftChild is None and node.BottomRightChild is None:
        return True
    else:
        return False


def relChild(point, relPoint):
    if point[0] <= relPoint.x and point[1] >= relPoint.y:
        return relPoint.TopLeftChild
    elif point[0] >= relPoint.x and point[1] <= relPoint.y:
        return relPoint.BottomRightChild
    elif point[0] > relPoint.x and point[1] > relPoint.y:
        return relPoint.TopRightChild
    elif point[0] < relPoint.x and point[1] < relPoint.y:
        return relPoint.BottomLeftChild


def printTree(node):
    levelList.append([node, 0])
    levels = []
    levels.append([(node.x, node.y), 0])
    level = 0

    while (levelList):

        if levelList[0][0] == 0:
            if level is not levelList[0][1]:
                level += 1
                print(level)
            levelList.remove(levelList[0])
            print("empty")
            continue

        if level is not levelList[0][1]:
            level += 1
            print(level)

        curNode = levelList[0][0]
        levelList.remove(levelList[0])
        position = [curNode.x, curNode.y]

        if isLeaf(curNode):
            print(str(position) + ' ' + str(curNode.points))
            continue

        TopLeftChild = curNode.TopLeftChild
        TopRightChild = curNode.TopRightChild
        BottomRightChild = curNode.BottomRightChild
        BottomLeftChild = curNode.BottomLeftChild

        print(position)

        if TopLeftChild is not None:
            levelList.append([TopLeftChild, level + 1])
            levels.append([(TopLeftChild.x, TopLeftChild.y), level + 1])
        else:
            levelList.append([0, level + 1])
            levels.append([0, level + 1])
        if TopRightChild is not None:
            levelList.append([TopRightChild, level + 1])
            levels.append([(TopRightChild.x, TopRightChild.y), level + 1])
        else:
            levelList.append([0, level + 1])
            levels.append([0, level + 1])
        if BottomRightChild is not None:
            levelList.append([BottomRightChild, level + 1])
            levels.append([(BottomRightChild.x, BottomRightChild.y), level + 1])
        else:
            levelList.append([0, level + 1])
            levels.append([0, level + 1])
        if BottomLeftChild is not None:
            levelList.append([BottomLeftChild, level + 1])
            levels.append([(BottomLeftChild.x, BottomLeftChild.y), level + 1])
        else:
            levelList.append([0, level + 1])
            levels.append([0, level + 1])
    return levels


def deleteChild(father, child):
    if father.TopLeftChild is child:
        father.TopLeftChild = None
    elif father.TopRightChild is child:
        father.TopRightChild = None
    elif father.BottomLeftChild is child:
        father.BottomLeftChild = None
    elif father.BottomRightChild is child:
        father.BottomRightChild = None
    else:
        return False
