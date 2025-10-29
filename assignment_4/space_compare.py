import numpy as np
import matplotlib.pyplot as plt

# Define the range of n for our theoretical plot
n_values = np.arange(1, 51)

# 1. Recursive: Space is O(n) due to the recursion call stack depth.
space_recursive = n_values

# 2. Iterative: Space is O(1) because it only uses a few fixed variables.
# We'll represent this constant value as 1 for plotting.
space_iterative = np.ones_like(n_values)

# 3. DP Top-Down: Space is O(n) for the memoization table + O(n) for the call stack.
# Overall, it's O(n).
space_dp_top_down = n_values

# 4. DP Bottom-Up: Space is O(n) to store the results in the DP table (array).
space_dp_bottom_up = n_values


# --- Plotting the results ---
plt.style.use('seaborn-v0_8-whitegrid')
plt.figure(figsize=(12, 8))

# Plot each complexity
plt.plot(n_values, space_recursive, 'o--', label=r'Recursive - $O(n)$')
plt.plot(n_values, space_iterative, 'o-', linewidth=4, label=r'Iterative - $O(1)$')
plt.plot(n_values, space_dp_top_down, 'x--', label=r'DP Top-Down - $O(n)$')
plt.plot(n_values, space_dp_bottom_up, '.--', label=r'DP Bottom-Up - $O(n)$')

plt.xlabel("Fibonacci Number (n)")
plt.ylabel("Theoretical Space Units")
plt.title("Theoretical Space Complexity of Fibonacci Algorithms")
plt.legend(fontsize=12)
plt.grid(True, which="both", ls="--")
plt.show()