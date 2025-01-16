#include<iostream>
#include<chrono>
#include<omp.h>
using namespace std;
using namespace chrono;
void ParallelBubbleSort(int arr[],int n)
{
  bool sorted=false;
  while(!sorted)
  {
    sorted=true;
    //for even indices
    #pragma omp parallel for
    {
      for(int i=0;i<n-1;i+=2)
      {
        if(arr[i]>arr[i+1])
        {
          swap(arr[i],arr[i+1]);
          sorted=false;
        }
      }
    }
    //for odd indices
    #pragma omp parallel for
    {
      for(int i=1;i<n-1;i+=2)
      {
        if(arr[i]>arr[i+1])
        {
          swap(arr[i],arr[i+1]);
          sorted=false;
        }
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
  auto duration1=duration_cast<microseconds>(end1-start1);
  cout<<"Time taken by SequentialBubbleSort: "<<duration1.count()/10000.0<<"\n";
  
  
  //for ParallelBubbleSort
  //set random values to array
  for(int i=0;i<n;i++)
    arr[i]=rand()%10000;
  auto start=high_resolution_clock::now();
  ParallelBubbleSort(arr,n);
  auto end=high_resolution_clock::now();
  auto duration=duration_cast<microseconds>(end-start);
  cout<<"Time taken by ParallelBubbleSort: "<<duration.count()/10000.0<<" ";
  return 0;
}