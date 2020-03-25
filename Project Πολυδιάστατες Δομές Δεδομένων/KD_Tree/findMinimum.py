#  Recursively finds minimum of d'th dimension in KD tree
#  The parameter depth is used to determine current axis.

def minNode(node1, node2, node3, axis):
    res = node1
    if node2 is not None and node2.node[axis] < res.node[axis]:
        res = node2
    if node3 is not None and node3.node[axis] < res.node[axis]:
        res = node3
    return res


def findMinimum(node, depth, axis):
    if node is None:
        return None
    currentDepth = depth % 2
    if currentDepth == axis:
        if node['leftChild'] is None:
            return None
        return findMinimum(node['node'].leftChild, depth + 1, axis)

    #  If current dimension is different then minimum can be anywhere
    #  in this subtree

    return minNode(node, findMinimum(node.leftChild, axis, depth + 1),
                   findMinimum(node.rightChild, axis, depth + 1), axis)


def findMin(node, axis):
    return findMinimum(node, axis, 0)
