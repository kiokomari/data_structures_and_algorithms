import networkx as nx
import matplotlib.pyplot as plt
import graphm
import time

mtxt = open('input.txt').read()
mtxt = [item.split() for item in mtxt.split('\n')[:-1]]
g = nx.DiGraph()
graph = graphm.Graph(len(mtxt) - 1)
# filter
for y in range(1, len(mtxt)):
    for x in range(1, len(mtxt)):
        if mtxt[y][x] != 'z':
            g.add_edge(mtxt[y][0], mtxt[0][x], weight=mtxt[y][x])
            graph.addEdge(int(mtxt[y][0]), int(mtxt[0][x]), int(mtxt[y][x]))
            print(mtxt[y][0], " -> ", mtxt[0][x], " = ", mtxt[y][x])
print("Enter first dot")
fr = int(input())
print("Enter last dot")
to = int(input())
start_time = time.time()
if (fr > len(mtxt)-2 or to > len(mtxt)-2):
    print(fr, " -> ", to, " = ", -1)
    resArr = graph.BellmanFord(0)
    result = resArr[1]

else:
    resArr = graph.BellmanFord(fr)
    result = resArr[to]
    print(fr, " -> ", to, " = ", result)
print("--- %s seconds ---" % (time.time() - start_time))
answer = [(u, v) for (u, v, d) in g.edges(
    data=True) if d['weight'] == str(result)]
other = [(u, v) for (u, v, d) in g.edges(
    data=True) if d['weight'] != str(result)]
pos = nx.spring_layout(g)
nx.draw_networkx_nodes(g, pos)
nx.draw_networkx_edges(g, pos, edgelist=answer,
                       edge_color='b', arrowstyle='->')
nx.draw_networkx_edges(g, pos, edgelist=other, edge_color='b', arrowstyle='->')
nx.draw_networkx_labels(g, pos, font_size=11, font_family='sans-serif')
plt.savefig("filename.png")
