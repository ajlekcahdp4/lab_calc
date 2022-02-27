import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter, AutoMinorLocator)
import numpy as np
#GNUplot
#Векторная графика .svg
def DrawGraph (N, x, y, a, b, ad, bd, name1, name2):
    X = np.linspace (min(x)* 0.95, max(x)* 1.05, 100)
    Y = np.array([a*x_c + b for x_c in X])
    fig, ax = plt.subplots(figsize=(8, 6))

    ax.set_xlabel(name1, fontsize=14)
    ax.set_ylabel(name2, fontsize=14)
    ax.text(min(x) , min(y), 'y = %.4f*x + %.4f' %(a, b))
    ax.set_title(r'График №1', fontsize=12)

    ax.grid(which="major", linewidth=1.2)
    ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)

    ax.plot(X, Y, c = 'blue', label="График по МНК")
    ax.scatter(x, y, c = 'red', label="Измеренные точки")
    
    ax.legend()

    ax.xaxis.set_minor_locator(AutoMinorLocator())
    ax.yaxis.set_minor_locator(AutoMinorLocator())
    ax.tick_params(which='major', length=10, width=2)
    ax.tick_params(which='minor', length=5, width=1)
    
    plt.savefig(str(input("Enter the name for graph picture file\n")))