#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int weight;
    double ratio;
};

int compareItems(const void *a, const void *b) {
    struct Item *itemA = (struct Item *)a;
    struct Item *itemB = (struct Item *)b;

    if (itemB->ratio > itemA->ratio) return 1;
    if (itemB->ratio < itemA->ratio) return -1;
    return 0;
}

double fractionalKnapsack(int W, int values[], int weights[], int n) {
    struct Item items[n];

    for (int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        if (weights[i] > 0) {
            items[i].ratio = (double)values[i] / weights[i];
        } else {
            items[i].ratio = 0; 
        }
    }

    qsort(items, n, sizeof(struct Item), compareItems);
    
    double totalValue = 0.0;
    double remainingCapacity = W;

    for (int i = 0; i < n; i++) {
        if (remainingCapacity == 0) break; 

        if (items[i].weight <= remainingCapacity) {
            remainingCapacity -= items[i].weight;
            totalValue += items[i].value;
        } 
        else {
            totalValue += items[i].ratio * remainingCapacity;
            remainingCapacity = 0;
        }
    }
    
    return totalValue;
}


int main() {
    int W = 50; 

    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    
    int n = sizeof(values) / sizeof(values[0]);

    printf("Knapsack Capacity: %d\n", W);

    double maxValue = fractionalKnapsack(W, values, weights, n);

    printf("Maximum value in Knapsack = %.2f\n", maxValue);

    return 0;
}