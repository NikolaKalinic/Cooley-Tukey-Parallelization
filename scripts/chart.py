import matplotlib.pyplot as plt
import numpy as np

# Assuming you have three files with 10 values each
with open('seq.txt', 'r') as file:
    file1_values = [float(line.strip()) for line in file.readlines()]

# Assuming you have two more files (file2.txt and file3.txt) with similar data
# Modify the filenames accordingly if needed
with open('mp.txt', 'r') as file:
    file2_values = [float(line.strip()) for line in file.readlines()]

with open('mpi.txt', 'r') as file:
    file3_values = [float(line.strip()) for line in file.readlines()]


# Create an array for the x-axis numbering
x_values = np.arange(1, 11)

# Plotting the data
plt.plot(x_values, file1_values, label='Sekvecnijalna')
plt.plot(x_values, file2_values, label='OpenMP')
plt.plot(x_values, file3_values, label='OpenMPI')

# Adding labels and title
plt.xlabel('Redni broj')
plt.ylabel('Vreme(s)')
plt.title('Prosecno vreme izvrsavanja')

# Adding legend
plt.legend()

# Display the plot
plt.show()
