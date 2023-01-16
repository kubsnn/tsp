import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

with open("tsp1000.txt", "r") as f:
    n = int(f.readline())
    c = [[int(j) for j in i.strip().split(" ")] for i in f.readlines()]

with open("out.txt", "r") as f:
    e = [[int(j) for j in i.strip().split(" ")] for i in f.readlines()]
    ee = []
    for i in range(len(e)//n):
        ee.append(e[i*n:(i+1)*n])

    ee = ee[::]

fig, ax = plt.subplots()


def animate(i):
    ax.clear()
    ax.set_title("Frame {}".format(i))
    for j in range(len(ee[i])):
        ax.plot([c[ee[i][j][0]][0], c[ee[i][j][1]][0]], [
                c[ee[i][j][0]][1], c[ee[i][j][1]][1]], 'r-')
        ax.plot([c[ee[i][j][0]][0], c[ee[i][j][1]][0]], [
                c[ee[i][j][0]][1], c[ee[i][j][1]][1]], 'ko')


ani = FuncAnimation(fig, animate, frames=len(ee), interval=15, repeat=False)
plt.show()
