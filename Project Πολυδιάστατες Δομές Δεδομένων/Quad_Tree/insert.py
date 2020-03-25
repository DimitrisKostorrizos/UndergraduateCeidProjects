from recordtype import recordtype

qtNode = recordtype('qtNode', 'TopLeftChild TopRightChild BottomLeftChild BottomRightChild points x y')

def insert(node, max_nodes_per_quad):
    cross_x = node.x
    cross_y = node.y
    PointsList = node.points
    Top_Left_List = []
    Top_Right_List = []
    Bottom_Left_List = []
    Bottom_Right_List = []
    for point in PointsList:
        if point[0] <= cross_x and point[1] >= cross_y:
            Top_Left_List.append(point)
        else:
            if cross_x <= point[0] and point[1] <= cross_y:
                Bottom_Right_List.append(point)
        if cross_x < point[0] and point[1] > cross_y:
            Top_Right_List.append(point)
        if point[0] < cross_x and point[1] < cross_y:
            Bottom_Left_List.append(point)
    PointsList.clear()

    if len(Top_Left_List) > 0: # Calculate coordinates for TopLeftChild
        Top_Left_List.sort(key=lambda tup: tup[0])
        kapou_x_TL = Top_Left_List[0][0]
        Top_Left_List.sort(key=lambda tup: tup[1])
        kapou_y_TL = Top_Left_List[-1][1]

        Top_Left_Child = qtNode(None, None, None, None, Top_Left_List, (cross_x + kapou_x_TL) / 2, (cross_y + kapou_y_TL) / 2)  # Create TopLeftChild
        node.TopLeftChild = Top_Left_Child
        if len(Top_Left_List) > max_nodes_per_quad: # Split the extra points
            insert(Top_Left_Child, max_nodes_per_quad)

    if len(Top_Right_List) > 0: # Calculate coordinates for TopRightChild
        Top_Right_List.sort(key=lambda tup: tup[0])
        kapou_x_TR = Top_Right_List[-1][0]
        Top_Right_List.sort(key=lambda tup: tup[1])
        kapou_y_TR = Top_Right_List[-1][1]

        Top_Right_Child = qtNode(None, None, None, None, Top_Right_List, (cross_x + kapou_x_TR) / 2, (cross_y + kapou_y_TR) / 2) # Create TopRightChild
        node.TopRightChild = Top_Right_Child
        if len(Top_Right_List) > max_nodes_per_quad: # Split the extra points
            insert(Top_Right_Child, max_nodes_per_quad) 

    if len(Bottom_Left_List) > 0: # Calculate coordinates for BottonLeftChild
        Bottom_Left_List.sort(key=lambda tup: tup[0])
        kapou_x_BL = Bottom_Left_List[0][0]
        Bottom_Left_List.sort(key=lambda tup: tup[1])
        kapou_y_BL = Bottom_Left_List[0][1]

        Bottom_Left_Child = qtNode(None, None, None, None, Bottom_Left_List, (cross_x + kapou_x_BL) / 2, (cross_y + kapou_y_BL) / 2) # Create BottonLeftChild
        node.BottomLeftChild = Bottom_Left_Child
        if len(Bottom_Left_List) > max_nodes_per_quad: # Split the extra points
            insert(Bottom_Left_Child, max_nodes_per_quad)

    if len(Bottom_Right_List) > 0: # Calculate coordinates for BottonRightChild
        Bottom_Right_List.sort(key=lambda tup: tup[0])
        kapou_x_BR = Bottom_Right_List[-1][0]
        Bottom_Right_List.sort(key=lambda tup: tup[1])
        kapou_y_BR = Bottom_Right_List[0][1]

        Bottom_Right_Child = qtNode(None, None, None, None, Bottom_Right_List, (cross_x + kapou_x_BR) / 2, (cross_y + kapou_y_BR ) / 2) # Create BottomRightChild
        node.BottomRightChild = Bottom_Right_Child
        if len(Bottom_Right_List) > max_nodes_per_quad: # Split the extra points
            insert(Bottom_Right_Child, max_nodes_per_quad)