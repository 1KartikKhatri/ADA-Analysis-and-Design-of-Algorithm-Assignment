import time
import matplotlib.pyplot as plt
import sys

# Increase recursion limit for the recursive functions
# Be cautious with this, as the naive recursive function grows very fast
sys.setrecursionlimit(2000)

# 1. Naive Recursive Version (4a)
def fibonacci_recursive(n):
    """Standard recursive Fibonacci. Very inefficient."""
    if n <= 1:
        return n
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)

# 2. Iterative Version (4b)
def fibonacci_iterative(n):
    """Space-optimized iterative Fibonacci."""
    if n <= 1:
        return n
    a, b = 0, 1
    for _ in range(n - 1):
        a, b = b, a + b
    return b

# 3. Dynamic Programming - Top-Down (Memoization) (4c)
def fibonacci_dp_top_down(n, memo=None):
    """Recursive Fibonacci with memoization to store results."""
    if memo is None:
        memo = {}
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    
    memo[n] = fibonacci_dp_top_down(n - 1, memo) + fibonacci_dp_top_down(n - 2, memo)
    return memo[n]

# 4. Dynamic Programming - Bottom-Up (Tabulation) (4d)
def fibonacci_dp_bottom_up(n):
    """Iterative Fibonacci building up from the bottom."""
    if n <= 1:
        return n
    
    # Create a table to store Fibonacci numbers
    dp = [0] * (n + 1)
    dp[1] = 1
    
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
        
    return dp[n]

# --- Main script to time and plot ---

# Define the functions to test
functions = {
    "Recursive": fibonacci_recursive,
    "Iterative": fibonacci_iterative,
    "DP Top-Down": fibonacci_dp_top_down,
    "DP Bottom-Up": fibonacci_dp_bottom_up
}

# Store results: { "Function Name": [time1, time2, ...] }
times = {name: [] for name in functions}
# Set a range for n. The recursive version becomes very slow after n=35.
n_values = range(1, 36)

print("Calculating execution times...")

for n in n_values:
    print(f"  Testing for n = {n}")
    for name, func in functions.items():
        start_time = time.perf_counter()
        func(n)
        end_time = time.perf_counter()
        times[name].append(end_time - start_time)

# --- Plotting the results ---
plt.style.use('seaborn-v0_8-whitegrid')
plt.figure(figsize=(12, 8))

for name, duration in times.items():
    plt.plot(n_values, duration, marker='o', linestyle='--', markersize=4, label=name)

plt.xlabel("Fibonacci Number (n)")
plt.ylabel("Execution Time (seconds)")
plt.title("Time Complexity of Fibonacci Algorithms")
# Use a logarithmic scale for the y-axis to see the huge difference
plt.yscale('log') 
plt.legend()
plt.grid(True, which="both", ls="--")
plt.show()