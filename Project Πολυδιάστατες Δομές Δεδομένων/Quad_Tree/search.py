from recordtype import recordtype
import functions
import gatherTreeNodes

list = []
path=[]

qtNode = recordtype('qtNode', 'TopLeftChild TopRightChild BottomLeftChild BottomRightChild points x y')

def search(node,point):
    if node is None:
        return False

    if functions.isLeaf(node) is True:
        if point in node.points:
                return True
        return False
    else:
        return search(functions.relChild(point,node),point)



def stypidQ(root,k,point):
    gatherTreeNodes.gather_tree_nodes(root)
    qList = gatherTreeNodes.general_list
    kList = []
    for qpoint in qList:
        if len(kList < k -1):
            kList.append([point,distance.euclidean(qpoint,point)])
        else:
            kList.sort(key=lambda x: x[1])
            dist = distance.euclidean(qpoint,point)
            if dist < kList(k-1)[1]:
                kList.pop()
                kList.append(qpoint)




def delete(node,point):
    path.append(node)
    if node is None:
        return False

    if functions.isLeaf(node) is True:
        if point in node.points:
                node.points.remove(point)
                if not node.points:
                    while functions.isLeaf(path[-1]):
                       functions.deleteChild(path[-2],node)
                       path.remove(node)
                       del node


                return True
        return False
    else:
        return delete(functions.relChild(point,node),point)