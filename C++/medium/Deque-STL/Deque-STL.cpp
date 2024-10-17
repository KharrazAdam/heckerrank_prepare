#include <iostream>
#include <deque> 
using namespace std;

int find_max(deque<int> &deq) {
	int max = 0;
	for (size_t i = 1; i < deq.size(); i++)
		max = max > deq[i] ? max : deq[i];
	return max;
}

void printKMax(int arr[], int n, int k){
	deque<int>	mydeque;
	int			max = 0;

	for (size_t i = 0; i < k; i++)
	{
		mydeque.push_back(arr[i]);
		max = max > arr[i] ? max : arr[i];
	}
	cout << max;
	for (size_t i = k; i < n; i++) {
		max == mydeque.front() ? max = find_max(mydeque): false;
		mydeque.pop_front();
		mydeque.push_back(arr[i]);
		max = max > arr[i] ? max : arr[i];
		cout << ' ' << max;
	}
	cout << endl;
}

int main(){
  
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
    	cin >> n >> k;
    	int i;
    	int arr[n];
    	for(i=0;i<n;i++)
      		cin >> arr[i];
    	printKMax(arr, n, k);
    	t--;
  	}
  	return 0;
}