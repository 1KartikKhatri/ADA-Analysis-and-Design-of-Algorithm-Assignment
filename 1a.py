import random
import time
import matplotlib.pyplot as plt

def generate_random_array(n):
    return [random.randint(0,100000) for _ in range(n)]


def linear_search(arr, target):
    for x in arr:
        if x ==target:
            return True
    return False


n_values = [100, 500, 1000, 2000, 5000, 10000, 20000] 
times = []

for n in n_values:
    arr = generate_random_array(n)
    target = arr[-1] 

    start = time.time()
    for _ in range(10000):  
        linear_search(arr, target)
    end = time.time()

    total_time = end- start
    avg_time = total_time /10000.0
    times.append(avg_time)

    print(f"n={n}, Total time={total_time:.6f}s, Avg per search={avg_time:.10f}s")


plt.plot(n_values, times, marker='o')
plt.xlabel("Number of elements (n)")
plt.ylabel("Average time per search (s)")
plt.title("Linear Search Time vs List Size")
plt.grid(True)
plt.show()
