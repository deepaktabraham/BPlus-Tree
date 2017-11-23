#include "main.h"


using namespace std;


// constructor for leaf node
LeafNode :: LeafNode()
{	
	isLeaf = true;
	prev = this;
	next = this;
}


// function for insertion in a leaf node
void LeafNode :: Insert(float key, string value)
{
	// search for the key in the given leaf node
	vector<float>::iterator index = lower_bound(keys.begin(), keys.end(), key);

	// check if inserting a duplicate value for an existing key
	if((0 != keys.size()) && (key == keys[index - keys.begin()]))
	{
		// add the duplicate value for the given key
		values[index - keys.begin()].push_back(value);
	}

	// if inserting a new key and value
	else
	{
		// insert the new key
		keys.insert(index, key);

		//insert the corresponding value
		vector<string> newValue;
		newValue.push_back(value);
		index = lower_bound(keys.begin(), keys.end(), key);	
		values.insert(values.begin() + (index - keys.begin()), newValue);
	}
}


// function for splitting a leaf node
Node* LeafNode :: Split(float* keyToParent)
{
	// create a new right leaf node
	LeafNode* rightNode = new LeafNode;

	// key to be moved up to the parent is the middle element in the current leaf node
	*keyToParent = keys[keys.size()/2];

	// Copy the second half of the current leaf node to the new right leaf node. Erase the second
	// half of the current leaf node, and thus the current leaf node becomes the left leaf node.
	rightNode->keys.assign(keys.begin() + keys.size()/2, keys.end());
	rightNode->values.assign(values.begin() + values.size()/2, values.end());
	keys.erase(keys.begin() + keys.size()/2, keys.end());
	values.erase(values.begin() + values.size()/2, values.end());

	// link the leaf nodes to form a doubly linked list
	rightNode->next = next;
	rightNode->prev = this;
	next = rightNode;
	(rightNode->next)->prev = rightNode;

	// return the right leaf node
	return rightNode;
}


// getter function for accessing values
vector< vector <string> > LeafNode :: Get_Values()
{
	// return the vector of values
	return values;
}


// getter function for accessing the next pointer
Node* LeafNode :: Get_Next()
{
	// return the pointer to the next leaf node
	return next;
}
