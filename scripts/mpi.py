import matplotlib.pyplot as plt
import numpy as np

# Assuming you have three files with 10 values each
with open('test.txt', 'r') as file:
    file1_values = [float(line.strip()) for line in file.readlines()]



# Create an array for the x-axis numbering
x_values = np.arange(1, 11)

# Plotting the data

plt.plot(x_values, file1_values, label='OpenMPI')

# Adding labels and title
plt.xlabel('Broj procesa')
plt.ylabel('Vreme(s)')
plt.title('Vreme izvrsavanja OpenMPI')

# Adding legend
plt.legend()
plt.xticks(np.arange(min(x_values), max(x_values)+1, 1))

# Display the plot
plt.show()
