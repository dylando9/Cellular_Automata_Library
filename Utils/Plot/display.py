# Creator: Yara Khoury 
# Date Created: December 4, 2023
# Last revisited: December 15, 2023

# Read from CSV file and produce images of matrices of every step. 

import matplotlib.pyplot as plt 
import matplotlib.colors as colors
from matplotlib.colors import ListedColormap
import csv 

# Path to the CSV file
filename = "../Data/Application.csv"

# function: read_csv_to_matrices
#           read the CSV file and convert it into a list of matrices
# input:    csv filename (and path)
# output:   returns lists of matrices and counts
def read_csv_to_matrices(filename):
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        matrices = []  # start list to store all matrices
        counts = []  # start list to store the counts of cells in each states
        current_matrix = []  # temp list to store the current matrix

        for row in reader:
            # check if current row has state count info and append to list
            if 'State' in row[0]:
                counts.append(row)
            # if not, check for the separator indicating a new matrix
            elif '------' in row:
                if current_matrix:
                    matrices.append(current_matrix)  # add the completed matrix to the list
                    current_matrix = []  # reset the current matrix so it can hold the next one
            else:
                # add the current row to the current matrix
                # and convert each cell into an integer
                current_matrix.append([int(cell) for cell in row if cell])

        # add the last matrix to the list if it exists
        if current_matrix:
            matrices.append(current_matrix)

    return matrices, counts

# function: plot_matrices
#           plots each matrix using Matplotlib
# input:    matrices and counts read from csv file
# output:   plots matrix and saves it into png file
def plot_matrices(matrices, counts):
    cmap = ListedColormap(['orange', 'grey', 'black']) 
    boundaries = [-0.5, 0.5, 1.5, 2.5]
    norm = colors.BoundaryNorm(boundaries, cmap.N, clip=True)

    for i, matrix in enumerate(matrices):
        fig, ax = plt.subplots(figsize=(8, 8))
        im = ax.imshow(matrix, cmap=cmap, norm=norm, interpolation='nearest')  # Use the discrete colormap and norm
        ax.set_title(f'Step {i+1}')
        # Create a colorbar with the colormap
        cbar = fig.colorbar(im, ax=ax, ticks=[0, 1, 2], fraction=0.046, pad=0.04)  
        # Set the tick labels as state values
        cbar.ax.set_yticklabels(['0', '1', '2'])  
        # format the counts into a string and place it on the plot
        count_str = "\n".join(counts[i])

        # Placing the text in the figure space but not overlapping with the plot
        fig.text(0.02, 0.02, count_str, fontsize=10, verticalalignment='bottom')

        plot_image_name = f'matrix_step{i+1}.png'
        plt.savefig(plot_image_name, bbox_inches='tight')
        plt.close()


# Read matrices from the CSV file and store them in a list
matrices, counts = read_csv_to_matrices(filename)

# Plot all the matrices
plot_matrices(matrices, counts)