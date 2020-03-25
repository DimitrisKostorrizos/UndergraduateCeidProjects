import boundaries
import build
import search
import time
import rebalance
import knnSearch

points = []
file = open("test.txt", "r")
for line in file:
    points.append(eval(line))
file.close()

temp_points = points.copy()

# points = [(-3, 1), (1, 1), (-1, -5), (1, -1), (1, 2), (2, 2), (0.5, 2.7)[(1, 1), (1, -1), (-1, 1), (-1, -1), (2, 3), (4, 1), (-1, -5), (-3, 9)]    # For some reason last node pops an error, exclude it to run!
dimensions = 2
start_time = time.time()
root = build.build(points, 1)  # Build the tree
elapsed_time = time.time() - start_time
print("Quad Tree Build: ", elapsed_time)

start_time = time.time()
for point in temp_points:
    searchNode = search.search(root, point)
elapsed_time = time.time() - start_time
print("Quad Tree Search: ", elapsed_time)

start_time = time.time()
for point in temp_points[:100]:
    search.delete(root, point)
elapsed_time = time.time() - start_time
print("Quad Tree Delete: ", elapsed_time)

start_time = time.time()
for point in temp_points[:500]:
    knnSearch.kNNSearch(root, point, 4)
elapsed_time = time.time() - start_time
print("Quad Tree KNNSearch: ", elapsed_time)
