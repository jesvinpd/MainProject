import pandas as pd
import os
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv("../linear_log.csv")

# Plot both 'm' and 'b' against 'epoch'
plt.figure(figsize=(8,5))
plt.plot(df["epoch"], df["m"], marker='o', label="m")
plt.plot(df["epoch"], df["b"], marker='s', label="b")

# Add labels and title
plt.title("m and b vs Epoch")
plt.xlabel("Epoch")
plt.ylabel("Values")
plt.legend()
plt.grid(True)

# Show plot
#plt.show()

# Find a unique filename
filename = "plot.png"
i = 1
while os.path.exists(filename):
    filename = f"plot_{i}.png"
    i += 1

# Save plot
plt.savefig(filename)
print(f"Saved plot as {filename}")
