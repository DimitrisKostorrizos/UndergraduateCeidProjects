import medianBuild
import searchPoint
import rebalance
import insert
import kNNQuery
import delete
import time

points = []
file = open("test.txt", "r")
for line in file:
    points.append(eval(line))
file.close()

dimensions = 2

start_time = time.time()
root = medianBuild.kdTreeBuild(points, 0)  # Build the tree
elapsed_time = time.time() - start_time

print("Kd Tree Build: ", elapsed_time)

start_time = time.time()
for point in points:
    searchNode = searchPoint.kdTreeSearch(root, point, 0)
elapsed_time = time.time() - start_time
print("Kd Tree Search: ", elapsed_time)

start_time = time.time()
for point in points[:100]:
    delete.deleteNode(root, point, 0)
elapsed_time = time.time() - start_time
print("Kd Tree Delete: ", elapsed_time)

start_time = time.time()
for point in points[:100]:
    KNNPoints = kNNQuery.kNNSearch(root, point, 4)
elapsed_time = time.time() - start_time
print("Kd Tree KNNSearch: ", elapsed_time)
