import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv(r"c:\Users\kartik nath khatri\Desktop\ADA class sem 2\assignment_3\results.txt")

sizes = data["Size"]
times = data["Time"]

plt.figure(figsize=(8, 6))
plt.plot(sizes, times, marker="o", color="green", linestyle="-", label="Strassen Method")

plt.xlabel("Matrix Size (N x N)")
plt.ylabel("Execution Time (seconds)")
plt.title("Matrix Multiplication Performance - Strassen's Method")
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend()

plt.savefig("strassen_performance.png", dpi=300)
plt.show()
