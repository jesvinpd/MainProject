import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

# Your training data
X = np.array([1, 2, 3, 4])
Y = np.array([2, 3, 5, 7])

# Read linear regression log from parent folder
df = pd.read_csv("../linear_log.csv")

fig, ax = plt.subplots()

def update(frame):
    ax.clear()

    # Plot original data points
    ax.scatter(X, Y, color="red", label="Data Points")

    # Get current linear regression parameters
    m = df["m"].iloc[frame]
    b = df["b"].iloc[frame]

    # Plot regression line with current parameters
    X_line = np.linspace(min(X) - 1, max(X) + 1, 200)
    Y_pred = m * X_line + b   # linear model: y = m*x + b

    ax.plot(X_line, Y_pred, color="blue", label=f"y = {m:.4f}x + {b:.4f}")

    # Graph labels
    ax.set_title(f"Linear Regression Fit (Epoch {df['epoch'].iloc[frame]})")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend()
    ax.grid(True)

ani = FuncAnimation(fig, update, frames=len(df), interval=300, repeat=False)
plt.show()

