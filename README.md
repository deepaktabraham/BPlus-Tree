# B+ Tree
B+ trees are order “m” trees, often with a variable number of children per node. Unlike other such trees, in B+ trees, the internal nodes store only keys, while key-value pairs are stored in the leaf nodes. 

In this project, a C++ implementation of a memory-resident B+ tree is presented. The implementation makes use of the Standard Template Library (STL), but does not use any of the complex data structures provided by it. The design is such that each key can have multiple values associated with it. Also, all leaf nodes are linked together to form a doubly linked list.


### Supported operations:
1. Insert a key-value pair: **`Insert(key,value)`** 
2. Return all values associated with a given key: **`Search(key)`**
3. Return all key value pairs such in a given range: **`Search(key1,key2)`** 


### Expected Input:
The program expects input to be provided in a text file. The first line of this input file should specify the order of the B+ tree. Subsequent lines can have any of the above supported operations,one operation per line. A sample input file is provided (input_file.txt) is provided.


### Commands:
To build the source code: **`make`**<br />
To execute the built binary: **`treesearch <input_file.txt>`**<br />
To clean the repo: **`make clean`**<br />
