#!/usr/bin/env python3


def bfs_traversal(graph, initial_node):
    # your implementation here
    
    #initialize the traversal and visited lists with the initial node
    traversal = []
    visited = []
    #initialize the queue
    queue = []

    curr = initial_node
    queue.append(curr)
    visited.append(curr)

    #begin analyzing edges
    while queue:
        
        curr = queue.pop(0)

        for edge in graph[curr]:
            if edge not in visited:
                visited.append(edge)
                queue.append(edge)

        traversal.append(curr)

    # your function will return a list!
    return traversal

def main():
    graph1 = {"+": ["*",3], "*":[2,7], 2:[],7:[],3:[]}
    inode = "+"
    graph2 = {0: [1,3], 1:[2,3], 2:[3,1], 3:[0,1]}
    jnode = 0
    print(bfs_traversal(graph1, inode))
    print(bfs_traversal(graph2, jnode))
   

# Main Execution
if __name__ == '__main__':
    main()
