#include<iostream>
#include <functional>
#include <string>
using namespace std;

class HashNode
{
private:
	string key = "-";
	string value = "-";
	int DFB = -1;
public:
	HashNode() {}
	HashNode(string key, string value) : value(value), key(key), DFB(0) {}
	int plusDFB() { return ++DFB; }
	int minusDFB() { return --DFB; }
	int getDFB() { return DFB; }
	string getValue() { return value; }
	string getKey() { return key; }
	void showNode() { cout << "key = " << key << ", value = " << value << ", DFB = " << DFB << endl;; }
};


class HashTable
{
private:
	HashNode** arr;
	int capacity = 0;
	int size = 0;
public:

	HashTable(int size) : capacity(size * 2)
	{
		arr = new HashNode * [capacity];
		HashNode* tmp = new HashNode;

		for (int i = 0; i < capacity; i++)
			arr[i] = tmp;
	}

	void insertNode(string key, string value)
	{
		size++;
		if (size > capacity)
		{
			IncreaseCapacity();
		}

		HashNode* cur = new HashNode(key, value);
		HashNode* tmp = new HashNode;
		int hashIndex = HashFunc(key);

		if (arr[hashIndex]->getDFB() == -1)
		{
			arr[hashIndex] = cur;
		}
		else
		{
			cur->plusDFB();
			for (int i = hashIndex + 1; i < size + 1; ++i)
			{
				if (arr[i]->getDFB() == -1)
				{
					arr[i] = cur;
					break;
				}

				if (arr[i]->getDFB() >= cur->getDFB())
				{
					cur->plusDFB();
					continue;
				}
				else
				{
					tmp = arr[i];
					arr[i] = cur;
					cur = tmp;
					cur->plusDFB();
				}
			}
		}
	}

	void IncreaseCapacity()
	{
		HashNode* tmp = new HashNode;

		HashNode** tmp_arr = new HashNode * [size - 1];
		int tmp_size = size - 1;

		for (int i = 0; i < tmp_size; ++i)
		{
			tmp_arr[i] = arr[i];
		}

		delete[] arr;

		capacity = size * 2;
		arr = new HashNode * [capacity];

		for (int i = 0; i < capacity; i++)
			arr[i] = tmp;

		for (int i = 0; i < tmp_size; ++i)
		{
			this->insertNode(tmp_arr[i]->getKey(), tmp_arr[i]->getValue());
		}
	}

	void deleteNode(string key)
	{
		int hashIndex = HashFunc(key);
		int cur_DFB = 0;
		int FLAG = 0;
		HashNode* tmp = new HashNode;

		while (arr[hashIndex]->getDFB() >= cur_DFB)
		{
			if (arr[hashIndex]->getKey() == key)
			{
				cout << endl << "Element with key = " << key << " and value = " << arr[hashIndex]->getValue() << " was deleted!" << endl;
				arr[hashIndex] = tmp;
				FLAG = 1;
			}

			hashIndex++;
			cur_DFB++;
		}

		if (!FLAG)
		{
			cout << endl << "Element with key = " << key << " was not found for deleting!" << endl;
			return;
		}

		while (arr[hashIndex]->getDFB() != 0 && arr[hashIndex]->getDFB() != -1)
		{
			arr[hashIndex - 1] = arr[hashIndex];
			arr[hashIndex - 1]->minusDFB();
			hashIndex++;
		}
		arr[hashIndex - 1] = tmp;
	}

	string getValue(string key)
	{
		int hashIndex = HashFunc(key);
		int cur_DFB = 0;


		while (arr[hashIndex]->getDFB() >= cur_DFB)
		{
			if (arr[hashIndex]->getKey() == key)
			{
				cout << "Element with key = " << key << " and value = " << arr[hashIndex]->getValue() << " was found!" << endl;
				return arr[hashIndex]->getValue();
			}

			hashIndex++;
			cur_DFB++;
		}

		cout << "Element with key = " << key << " was not found" << endl;
		return "";
	}

	int HashFunc(string key)
	{
		int tmp = 0;

		for (int i = 0; i < key.length(); ++i)
			tmp += (int)key[i];

		return tmp % capacity;
	}

	void showHashTable()
	{
		cout << "HashTable:" << endl;;
		for (int i = 0; i < capacity; ++i)
		{
			cout << arr[i]->getKey() << "\t" << arr[i]->getValue() << "\t [" <<
				arr[i]->getDFB() << "]" << endl;
		}
	}

	int getCapacity() { return capacity; }
	int getSize() { return size; }

	~HashTable() { delete [] arr; }
};


int main()
{
	cout << "=======================Example 1=======================" << endl;

	HashTable Tab1(10);
	Tab1.insertNode("P", "value1");
	Tab1.insertNode("Q", "value2");
	Tab1.insertNode("d", "value3");
	Tab1.insertNode("e", "value4");
	Tab1.insertNode("x", "value5");
	Tab1.showHashTable();
	cout << endl << endl;

	string find1 = Tab1.getValue("x");
	cout << find1 << endl;
	string find2 = Tab1.getValue("T");
	cout << find2 << endl;
	string find3 = Tab1.getValue("(");
	cout << find3 << endl;

	Tab1.deleteNode("T");
	Tab1.deleteNode("x");
	cout << endl;
	Tab1.showHashTable();

	cout << endl << endl;
	cout << "=======================Example 2=======================" << endl;

	HashTable Tab2(1);
	Tab2.insertNode("P", "value1");
	Tab2.insertNode("Q", "value2");
	Tab2.showHashTable();

	cout << endl;
	Tab2.insertNode("b", "value3");
	Tab2.showHashTable();

	return 0;
}