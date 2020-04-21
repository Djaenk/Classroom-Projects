import networkx
import random

vertex_count = 1
for i in range(15):
    #Arguments produce graphs increasing quartically in size with linear edge
    #densities of 10. Density chosen based on discussion in the following paper:
    # Guy Melançon. Just how dense are dense graphs in the real world? A
    # methodological note. BE-LIV 2006: BEyond time and errors: novel evaLuation
    # methods for Information Visualization (AVIWorkshop), May 2006, Venice,
    # Italy, pp.75-81. ￿lirmm-00091354￿
    #https://hal-lirmm.ccsd.cnrs.fr/lirmm-00091354

    graph = networkx.connected_watts_strogatz_graph(vertex_count, 10 if 10 < vertex_count else vertex_count, 1)
    for (node1, node2, attributes) in graph.edges(data = True):
        attributes["weight"] = random.randint(1, vertex_count)
    vertices = graph.nodes()
    weights = networkx.get_edge_attributes(graph, "weight")
    edges = []
    for edge in graph.edges():
        target1 = edge[0]
        target2 = edge[1]
        weight = weights[edge]
        edges.append((target1, target2, weight))

    filename = f'graph{i}.txt'
    with open(filename, "w+") as file:
        file.write(f'[{len(vertices)}]')
        file.write('\n')
        for vertex in vertices:
            file.write(str(vertex))
            file.write('\n')
        file.write('[undirected]')
        file.write('\n')
        for edge in edges:
            file.write(f'{edge[2]:000006} - {edge[0]} - {edge[1]}')
            file.write('\n')

    vertex_count *= 2