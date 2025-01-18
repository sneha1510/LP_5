#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;
using namespace chrono;

const int THRESHOLD = 1000; // Threshold for switching to sequential sort

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1, n2 = high - mid;
    int left[n1], right[n2];

    for (int i = 0; i < n1; i++) left[i] = arr[low + i];
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];

    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (high - low <= THRESHOLD) {
        mergeSort(arr, low, high); // Use sequential merge sort for small sizes
        return;
    }

    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }
        merge(arr, low, mid, high);
    }
}

int main() {
    const int n = 1000000; // Increased array size for better parallelization benefits
    int arr[n];
    
    cout<<"Main method started";

    // Initialize array with random values
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;

    // Sequential merge sort
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();
    cout << "Sequential time: " << duration_cast<microseconds>(end - start).count() / 1e6 << " seconds\n";

    // Reinitialize array for parallel sort
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;

    // Set number of threads for OpenMP
    omp_set_num_threads(4); // Adjust based on your CPU cores

    // Parallel merge sort
    start = high_resolution_clock::now();
    parallelMergeSort(arr, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "Parallel time: " << duration_cast<microseconds>(end - start).count() / 1e6 << " seconds\n";

    return 0;
}
