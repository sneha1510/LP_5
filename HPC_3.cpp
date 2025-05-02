#include<omp.h>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    cout<<"Enter total no: ";
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
    {
        cout<<"Enter "<<(i+1)<<" element: ";
        cin>>arr[i];
    }
    cout<<"You have entered: ";
    for(int i:arr)
        cout<<i<<" ";

    cout<<endl;
    int max_val=arr[0],min_val=arr[0],sum=0;
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for(int i=0;i<arr.size();i++)
    {
        min_val=min(min_val,arr[i]);
        max_val=max(max_val,arr[i]);
        sum+=arr[i];
    }
    double avg=static_cast<double>(sum)/arr.size();
    cout<<"Min value: "<<min_val<<endl;
    cout<<"Max value: "<<max_val<<endl;
    cout<<"Sum: "<<sum<<endl;
    cout<<"avg: "<<avg<<endl;

    return 0;
}
