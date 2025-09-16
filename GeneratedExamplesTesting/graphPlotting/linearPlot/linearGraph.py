import pandas as pd
import matplotlib
matplotlib.use("TkAgg") 
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

# Your training data (same as in input.td)
X = np.array([1, 2, 3, 4])
Y = np.array([2, 3, 5, 7])

# Read regression log
df = pd.read_csv("./linear_log.csv")

fig, ax = plt.subplots()

def update(frame):
    ax.clear()

    # Plot original data points
    ax.scatter(X, Y, color="red", label="Data Points")

    # Get current regression parameters
    m = df["m"].iloc[frame]
    b = df["b"].iloc[frame]

    # Plot regression line with current parameters
    X_line = np.linspace(min(X) - 1, max(X) + 1, 200)
    Y_pred = m * X_line + b   # linear model: y = mx + b

    ax.plot(X_line, Y_pred, color="blue", label=f"Model: y={m:.3f}x+{b:.3f}")

    # Graph labels
    ax.set_title(f"Linear Regression Fit (Epoch {df['epoch'].iloc[frame]})")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend()
    ax.grid(True)
    
    # Set consistent axis limits for better visualization
    ax.set_xlim(0, 5)
    ax.set_ylim(0, 8)

# Create animation - sample every 10th frame for faster animation
sample_frames = range(0, len(df), 10)  # Every 10th epoch
ani = FuncAnimation(fig, update, frames=sample_frames, interval=100, repeat=False)
plt.show()

# Optional: Save as GIF (uncomment to save)
import os
filename = "linearAnimation"
i = 1
while os.path.exists(f"{filename}.gif"):
    filename = f"linearAnimation_{i}"
    i += 1

ani.save(f"{filename}.gif", writer="pillow")
print(f"Saved animation as {filename}.gif")

