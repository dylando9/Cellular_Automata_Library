# Creator: Yara Khoury
# Modified by: Yara Khoury
# Date Created: December 15, 2023
# Last revisited: December 15, 2023

import csv
import matplotlib.pyplot as plt

# lists to hold the column data
initial_probabilities = []
final_affected_counts = []
final_unaffected_counts = []
final_dead_counts = []

# get data from CSV
with open("../../Utils/Data/Prob_results.csv", 'r') as file:
    csv_reader = csv.reader(file)
    next(csv_reader)  # skip the header
    for row in csv_reader:
        initial_probabilities.append(float(row[0]))
        final_affected_counts.append(int(row[1]))
        final_unaffected_counts.append(int(row[2]))
        final_dead_counts.append(int(row[3]))

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(initial_probabilities, final_affected_counts, label='Affected Cells')
plt.plot(initial_probabilities, final_unaffected_counts, label='Unaffected Cells')
plt.plot(initial_probabilities, final_dead_counts, label='Dead Cells')
plt.xlabel('Initial Probability')
plt.ylabel('Count of Cells')
plt.title('Effect of Initial Probability on Cancer Growth')
plt.legend()
plt.grid(True)

# Save the plot as a PNG file
plt.savefig('initial_prob_analysis.png')