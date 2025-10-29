import time
import numpy as np
import matplotlib.pyplot as plt

# --- Algorithm Implementations ---

# 1. 0/1 Knapsack using Dynamic Programming (Bottom-up for simplicity)
def knapsack_01_dp(W, weights, values, n):
    # Create a DP table to store results of subproblems
    dp = [[0 for _ in range(W + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, W + 1):
            # If the current item's weight is more than the capacity w,
            # we can't include it.
            if weights[i - 1] > w:
                dp[i][w] = dp[i - 1][w]
            # Otherwise, we find the maximum of either including the item or not
            else:
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                )
    return dp[n][W]

# 2. Fractional Knapsack using Greedy approach
def fractional_knapsack_greedy(W, weights, values, n):
    # Create a list of items with their value-to-weight ratios
    items = []
    for i in range(n):
        if weights[i] > 0:
            items.append({
                "value": values[i],
                "weight": weights[i],
                "ratio": values[i] / weights[i]
            })

    # Sort items in descending order of their ratio
    items.sort(key=lambda x: x["ratio"], reverse=True)

    total_value = 0.0
    remaining_capacity = W

    for item in items:
        if remaining_capacity == 0:
            break
        
        if item["weight"] <= remaining_capacity:
            remaining_capacity -= item["weight"]
            total_value += item["value"]
        else:
            total_value += item["ratio"] * remaining_capacity
            remaining_capacity = 0
            
    return total_value

# --- Performance Measurement ---

n_values = range(10, 501, 20) # Test for n from 10 to 500
times_dp = []
times_greedy = []

print("Running simulations...")

for n in n_values:
    # Generate random data for items
    weights = np.random.randint(1, 30, n)
    values = np.random.randint(10, 100, n)
    
    # Let W grow proportionally to n to make the comparison fair
    W = int(n * 5)

    # Time the 0/1 DP Knapsack
    start_time = time.time()
    knapsack_01_dp(W, weights, values, n)
    end_time = time.time()
    times_dp.append(end_time - start_time)

    # Time the Fractional Greedy Knapsack
    start_time = time.time()
    fractional_knapsack_greedy(W, weights, values, n)
    end_time = time.time()
    times_greedy.append(end_time - start_time)

print("Simulations complete. Plotting graph...")

# --- Plotting the Graph ---
plt.style.use('seaborn-v0_8-whitegrid')
plt.figure(figsize=(12, 7))

plt.plot(n_values, times_dp, marker='o', linestyle='-', color='r', label='0/1 Knapsack (DP) - O(n*W) ≈ O(n²)')
plt.plot(n_values, times_greedy, marker='s', linestyle='--', color='g', label='Fractional Knapsack (Greedy) - O(n log n)')

plt.xlabel('Number of Items (n)', fontsize=14)
plt.ylabel('Execution Time (seconds)', fontsize=14)
plt.title('Time Complexity Comparison of Knapsack Algorithms', fontsize=16)
plt.legend(fontsize=12)
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)
plt.grid(True)
plt.show()