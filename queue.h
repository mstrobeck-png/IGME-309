#include <iostream>
using namespace std;

template <class queue_class>
class queue
{
	//sizing of array & initalizing other values, k is my placement in array
	int m_size = 10;
	int k = -1;

	//pointer array
	queue_class* values; 

	//incoming values
	queue_class x; 

public:

	queue() {
		values = new queue_class[m_size];
	};

	//copy constructor
	queue(const queue& q) {
		x = q.x;
	}

	//copy assignment operator
	queue& operator=(const queue& other) {
		other.x;
	}

	//settings array size to whatever is being created. In this example it is 3.
	queue(queue_class m_size)
	{
		values = new queue_class[m_size];
	}

	//deconstructor
	~queue()
	{
		delete[] values;
	}

	int pushData(queue_class x)
	{
		//fills in array
		values[++k] = x;
		return x;
	}

	int getSize()
	{
		//finding size of array but adding 1 since arrays typically take in values at the 0 location
		cout << "Size of array is: " << k + 1 << endl; 
		return 0;
	};

	void print()
	{
		//setting up i for location in array
		int i = 0;

		//loops through to locate each value to output
		for (int j = 0; j < values[i]; j++) {  
			cout << values[j] << " ";
		}
		cout << endl;
	}

	void sortValues()
	{
		//to sort values
		cout << "values are being sorted" << endl;
		/*
		for (int j = 0; values[k]; j++) {
			if (values[k] < other.x) {
				return x;
			}
			if (values[k] > other.x) {
				return other.x;
			}
		}
		*/
		
	}
	
	bool isEmpty()
	{
		//by default the array is not full; located here so it can keep being updated as more values are added or removed
		bool full = false;

		//if the array contains anything, it will return full
		if (values[k] > 0) {
			cout << "It contains elements" << endl;  
			return true;
		}

		//if the array does not satisfy the if, then it tells us it is an empty array
		else
		{
			cout << "It is empty." << endl;   
			return false;
		}
	};

	void popping()
	{
		
		if (values[k] > 0) {
			//delete whatever is stored last
			values[k--] = x;
		}
		else {
			//if it equals zero or "null" 
			getSize();
		}

	}

	

};
