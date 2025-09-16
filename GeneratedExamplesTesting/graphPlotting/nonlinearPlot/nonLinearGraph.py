import pandas as pd
import matplotlib
matplotlib.use("TkAgg") 
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

# Your training data
X = np.array([1, 2, 3, 4])
Y = np.array([2, 3, 5, 7])

# Read regression log
df = pd.read_csv("./nonlinear_log.csv")

fig, ax = plt.subplots()

def update(frame):
    ax.clear()

    # Plot original data points
    ax.scatter(X, Y, color="red", label="Data Points")

    # Get current regression parameters
    a = df["a"].iloc[frame]
    b = df["b"].iloc[frame]

    # Plot regression curve with current parameters
    X_line = np.linspace(min(X) - 1, max(X) + 1, 200)
    Y_pred = a * (X_line**2) + b   # nonlinear model: y = a*x^2 + b

    ax.plot(X_line, Y_pred, color="blue", label=f"Model: y={a:.2f}x²+{b:.2f}")

    # Graph labels
    ax.set_title(f"Nonlinear Regression Fit (Epoch {df['epoch'].iloc[frame]})")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend()
    ax.grid(True)

ani = FuncAnimation(fig, update, frames=len(df), interval=300, repeat=False)
plt.show()

# Find a unique filename
#import os
# filename = "nonLinearPlot"
# i = 1
# while os.path.exists(filename):
#     filename = f"nonLinearPlot_{i}"
#     i += 1

# # Save plot
# ani.save(f"{filename}.gif", writer="pillow")
# print(f"Saved plot as {filename}.gif")