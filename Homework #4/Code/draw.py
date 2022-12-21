import matplotlib.pyplot as plt
import numpy as np

intervals = 100

def read_rand(method, num):
    x = []
    file = open(f"rand_{num}_{method}.txt", "r")
    while True:
        line = file.readline()
        if not line:
            break
        x.append(line.strip())
    x = list(map(float, x))
    file.close()
    return x

def draw_hist(method, num):
    x = read_rand(method, num)
    plt.title(f'{method}_rand_nums={num}')
    plt.xlabel('X')
    plt.ylabel('Probability')
    plt.hist(x, bins=intervals, density=True, facecolor='xkcd:blue green')
    plt.savefig(f'{method}_rand={num}.png')
    plt.clf()

draw_hist("uniform", 100)
draw_hist("uniform", 1000)
draw_hist("uniform", 10000)
draw_hist("uniform", 100000)
draw_hist("gauss", 100)
draw_hist("gauss", 1000)
draw_hist("gauss", 10000)
draw_hist("gauss", 100000)

