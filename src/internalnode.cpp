#include "main.h"


using namespace std;


// constructor for internal node
InternalNode :: InternalNode()
{
	isLeaf = false;
}


// function for insertion in an internal node
void InternalNode :: Insert(float key, Node* rightChild)
{
	// insert key in to suitable position in the given internal node
	vector<float>::iterator index = lower_bound(keys.begin(), keys.end(), key);
	keys.insert(index, key);

	// insert right child in the immediately next index in the children vector
	index = lower_bound(keys.begin(), keys.end(), key);
	children.insert(children.begin() + (index - keys.begin() + 1), rightChild);
}


// function for insertion in a new internal root node
void InternalNode :: Insert(float key, Node* leftChild, Node* rightChild)
{
	// insert key, left child and right child
	keys.push_back(key);
	children.push_back(leftChild);
	children.push_back(rightChild);
}


// function for splitting an internal node
Node* InternalNode :: Split(float* keyToParent)
{
	int length = keys.size();

	// create a new right internal node
	InternalNode* rightNode = new InternalNode;

	// key to be moved up to the parent is the middle element in the current internal node
	*keyToParent = keys[length/2];

	// Copy the second half of the current internal node excluding the middle element to the 
	// new right internal node. Erase the second half of the current internal node including 
	// the middle element, and thus current internal node becomes the left internal node.
	rightNode->keys.assign(keys.begin() + (length/2 + 1), keys.end());
	rightNode->children.assign(children.begin() + (length/2 + 1), children.end());
	keys.erase(keys.begin() + length/2, keys.end());
	children.erase(children.begin() + (length/2 + 1), children.end());

	// return the new right internal node
	return rightNode;
}


// getter function for accessing children
vector<Node*> InternalNode :: Get_Children()
{
	// return the children vector
	return children;
}
