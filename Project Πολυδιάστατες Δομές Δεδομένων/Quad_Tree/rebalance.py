import build
import gatherTreeNodes


def rebalance(node,maxNodesPerQuad):
    gatherTreeNodes.gather_tree_nodes(node) # Gather all points
    root = build.build(gatherTreeNodes.general_list, maxNodesPerQuad) # Rebuild tree
    return root
