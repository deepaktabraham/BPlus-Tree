# B+ Tree
B+ Trees are order “m” trees, often with variable number of children per node. Unlike other such trees, in B+ trees, the internal nodes store keys only, while key-value pairs are stored in the leaf nodes. 

In this project, a C++ implementation of a memory-resident B+ tree is presented. The implementation makes use of the Standard Template Library (STL), but does not use any of the complex data structures provided by it. The design is such that each key can have multiple values associated with it. The implementation supports operations such as insertion of key-value pair, key based search, and range search to display all key-value pairs in the given range of keys.
