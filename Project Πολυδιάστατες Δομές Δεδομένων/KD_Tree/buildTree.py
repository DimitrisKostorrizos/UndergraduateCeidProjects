# Build KD Tree By Omiros

dimensions = 2


def buildTree(points, depth=0):
    n = len(points)  # Get the number of points
    if n == 0:
        return None

    axis = depth % dimensions  # Decide according to what axis the split will be performed

    points.sort(key=lambda point: point[axis])  # Sort points based on the axis

    # Return multiple values, with '' as the alias name.
    return {
        'media': points[n/2],
        'rightChild': buildTree(points[median + 1:], depth + 1),
        'leftChild': buildTree(points[:median], depth + 1)
    }

