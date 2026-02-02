#include <bits/stdc++.h>
using namespace std;

void dijkstraPrimes(int limit) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
   
    cout << 2 << " ";
    minHeap.push({4, 2});

    for (int number = 3; number <= limit; number++) {
        if (number < minHeap.top().first) {
            cout << number << " ";
            minHeap.push({number * number, number});
        } else {

            while (number == minHeap.top().first) {
                pair<int, int> topPair = minHeap.top();
                minHeap.pop();
                minHeap.push({topPair.first + topPair.second, topPair.second});
            }
        }
    }
    cout << endl;
}

int main() {
    dijkstraPrimes(10000);
    return 0;
}
