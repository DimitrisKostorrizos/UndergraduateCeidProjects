from recordtype import recordtype

dimensions = 2
kdNode = recordtype('kdNode', 'node leftChild rightChild') #Struct properties:node(tuple), leftChild, rightChild

def kdTreeBuild(points, depth = 0):
    if not points:
        return None
    axis = depth % dimensions #Switch between coordinates
    points.sort(key = lambda tup: tup[axis]) #Sort base on axis(x or y coordinate)
    median = int(len(points) / 2) #Round up
    root = kdNode(node = points[median], leftChild = kdTreeBuild(points[:median], depth + 1), rightChild = kdTreeBuild(points[median + 1:], depth + 1))
    return root
