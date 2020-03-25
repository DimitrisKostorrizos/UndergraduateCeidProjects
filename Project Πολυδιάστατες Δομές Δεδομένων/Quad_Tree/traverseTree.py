import insert


def traverse_tree(node, point, max_nodes_per_quad):
    if node.TopLeftChild is None and node.TopRightChild is None and node.BottomLeftChild is None and node.BottomRightChild is None: # Is leaf node
        node.points.append(point)
        if len(node.points) > max_nodes_per_quad: # Spilt child if points are hight that max point per quad
            print(node.points)
            return insert.insert(node, max_nodes_per_quad)
    cross_x = node.x
    cross_y = node.y
	# Check for the suitable child
    if point[0] <= cross_x and point[1] >= cross_y:
        traverse_tree(node.TopLeftChild, point, max_nodes_per_quad)
    else:
        if cross_x <= point[0] and point[1] <= cross_y:
            traverse_tree(node.BottomRightChild, point, max_nodes_per_quad)
    if cross_x < point[0] and point[1] > cross_y:
        traverse_tree(node.TopRightChild, point, max_nodes_per_quad)
    if point[0] < cross_x and point[1] < cross_y:
        traverse_tree(node.BottomLeftChild, point, max_nodes_per_quad)