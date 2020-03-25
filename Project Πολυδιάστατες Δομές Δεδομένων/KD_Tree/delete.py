import searchPoint
import findMinimum
import maxim


def deleteNode(root, point, depth):
    searchedNode = searchPoint.kdTreeSearch(root, point, depth)
    tempNode = None
    if searchedNode['found'] is False: # Check if node exists in the tree
        print("Node to be deleted, Not Found")
    else:
        if searchedNode['parentNode'] is None:  # Root case
            if searchedNode['node'].leftChild is None and searchedNode['node'].rightChild is None:
                print("You deleted the only node in tree, tree is destroyed now please rebuild")
                searchedNode['node'] = None
            elif searchedNode['node'].rightChild is not None:  # If node to be deleted has a right subtree

                minNode = maxim.findMin(searchedNode['node'].rightChild, searchedNode['depth'] % 2)
                deleteNode(searchedNode['node'], minNode,searchedNode['depth'] % 2)
                searchedNode['node'].node = minNode
            elif searchedNode['node'].leftChild is not None:

                maxNode = maxim.findMax(searchedNode['node'].leftChild, searchedNode['depth'] % 2)
                deleteNode(searchedNode['node'], maxNode,searchedNode['depth'] % 2)
                searchedNode['node'].node = maxNode
        elif searchedNode['node'].leftChild is None and searchedNode['node'].rightChild is None: # Node without children
            if searchedNode['parentNode'].leftChild == searchedNode['node']:
                searchedNode['parentNode'].leftChild = None
            if searchedNode['parentNode'].rightChild == searchedNode['node']:
                searchedNode['parentNode'].rightChild = None
        elif searchedNode['node'].rightChild is not None:  # If node to be deleted has a right subtree
            minNode = maxim.findMin(searchedNode['node'].rightChild, searchedNode['depth'] % 2)

            if searchedNode['parentNode'].leftChild == searchedNode['node']:
                deleteNode(searchedNode['node'], minNode,searchedNode['depth'] % 2)
                searchedNode['parentNode'].leftChild.node = minNode
            if searchedNode['parentNode'].rightChild == searchedNode['node']:
                deleteNode(searchedNode['node'], minNode,searchedNode['depth'] % 2)
                searchedNode['parentNode'].rightChild.node = minNode

        elif searchedNode['node'].leftChild is not None: 
            maxNode = maxim.findMax(searchedNode['node'].leftChild, searchedNode['depth'] % 2)

            if searchedNode['parentNode'].leftChild == searchedNode['node']:
                deleteNode(searchedNode['node'], maxNode,searchedNode['depth'] % 2)
                searchedNode['parentNode'].leftChild.node = maxNode
            if searchedNode['parentNode'].rightChild == searchedNode['node']:
                deleteNode(searchedNode['node'], maxNode,searchedNode['depth'] % 2)
                searchedNode['parentNode'].rightChild.node = maxNode


