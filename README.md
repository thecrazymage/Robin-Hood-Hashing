# Robin Hood hashing implementation in C++ #

## Code run ##

```bash
g++ main.cpp -o main.exe
.\main.exe
```

## Code review ##

Data item class **HashNode**:
   1. Consists of:
      * string "key" - by default "-";
      * string "value" - by default "-";
      * variable DFB -  a **D**istance **F**rom expected **B**ucket - by default (-1).
   2. For the HashNode class, the following have been implemented:
      * two constructors - by default and with the parameters "key" and "value";
      * method plusDFB() - to add one to the DFB variable;
      * method minusDFB() - to subtract one from the DFB variable;
      * method getDFB() - to obtain the value of the DFB variable;
      * method getValue() - to get the string "value";
      * method getKey() - to get the string "key";
      * method showNode() - to output values of the HashNode class fields;

Main class **HashTable**:
   1. Consists of:
      * variable arr - array of pointers to objects of class HashNode;
      * variable size - current number of elements in "arr" - by default 0;
      * variable capacity - maximum possible number of elements in "arr" - by default 0, always twice as big as the variable "size".
   2. For the HashTable class, the following have been implemented:
      * constructor with the parameter "size", which defines the variable "capacity";
      * method insertNode() - to add an element to the hash table;
      * method IncreaseCapacity() - to increase the variable "capacity", is used in the insertNode() method if variable "size" becomes larger than the "capacity";
      * method deleteNode() - to remove an element from the hash table;
      * method getValue() - to get the value from the key;
      * method HashFunc() - for key coding;  
        This method converts the string "key" character by character to the integer value according to the ASCII table, takes the sum of the received values and takes the value modulo "capacity".
      * method showHashTable() - to output the hash table;
      * method getCapacity() - to get the value of the variable "capacity";
      * method getSize() -  to get the value of the variable "size";
      * destructor - to free memory allocated in the constructor.

## Analysis of implemented examples ##

### Example 1 ###

Let's create a class object for 10 elements($\Rightarrow$ size = 10, capacity = 20) and add 5 elements.
| Element | ASCII code | Code % capacity (this is the number of the element in the array "arr", respectively) |
|:-------:|:----------:|:------------------------------------------------------------------------------------:|
|    P    |     80     |                                           0                                          |
|    Q    |     81     |                                           1                                          |
|    d    |    100     |                                           0                                          |
|    e    |    101     |                                           1                                          |
|    x    |    120     |                                           0                                          |

The following hash table should be obtained by adding the elements in turn:
| key |  value |  DFB  |
|:---:|:------:|:-----:|
|  P  | value1 | \[0\] |
|  d  | value3 | \[1\] |
|  x  | value5 | \[2\] |
|  e  | value4 | \[2\] |
|  Q  | value2 | \[3\] |
|  -  |    -   | \[-1\]|
| ... |   ...  |  ...  |
|  -  |    -   | \[-1\]|

Next, we find the value of the element with key = "x" and do not find the value of the elements with key = "T", "(" (we look for and do not find **two** elements, since the search for them is slightly different).
| Element | ASCII code | Code % capacity |
|:-------:|:----------:|:---------------:|
|    T    |     84     |        4        |
|    (    |     40     |        0        |

Next, let's try to delete a non-existent element in the table - "T", and then delete the existing "x".
After deletion, the table should change and become:
| key |  value |  DFB  |
|:---:|:------:|:-----:|
|  P  | value1 | \[0\] |
|  d  | value3 | \[1\] |
|  e  | value4 | \[1\] |
|  Q  | value2 | \[2\] |
|  -  |    -   | \[-1\]|
| ... |   ...  |  ...  |
|  -  |    -   | \[-1\]|

### Example 2 ###

Let's try to add an element to the table, in which when the element is added, "size" will become larger than "capacity".
Let's create a class object for 1 element($\Rightarrow$ size = 1, capacity = 2)
| Element | ASCII code | Code % capacity |
|:-------:|:----------:|:---------------:|
|    P    |     80     |        0        |
|    Q    |     81     |        1        |

Elements "P" and "Q" are safely added, the hash table should look like this:
| key |  value |  DFB  |
|:---:|:------:|:-----:|
|  P  | value1 | \[0\] |
|  d  | value3 | \[0\] |

Let's add the "b" element. There is not enough space for "b", so the IncreaseCapacity() method starts its work and the hash table changes.
Now: size = 3, capacity = 6.
| Element | ASCII code | Code % capacity |
|:-------:|:----------:|:---------------:|
|    P    |     80     |        2        |
|    Q    |     81     |        3        |
|    b    |     98     |        2        |

The hash table should now look like this:
| key |  value |  DFB  |
|:---:|:------:|:-----:|
|  -  |    -   | \[-1\]|
|  -  |    -   | \[-1\]|
|  P  | value1 | \[0\] |
|  b  | value3 | \[1\] |
|  Q  | value2 | \[1\] |
|  -  |    -   | \[-1\]|