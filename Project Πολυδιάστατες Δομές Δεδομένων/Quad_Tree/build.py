from recordtype import recordtype
import insert
import boundaries

qtNode = recordtype('qtNode', 'TopLeftChild TopRightChild BottomLeftChild BottomRightChild points x y')


def build(points, max_nodes_per_quad):
    mid_x, mid_y = boundaries.boundaries(points) # Calculate first cross boundaries
    root = qtNode(None, None, None, None, points, mid_x, mid_y)
    insert.insert(root, max_nodes_per_quad)
    return root
