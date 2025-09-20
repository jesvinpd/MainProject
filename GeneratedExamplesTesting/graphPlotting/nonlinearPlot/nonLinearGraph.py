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

    # Create ellipse using the parameters
    # Using parametric equations for ellipse: x = h + a*cos(t), y = k + b*sin(t)
    # Center the ellipse around the mean of data points
    h = np.mean(X)  # center x
    k = np.mean(Y)  # center y
    
    # Scale the parameters to create reasonable ellipse dimensions
    a_scaled = abs(a) * 0.5  # semi-major axis (scaled down)
    b_scaled = abs(b) * 0.3  # semi-minor axis (scaled down)
    
    # Generate ellipse points
    t = np.linspace(0, 2*np.pi, 200)
    X_ellipse = h + a_scaled * np.cos(t)
    Y_ellipse = k + b_scaled * np.sin(t)

    ax.plot(X_ellipse, Y_ellipse, color="blue", label=f"Ellipse: a={a_scaled:.2f}, b={b_scaled:.2f}")

    # Graph labels
    ax.set_title(f"Ellipse Fit (Epoch {df['epoch'].iloc[frame]})")
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.legend()
    ax.grid(True)
    
    # Set axis limits to show both data and ellipse properly
    ax.set_xlim(-1, 6)
    ax.set_ylim(-2, 10)

ani = FuncAnimation(fig, update, frames=len(df), interval=300, repeat=False)
plt.show()

#Find a unique filename
import os
filename = "nonLinearPlot"
i = 1
while os.path.exists(filename):
    filename = f"nonLinearPlot_{i}"
    i += 1

# Save plot
ani.save(f"{filename}.gif", writer="pillow")
print(f"Saved plot as {filename}.gif")