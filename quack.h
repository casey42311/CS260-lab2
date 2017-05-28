// you can only change this file by adding variables and/or functions to the "private" section

#pragma once

#include <ostream>
#include <iomanip>

class Quack
{
public:
	static const char	YOUR_NAME[];		// used for printing out programmer's name
	static const bool	PREMIUM_VERSION;	// used to designate Regular vs. Premium

	Quack(int capacity, int growBy = 0);
		// capacity: # of slots in array
		// growBy:   # of slots to add to array when it grows, 0 means "don't grow"
	~Quack(void);
	bool pushFront(const char ch);		// push an item onto the front
	bool pushBack(const char ch);		// push an item onto the back
	bool popFront(char& ch);			// pop an item off the front
	bool popBack(char& ch);				// pop an item off the back
	void rotate(int r);					// "rotate" the stored items (see note below)
	void reverse(void);					// reverse the order of the stored items
	int	itemCount(void);				// return the current number of stored items

	void printArray(std::ostream& out)					// print contents of array
	{
		unsigned int	ch;

		out << "[ ";
		for (int i = 0; i < capacity; i++) {
			ch = static_cast<unsigned char>(items[i]);	// avoid sign extension
			if (ch == '-')								// print in hex, because using '-' for 0xCD
				goto printHex;
			else if (ch >= '!' && ch <= '}')			// ASCII text character
				out << static_cast<char>(ch) << ' ';
			else if (ch == 0xCD)						// print 0xCD as '-'
				out << "- ";
			else										// print everything else as hex
				goto printHex;
			continue;

		printHex:	
			out << std::setw(2) << std::setfill('0') << std::hex << ch << ' ';
			}
		out << ']' << std::endl;
	}

private:
	char	*items;						// pointer to storage for circular array,
										// each item in the array is a char
	int		nItems;						// # of items currently stored in array
	int		capacity;					// # of slots in array
	int		growBy;						// # of slots array will grow by
	int     front;						// first item in the array
	int     back;						// last item in the array

public:
	friend std::ostream& operator<<(std::ostream& out, Quack *q);
};

// The following example should make it clear what "rotate" means.
// This is showing you the "logical contents" of the quack, i.e.
// which item is first, which is second, etc. It is NOT showing you
// where the items are in the array.
//
//   quack: c, b, a, f, g				-- current contents, front is on the left
//   >>> rotate(2)
//   quack: a, f, g, c, b				-- contents after rotation by +2
//   >>> rotate(-3)
//   quack: g, c, b, a, f				-- contents after rotation by -3
