import matplotlib.pyplot as plt

def read_data_from_file(filename):
    sizes = []
    times = []

    with open(filename, 'r') as file:
        lines = file.readlines()

        for line in lines[1:]:
            parts = line.split()
            if len(parts) >= 2:  
                size = int(parts[0])
                time_taken = float(parts[1])
                sizes.append(size)
                times.append(time_taken)

    return sizes, times

def plot_graph(sizes, times):
    plt.plot(sizes, times, marker='o', linestyle='-', color='b')
    plt.xlabel("Array Size")
    plt.ylabel("Time Taken (seconds)")
    plt.title("bubble Sort Performance (from file)")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    filename = "bubblesort_results.txt" 
    sizes, times = read_data_from_file(filename)
    plot_graph(sizes, times)
