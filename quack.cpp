// add code to these functions to make Quack do something useful

#include "memoryleakdetect.h"		// this must be the first #include in each of your .cpp files
#include "quack.h"

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	Quack::YOUR_NAME[]("Casey Benson");

// change the value of this variable to true if you're doing the Premium version
const bool	Quack::PREMIUM_VERSION(true);

Quack::Quack(int capacity, int growBy) :
	capacity(capacity),
	growBy(growBy),
	nItems(0),
	items(new char[capacity]),
	front(capacity),
	back(capacity)
{
}

Quack::~Quack(void)
{
	delete[] items;
}

// items are pushed to successively LOWER slots in the circular array
// (except for when the beginning of the array "wraps around" to the end)
bool Quack::pushFront(const char ch)
{
	//If the array is full
	if (nItems >= capacity)
	{
		char *grow;
		int i(0);
		int j(0);

		//grow will replace existing array of items
		grow = new char[capacity + growBy];

		//copy current array into grow
		for (i = front; i != back; i++, j++)
		{
			if (i > capacity - 1)
				i = 0;
			grow[j] = items[i];
		}
		grow[j] = items[i];

		back = j;

		if (front != 0)
			front = capacity + growBy;

		delete[] items;

		items = grow;

		//"grow" the capacity
		capacity = capacity + growBy;
	}

	if (nItems == 0)
	{
		items[nItems] = ch;
		back = 0;
		nItems++;
		return true;
	}
	else if (nItems > 0)
	{
		front--;
		if (front < 0)
			front = capacity - 1;
		items[front] = ch;
		nItems++;
		return true;
	}

	return false;
}

// items are pushed to successively HIGHER slots in the circular array
// (except for when the end of the array "wraps around" to the beginning)
bool Quack::pushBack(const char ch)
{
	//If the array is full
	if (nItems >= capacity)
	{
		char *grow;
		int i(0);
		int j(0);

		//grow will replace existing array of items
		grow = new char[capacity + growBy];

		//copy current array into grow
		for (i = front; i != back; i++, j++)
		{
			if (i > capacity - 1)
				i = 0;
			grow[j] = items[i];
		}
		grow[j] = items[i];

		back = j;

		if (front != 0)
			front = capacity + growBy;

		delete[] items;

		items = grow;

		//"grow" the capacity
		capacity = capacity + growBy;
	}

	if (nItems == 0)
	{
		items[0] = ch;
		back = 0;
		front = 0;
		nItems++;
		return true;
	}
	else if (nItems > 0)
	{
		back++;
		if(back >= capacity)
			back = 0;
		items[back] = ch;
		nItems++;
		return true;
	}
	
	return false;
}

bool Quack::popFront(char& ch)
{
	//check if empty
	if (nItems == 0)
		return false;

	ch = items[front++];

	if (front >= capacity)
		front = front - capacity;

	nItems--;
	return true;
}

bool Quack::popBack(char& ch)
{
	//check if empty
	if (nItems == 0)
		return false;

	ch = items[back--];

	if (back < 0)
		back = capacity - 1;

	nItems--;
	return true;
}

void Quack::rotate(int r)
{
	// Avoids extra rotations if r > nItems
	//Ex: If r is 10 and nItems is 7, rotate 3 instead of 10 to get the same result.
	if (r > nItems)
		r = r % nItems;

	//If r is greater than half the value of nItems
	//if (r > nItems / 2)
	//	r = r - nItems;

	//If number to be rotated by is positive
	if (r > 0)
	{
		for (int i = 1; i <= r; i++)
		{
			//popFront
			char ch = items[front];
			front = (front + 1) % capacity;

			//pushBack
			back = (back + 1) % capacity;
			items[back] = ch;
		}
	}
	else //If number to be rotated by is negative
	{
		for (int i = 1; i <= (r*-1); i++)
		{
			//popBack
			char ch = items[back];
			back = (back - 1) % capacity;

			//pushFront
			front = (front - 1) % capacity;
			if (front < 0)
				front = front + capacity;
			items[front] = ch;
		}
	}
}

void Quack::reverse(void)
{
	char ch;
	int f;
	int b;

	for (f = 0, b = nItems; f < nItems / 2; f++, b--)
	{
		ch = items[f];
		items[f] = items[b];
		items[b] = ch;
	}
}

int	Quack::itemCount(void)
{
	return nItems;
}

ostream& operator<<(ostream& out, Quack *q)
{
	int x(q->front);
	int y(q->back);

	//no items in the array
	if (q->nItems == 0)
	{
		out << "quack: empty" << endl << endl;
		return out;
	}

	out << "quack: ";

	while (x != y)
	{
		out << q->items[x] << ", ";
		x++;
		if (x > q->capacity - 1)
			x = 0;
	}

	out << q->items[x] << endl << endl;

	// returning out is ALWAYS required for an operator<< overload
	return out;
}
