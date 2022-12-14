import numpy as np
import matplotlib.pyplot as plt

def visualize_grid(filename):
    dfile = open('Data/'+filename, 'r')

    # Read the second line 
    line = dfile.readline()
    line = dfile.readline()
    gridrow = int(line.split()[2])
    gridcol = int(line.split()[4])

    # Read the eighth line
    line = dfile.readline()
    line = dfile.readline()
    line = dfile.readline()
    line = dfile.readline()
    line = dfile.readline()
    line = dfile.readline()
    steps = int(line.split()[3])

    print('Grid size: ', gridrow, gridcol)
    print('Steps: ', steps)
    return gridcol, gridrow, steps


if __name__ == '__main__':
    visualize_grid('test.txt')
