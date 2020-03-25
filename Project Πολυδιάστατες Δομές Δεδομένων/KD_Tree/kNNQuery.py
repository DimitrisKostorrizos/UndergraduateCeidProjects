import math

dimensions = 2
kNNPoints = []
minimumDistance = float('inf')

def euclideanDistance(a, b):
    return math.sqrt(math.pow(a[0] - b[0], 2) + math.pow(a[1] - b[1], 2))


def kNNSearch(node, queryPoint, k):
    reverseSearch(node, queryPoint, k) # We have to choose what this function will return
    # if len(kNNPoints) < k:
    #     print("sorry,not enough points")
    # else:
    #     print("enough points")
    return kNNPoints

def reverseSearch(node, queryPoint, k, depth = 0):
    global minimumDistance
    if node is None:
        return

    distance = euclideanDistance(node.node, queryPoint)
    if len(kNNPoints) < k or distance < minimumDistance:
        if len(kNNPoints) == k:
            kNNPoints.pop(-1)
        kNNPoints.append((node.node, distance)) # Append (node, distance) in this list
        kNNPoints.sort(key = lambda tup: tup[1])
        minimumDistance = kNNPoints[-1][1] # last element distance(furthest distance)
    axis = depth % dimensions
    if queryPoint[axis] < node.node[axis]:
        return reverseSearch(node.leftChild, queryPoint, k, depth + 1), reverseSearch(node.rightChild, queryPoint, k, depth + 1) # Search left sub tree
    else:
        return reverseSearch(node.rightChild, queryPoint, k, depth + 1), reverseSearch(node.leftChild, queryPoint, k, depth + 1)  # Search right sub tree
