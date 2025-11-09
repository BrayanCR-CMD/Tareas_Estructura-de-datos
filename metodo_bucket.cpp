//metodo de ordenamiento bucket sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(vector<int>& arr, int bucketSize = 5) {
    if (arr.empty()) return;

    int minValue = *min_element(arr.begin(), arr.end());
    int maxValue = *max_element(arr.begin(), arr.end());

    int bucketCount = (maxValue - minValue) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);

    for (int num : arr) {
        int bucketIndex = (num - minValue) / bucketSize;
        buckets[bucketIndex].push_back(num);
    }

    arr.clear();
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}

int main() {
    vector<int> arr = {29, 25, 3, 49, 9, 37, 21, 43};
    cout << "arreglo desordenado: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    bucketSort(arr);
    cout << "arreglo ordenado: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    return 0;
}