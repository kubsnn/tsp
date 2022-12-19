# show data from given files as a graph
import networkx as nx
import matplotlib.pyplot as plt


def visualizeResults(inputPath, outputPath):

    # open files
    inputFile = open(inputPath, "r")
    tspOutput = open(outputPath, "r")

    # transfrom tspOutput to sensible data
    # create dict for results
    results = {}
    for line in tspOutput:
        if line.startswith("Algorithm"):
            algName = line.split(":")[1].strip()
            results[algName] = {}
            results[algName]["path"] = []
        elif line.startswith("Path length"):
            solutionLength = float(line.split(":")[1].strip())
            results[algName]["solutionLength"] = solutionLength
        elif line.startswith("Elapsed"):
            results[algName]["elapsedTime"] = float(line.split(":")[1].strip())
        else:
            if line.strip() != "" and line.strip() != "[" and line.strip() != "]":
                results[algName]["path"] += list(
                    filter(lambda a: a != "", (line.strip()).split(",")))
            if line.strip() == "]":
                # remove last element from path
                results[algName]["path"] = results[algName]["path"][:-1]

    # print(results)

    # inputFile to vertices list
    vertices = []
    inputFile.readline()
    for line in inputFile:
        vertices.append(
            tuple(map(int, [line.strip().split(" ")[1], line.strip().split(" ")[2]])))

    # print(vertices)

    # transform vertices to nice networkx format (iterator,{'pos':(x,y)})
    v = [(i, {'pos': (vertices[i][0], vertices[i][1])})
         for i in range(len(vertices))]

    numOfGrpahs = len(results)

    plotNum = 0
    for key in results:
        fig, ax = plt.subplots()
        # create graph
        G = nx.Graph()
        G.add_nodes_from(v)
        # add edges
        for i in range(len(results[key]["path"])-1):
            G.add_edge(int(results[key]["path"][i]),
                       int(results[key]["path"][i+1]))
        G.add_edge(int(results[key]["path"][0]), int(results[key]["path"][-1]))
        ax = plt.gca()
        ax.set_title(key, {'fontsize': 14, 'fontweight': 'bold'})
        # draw subgraph
        nx.draw(G, nx.get_node_attributes(G, 'pos'), with_labels=True,
                node_size=150, ax=ax, font_size=8, font_weight='bold', node_color='r')
        # add path length
        ax.text(0.05, 0.95, "Path length: " +
                str(results[key]["solutionLength"]), transform=ax.transAxes, fontsize=10, verticalalignment='top')
        # add elapsed time
        ax.text(0.05, 0.90, "Elapsed time: " +
                str(results[key]["elapsedTime"]), transform=ax.transAxes, fontsize=10, verticalalignment='top')
        plotNum += 1

    plt.show()


if __name__ == '__main__':

    # open file settings.in
    settingsFile = open("settings.in", "r")
    inputPath = settingsFile.readline().strip()
    vAmount = int(settingsFile.readline())
    vMax = int(settingsFile.readline())
    outputPath = settingsFile.readline().strip()

    visualizeResults(inputPath, outputPath)
