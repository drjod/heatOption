import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D                                                                       
from json import load
from analyt import option_value
import sys


path = './' if len(sys.argv) == 1 else sys.argv[1]
analyt = False if len(sys.argv) < 3 else bool(sys.argv[2])




def plot():

    T, S, C, delta, gamma = np.loadtxt(path + 'output.dat', unpack=True)                                                                  
																											  
    with open('input.json') as input_data:                                                                    
        data = load(input_data)

        S_steps = data["domain"]["underlying"]["steps"] 
        time_steps = 1 # data["domain"]["time"]["steps"] 

    X = np.reshape(S, (time_steps+1, S_steps+1))
    Y = np.reshape(T, (time_steps+1, S_steps+1))
    Z = np.reshape(C, (time_steps+1, S_steps+1))  

    fig = plt.figure()
    ax2 = fig.add_subplot(231)#constrained_layout=True)
    CS = ax2.contourf(X, Y, Z, 10, cmap=plt.cm.YlGnBu_r, origin='lower')


    CS2 = ax2.contour(CS, levels=CS.levels[::2], colors='r', origin='lower')

    ax2.set_title('Black-Scholes')
    ax2.set_xlabel(r'$S$')                                                                                         
    ax2.set_ylabel(r'$T-t$')                                                                                       


    cbar = fig.colorbar(CS)
    cbar.ax.set_ylabel(r'$C(S,t)$')
    cbar.add_lines(CS2)

    # -----------------------------------------------------
																											  
    ax = fig.add_subplot(232, projection='3d')

    ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.YlGnBu_r)
    # ax.set_zlim3d(0, 10.0)
    ax.set_xlabel(r'$S$')
    ax.set_ylabel(r'$T-t$')
    ax.set_zlabel(r'$C(S,t)$')

    # -----------------------------------------------------

    ax = fig.add_subplot(234)
    ax.plot(X[time_steps], Z[time_steps], label='C', color='red')

    if analyt:
        S_val, analyt_C, analyt_delta, analyt_gamma = option_value()

        plt.gca().set_prop_cycle(None)
        ax.plot(S_val, analyt_C, label=r'$C_{analyt}$',
                    linestyle='None', marker='o', markersize=2, color='red')

    ax.grid(True)
    ax.legend()
    # -----------------------------------------------------

    Delta = np.reshape(delta, (time_steps+1, S_steps+1))

    ax = fig.add_subplot(235)
    ax.plot(X[time_steps], Delta[time_steps], label=r'$\Delta$', color='blue')

    if analyt:
        plt.gca().set_prop_cycle(None)
        ax.plot(S_val, analyt_delta, label=r'$\Delta_{analyt}$', 
                    linestyle='None', marker='o', markersize=2, color='blue')

    ax.grid(True)
    ax.legend()
    # -----------------------------------------------------

    Gamma = np.reshape(gamma, (time_steps+1, S_steps+1))  

    ax = fig.add_subplot(236)
    ax.plot(X[time_steps], Gamma[time_steps], label=r'$\Gamma$', color='green')

    if analyt:
        ax.plot(S_val, analyt_gamma, label=r'$\Gamma_{analyt}$', 
                    linestyle='None', marker='o', markersize=2, color='green')

    ax.grid(True)
    ax.legend()

    plt.subplots_adjust(top=0.92, bottom=0.08, left=0.10, right=0.95, hspace=0.25,
                    wspace=0.4)
    plt.show()


if __name__ == '__main__':
    plot()


