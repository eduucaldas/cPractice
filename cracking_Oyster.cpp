#include <bitset> // in bitsort
#include <vector>
#include <numeric> // in randomVector
#include <random> // in randomVector
#include <iostream>
#include <iterator> // testSmall
#include <chrono> //in testBig
#include <algorithm>

using namespace std;

const unsigned int MAX_VALUE = 2000000;

vector<int> bitsort(vector<int> v){
	/*
	Input: vector with non repeated elements that are in [0, MAX_VALUE[
	Output: bitsorted vector
	Complexity:
		time: MAX_VALUE + c*vector.length
		space: MAX_VALUE*sizeof(bit)
	*/
	bitset<MAX_VALUE> bset;

	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if(bset.test(*it))
			throw string("repeated numbers in input");
		else
			bset.flip(*it);
	}
	vector<int> bitsorted;
	for (int i = 0; i < MAX_VALUE; ++i)
	{
		if(bset.test(i))
			bitsorted.push_back(i);
	}
	return bitsorted;
}

vector<int> randomVector(int n){
	/*
	Input: number of elements in the 
	Output: a vector with n unique random elements in the range [0, MAX_VALUE[
	Complexity:
		time: O(MAX_VALUE)
		space: MAX_VALUE
	How: 
		1-create array [1,2,...,MAX_VALUE[
		2-Fisher-Yates shuffle the array
		3-pick the n first elements
	*/
	srand(time(NULL));
	//1
	int numbers[MAX_VALUE];
	std::iota(numbers, numbers + MAX_VALUE, 0);
	//2
	int tmp;
	for(int i = MAX_VALUE - 1; i > 0; i--){
		tmp = rand() % (i+1);
		swap(numbers[i], numbers[tmp]);
	}
	//3
	return vector<int>(numbers, numbers + n);
}

void testSmall(){
	int n;
	cout << "How many numbers should there be in your test vector? Given that MAX_VALUE = " << MAX_VALUE << endl;
	cin >> n;
	vector<int> v = randomVector(n);
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	v = bitsort(v);
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}

void testBig(int n){
	cout << "MAX_VALUE = " << MAX_VALUE << "\ndata's size = " << n << endl;
	chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	vector<int> v = randomVector(n);
	chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
	cout << "Time for randomVector = " << std::chrono::duration_cast<chrono::microseconds>(end - begin).count() <<endl;
	
	vector<int> bitsorted;
	chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
	bitsorted = bitsort(v);
	chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
	cout << "Time for bitsort = " << std::chrono::duration_cast<chrono::microseconds>(end1 - begin1).count() <<endl;
	
	chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
	sort(v.begin(), v.end());
	chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
	cout << "Time for sort = " << std::chrono::duration_cast<chrono::microseconds>(end2 - begin2).count() <<endl;
	
}

int main(){
	//testSmall();
	int n = MAX_VALUE/10;
	testBig(n);
	return 0;
}