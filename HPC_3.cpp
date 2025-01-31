#include <iostream>
#include <vector>
#include <omp.h>
#include <climits> // For INT_MAX, INT_MIN

using namespace std;

int main() {
    vector<int> numbers = {10, 20, 5, 8, 35, 15};

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int sum_val = 0;
     
    for(int n:numbers)
    {
      cout<<n<<" ";
    }
    cout<<"\n";
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum_val)
    for (int i = 0; i < numbers.size(); i++) {
        min_val = min(min_val, numbers[i]);
        max_val = max(max_val, numbers[i]);
        sum_val += numbers[i];
    }

    double avg_val = static_cast<double>(sum_val) / numbers.size();
    
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Sum: " << sum_val << endl;
    cout << "Average: " << avg_val << endl;

    return 0;
}
