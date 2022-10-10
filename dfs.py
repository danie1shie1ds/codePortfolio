#!/usr/bin/env python3

# def dfs_recurse(graph, curr, traversal, visited):
#     if curr not in visited:
#         traversal.append(curr)
#         visited.add(curr)

#     if not graph[curr]:
#             x = -1
#             while not graph[curr]:
#                 curr = traversal[x]
#                 x = x - 1
#                 print(curr)
#             curr = graph[curr].pop(0)
#             print("a")
#             return
#     curr = graph[curr].pop(0)
#     print("b")
#     dfs_recurse(graph, curr, traversal, visited)


def dfs_traversal(graph, initial_node):
    # your implementation here
    #initialize the traversal and visited lists with the initial node
    traversal = []
    #initialize the stack
    stack = [initial_node]
    traversal.append(initial_node)

    curr = initial_node

    # dfs_recurse(graph, curr, traversal, visited)
    while stack:
        curr = stack[-1]
        if curr not in traversal:
            stack.append(curr)
            traversal.append(curr)
        
        if graph[curr]:
            stack.append(graph[curr].pop(0))
        else:
            stack.pop()




    # your function will return a list!
    return traversal

def main():
    graph1 = {"+": ["*",3], "*":[2,7], 2:[],7:[],3:[]}
    inode = "+"
    graph2 = {0: [1,3], 1:[2,3], 2:[3,1], 3:[0,1]}
    jnode = 0
    print(dfs_traversal(graph1, inode))
    print(dfs_traversal(graph2, jnode))
   

# Main Execution
if __name__ == '__main__':
    main()

