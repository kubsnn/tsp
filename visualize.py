#show data from given files as a graph
import networkx as nx
import matplotlib.pyplot as plt

#open file settings.in
settingsFile = open("settings.in", "r")
inputPath = settingsFile.readline().strip()
vAmount = int(settingsFile.readline())
vMax = int(settingsFile.readline())
outputPath = settingsFile.readline().strip()

#open files
inputFile = open(inputPath, "r")
tspOutput = open(outputPath, "r")

#transfrom tspOutput to sensible data
#create dict for results
results = {}
for line in tspOutput:
    if line.startswith("Path"):
        path = list(line.split(":")[1].strip().split(" "))
        results[tspTitle]["path"] = path
    else:
        tspTitle = line.split(":")[0].strip()
        pathLength = float(line.split(":")[1])
        #add to results
        results[tspTitle] = {}
        results[tspTitle]["length"] = pathLength

print(results)

#inputFile to vertices list
vertices = []
inputFile.readline()
for line in inputFile:
    vertices.append(tuple(map(int,line.strip().split(" "))))

print(vertices)

#transform vertices to nice networkx format (iterator,{'pos':(x,y)})
v = [(i,{'pos':(vertices[i][0],vertices[i][1])}) for i in range(len(vertices))]

numOfGrpahs = len(results)


plotNum = 0
for key in results:
    fig, ax = plt.subplots()
    #create graph
    G = nx.Graph()
    G.add_nodes_from(v)
    #add edges
    for i in range(len(results[key]["path"])-1):
        G.add_edge(int(results[key]["path"][i]), int(results[key]["path"][i+1]))
    G.add_edge(int(results[key]["path"][0]), int(results[key]["path"][-1]))
    ax = plt.gca()
    ax.set_title(key,{'fontsize': 14, 'fontweight': 'bold'})
    #draw subgraph
    nx.draw(G, nx.get_node_attributes(G,'pos'), with_labels=True, node_size=150, ax=ax, font_size=8, font_weight='bold', node_color='r')
    #add path length
    ax.text(0.05, 0.95, "Path length: " + str(results[key]["length"]), transform=ax.transAxes, fontsize=10, verticalalignment='top')
    plotNum += 1

plt.show()