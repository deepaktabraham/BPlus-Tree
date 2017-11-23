#include "main.h"


using namespace std;


// getter function for accessing isLeaf
bool Node :: Get_IsLeaf()
{
	// return whether leaf or internal node
	return isLeaf;
}


// getter function for accessing keys
vector<float> Node :: Get_Keys()
{
	// return the vector of keys
	return keys;
}
