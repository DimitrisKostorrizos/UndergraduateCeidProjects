import searchPoint
import medianBuild


def insertNode(root, point):
    searchedNode = searchPoint.kdTreeSearch(root, point, 0)
    if searchedNode['found']:
        print("Node already exists")
        return None
    else:
        depth = searchedNode['depth']
        axis = depth % 2  # 2 cause this tree has 2 dimensions
        node = searchedNode['parentNode']
        if point[axis] < node.node[axis]:
            node.leftChild = medianBuild.kdNode(point, None, None)
        else:
            node.rightChild = medianBuild.kdNode(point, None, None)