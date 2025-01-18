#include <iostream>
#include <chrono>
#include <omp.h>
#include <algorithm>  // For std::merge

using namespace std;
using namespace chrono;

// Sequential merge sort function
void sequentialMergeSort(int arr[], int left, int right) {
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        // Allocate temp array on the heap
        int* temp = new int[right - left + 1];
        merge(arr + left, arr + mid + 1, arr + mid + 1, arr + right + 1, temp);
        for (int i = 0; i < (right - left + 1); ++i) {
            arr[left + i] = temp[i];
        }
        delete[] temp;  // Free the memory
    }
}

// Parallel merge sort function
void parallelMergeSort(int arr[], int left, int right, int threshold = 10000) {
    if (right - left < threshold) {
        sequentialMergeSort(arr, left, right);
    } else {
        if (left < right) {
            int mid = left + (right - left) / 2;

            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, left, mid, threshold);

                #pragma omp section
                parallelMergeSort(arr, mid + 1, right, threshold);
            }

            // Allocate temp array on the heap
            int* temp = new int[right - left + 1];
            merge(arr + left, arr + mid + 1, arr + mid + 1, arr + right + 1, temp);
            for (int i = 0; i < (right - left + 1); ++i) {
                arr[left + i] = temp[i];
            }
            delete[] temp;  // Free the memory
        }
    }
}

int main() {
    // Generate a large random array
    int n = 1000000;
    int* arr = new int[n];  // Allocate large array on the heap
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // Random numbers between 0 and 999
    }

    // Measure time for sequential merge sort
    auto start = high_resolution_clock::now();
    sequentialMergeSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken for sequential merge sort: " << duration.count() << " milliseconds" << endl;

    // Reset the array to an unsorted state
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // Random numbers again
    }

    // Measure time for parallel merge sort
    omp_set_num_threads(8);  // Set number of threads for parallelization

    start = high_resolution_clock::now();
    parallelMergeSort(arr, 0, n - 1);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken for parallel merge sort: " << duration.count() << " milliseconds" << endl;

    delete[] arr;  // Free the main array memory
    return 0;
}
