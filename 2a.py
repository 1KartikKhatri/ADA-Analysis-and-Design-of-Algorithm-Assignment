import random
import time
import matplotlib.pyplot as plt

# Generate a sorted array
def generate_sorted_array(n):
    arr = [random.randint(0, 10)]
    for i in range(1, n):
        arr.append(arr[-1] + random.randint(1, 10))
    return arr

# Binary search (with dummy work to amplify timing)
def binary_search(arr, target):
    left, right = 0, len(arr)
    while left < right:
        mid = left + (right - left) // 2
        if arr[mid] == target:
            return True
        if arr[mid] < target:
            # Dummy work to exaggerate runtime difference
            for _ in range(100):
                pass
            left = mid + 1
        else:
            right = mid
    return False

# Benchmark function
def benchmark_binary_search(n,trials=100000):
    arr = generate_sorted_array(n)
    target = arr[-1] + 1  # not present → worst case
    start = time.perf_counter()
    for _ in range(trials):
        binary_search(arr, target)
    end = time.perf_counter()
    total_time = end - start
    avg_time = total_time / trials
    return avg_time

# Run experiments for increasing n
sizes = [100, 500, 1000, 5000, 10000, 20000, 50000]
times = []

for n in sizes:
    avg = benchmark_binary_search(n,trials=20000)  # fewer trials for big n
    print(f"n={n}, avg_time={avg:.2e} s")
    times.append(avg)

# Plot only measured data
plt.figure(figsize=(8,6))
plt.plot(sizes, times, marker='o', color="blue", label="Binary Search (measured)")
plt.xlabel("Array Size (n)")
plt.ylabel("Average Time per Search (seconds)")
plt.title("Binary Search: Average Time vs Array Size")
plt.grid(True)
plt.show()
