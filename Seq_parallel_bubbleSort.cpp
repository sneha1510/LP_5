#include<iostream>
#include<chrono>
#include<omp.h>
using namespace std;
using namespace chrono;

void ParallelBubbleSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void SequentialBubbleSort(int arr[],int n)
{
  for(int i=0;i<n-1;i++)
  {
    for(int j=0;j<n-i-1;j++)
    {
      if(arr[j]>arr[j+1])
        swap(arr[j],arr[j+1]);
    }
  }
}
int main()
{
  int n=10000;
  int arr[n];
  //for SequentialBubbleSort
  //set random values to array
  for(int i=0;i<n;i++)
  {
    arr[i]=rand()%10000;
  }
  auto start1=high_resolution_clock::now();
  SequentialBubbleSort(arr,n);
  auto end1=high_resolution_clock::now();
  auto duration1=duration_cast<milliseconds>(end1-start1);
  cout<<"Time taken by SequentialBubbleSort: "<<duration1.count()<<" milisec"<<"\n";


  //for ParallelBubbleSort
  //set random values to array
  for(int i=0;i<n;i++)
    arr[i]=rand()%10000;

  omp_set_num_threads(8);  // Set number of threads for parallelization

  auto start=high_resolution_clock::now();
  ParallelBubbleSort(arr,n);
  auto end=high_resolution_clock::now();
  auto duration=duration_cast<milliseconds>(end-start);
  cout<<"Time taken by ParallelBubbleSort: "<<duration.count()<<" milisec"<<" ";
  return 0;
}
