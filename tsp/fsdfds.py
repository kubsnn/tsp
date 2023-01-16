#read graph vertices coordinates defined in file number of vertices and then  index x y
def read_graph_vertices_coordinates(file):
	graph_vertices_coordinates = []
	with open(file, 'r') as f:
		f.readline()
		for line in f:
			line = line.strip()
			if line:
				line = line.split()
				graph_vertices_coordinates.append((float(line[1]), float(line[2])))
	return graph_vertices_coordinates


#read graph edges defined in file as index1 index2
def read_graph_edges(file):
	graph_edges = []
	with open(file, 'r') as f:
		for line in f:
			line = line.strip()
			if line:
				line = line.split()
				graph_edges.append((int(line[0]), int(line[1])))
	return graph_edges

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

#plot graph
def plot_graph(graph_vertices_coordinates, graph_edges):
	fig, ax = plt.subplots()
	for edge in graph_edges:
		ax.plot([graph_vertices_coordinates[edge[0]][0], graph_vertices_coordinates[edge[1]][0]], [graph_vertices_coordinates[edge[0]][1], graph_vertices_coordinates[edge[1]][1]], 'r-')
		ax.plot([graph_vertices_coordinates[edge[0]][0], graph_vertices_coordinates[edge[1]][0]], [graph_vertices_coordinates[edge[0]][1], graph_vertices_coordinates[edge[1]][1]], 'ko')
	plt.show()

#plot graph animation
def plot_graph_animation(graph_vertices_coordinates, graph_edges):
	fig, ax = plt.subplots()
	def animate(i):
		ax.clear()
		ax.set_title("Frame {}".format(i))
		for j in range(len(graph_edges[i])):
			ax.plot([graph_vertices_coordinates[graph_edges[i][j][0]][0], graph_vertices_coordinates[graph_edges[i][j][1]][0]], [graph_vertices_coordinates[graph_edges[i][j][0]][1], graph_vertices_coordinates[graph_edges[i][j][1]][1]], 'r-')
			ax.plot([graph_vertices_coordinates[graph_edges[i][j][0]][0], graph_vertices_coordinates[graph_edges[i][j][1]][0]], [graph_vertices_coordinates[graph_edges[i][j][0]][1], graph_vertices_coordinates[graph_edges[i][j][1]][1]], 'ko')
	ani = FuncAnimation(fig, animate, frames=len(graph_edges), interval=15, repeat=False)
	plt.show()

#read graph vertices coordinates and edges from file
graph_vertices_coordinates = read_graph_vertices_coordinates('tsp1000.txt')
graph_edges = read_graph_edges('out.txt')

#plot graph
plot_graph(graph_vertices_coordinates, graph_edges)
