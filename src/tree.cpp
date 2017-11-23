#include "main.h"


using namespace std;


// function for searching from root to leaf node and pushing on to a stack
void BPlusTree :: Search_Path(Node* node, float key, stack<Node*>* path)
{
	// push node to stack
        path->push(node);

	// check if the node pushed to stack is an internal node
	if(!node->Get_IsLeaf())
        {
		// search for the given key in the current node
		vector<float> keys = node->Get_Keys();
		vector<Node*> children = node->Get_Children();
                vector<float>::iterator index = lower_bound(keys.begin(), keys.end(), key);

		// check if key is found
		if(key == keys[index - keys.begin()])
		{
			// recursively repeat by searching the path through the corresponding right child index
                	Search_Path(children[(index - keys.begin()) + 1], key, path);
		}

		// if key is not found
		else
		{
			// recursively repeat by searching the path through the corresponding left child index
			Search_Path(children[index - keys.begin()], key, path);
		}
        }
}


// function to destroy the tree
void BPlusTree :: Destroy(Node* node)
{
	// recursively repeat the function to delete all the nodes level by level, starting with the leaf nodes
	if (!node->Get_IsLeaf())
	{
  	        vector<Node*> children = node->Get_Children();
                for(vector<Node*>::iterator index = children.begin(); index != children.end(); index++)
                {
                        Destroy(*index);
        	}
	}
	delete(node);
}


#ifdef DEBUG
// function to reveal the contents of the B+ tree
void BPlusTree :: Reveal_Tree(Node* node)
{
	// check if tree is empty
        if (NULL == node)
        {
                cout<<endl<<"Root Node: Null";
                return;
        }

	// check if current node is a leaf node
        if(node->Get_IsLeaf())
        {
                cout<<endl<<"Leaf Node: ";
        }

	// if current node is a internal node
        else
        {
                cout<<endl<<"Internal Node: ";
        }

	// display the keys
        vector<float> keys = node->Get_Keys();
        for(vector<float>::iterator index = keys.begin(); index != keys.end(); index++)
        {
                cout<<*index<<" ";
        }
        cout<<endl;

	// check if internal node to continue revelation of the next level
        if (!node->Get_IsLeaf())
        {
		// display the keys in the children of the current internal node
                vector<Node*> children = node->Get_Children();
                cout<<"children"<<endl<<"--------"<<endl;
                for(vector<Node*>::iterator index = children.begin(); index != children.end(); index++)
                {
                        vector<float> childKeys = (*index)->Get_Keys();
                        for(vector<float>::iterator i = childKeys.begin(); i != childKeys.end(); i++)
                        {
                                cout<<*i<<" ";
                        }
                        cout<<endl;
                }

		// recursively repeat revelation of the next level
                for(vector<Node*>::iterator index = children.begin(); index != children.end(); index++)
                {
                        Reveal_Tree(*index);
                }
        }
}
#endif


// operation: Initialize(m)
void BPlusTree :: Initialize(int m)
{
	order = m;
	root = NULL;
}


// operation: Insert(key, value)
void BPlusTree :: Insert(float key, string value)
{
	// check if tree is empty
	if(NULL == root)
	{
		// Irrespective of the order, root is always a leaf node for 
		// the first insertion. So, create a new leaf node.
		root = new LeafNode;
		root->Insert(key, value);
	}

	// if it is a subsequent insertion
	else
	{
		Node* leftNode = NULL;
		Node* rightNode = NULL;
		float* keyToParent = new float;
		bool rootPopped = false;
		
		// obtain the search path from the root to leaf node and push it on to a stack
		stack<Node*>* path = new stack<Node*>;
		Search_Path(root, key, path);

		// insert the key-value pair in the leaf node
		path->top()->Insert(key, value);

		// Split the current node and insert the middle key & children in to the parent. Perform
		// this as long as there is an imbalance in the tree, moving up the stack every iteration.
		while(path->top()->Get_Keys().size() == order)
		{
			// Update the current node as the left half and return the right half. Also 
			// obtain the middle element, which is the key to be moved up to the parent.
			leftNode = path->top();
			rightNode = leftNode->Split(keyToParent);

			// check if currently split node is not the root node
			path->pop();
			if(!path->empty())
			{
				// Insert the middle key and the right half in to 
				// the parent. The parent will be an internal node.
				path->top()->Insert(*keyToParent, rightNode);
			}

			// if currently split node is the root node
			else
			{
				// set flag indicating that the root has popped from the stack
				rootPopped = true;
				break;
			}
		}

		// new internal node needs to be created and assigned as the root
		if(rootPopped)
		{
			// create a new internal node
			InternalNode* tempRoot = new InternalNode;

			// insert the left and the right halves as the children of this new internal node
			tempRoot->Insert(*keyToParent, leftNode, rightNode);

			// mark this new internal node as the root of the tree
			root = tempRoot;
		}

		delete(keyToParent);
		delete(path);
	}
}


// operation: Search(key)
void BPlusTree :: Search(float key)
{
	// check if tree is empty
	if(NULL == root)
	{
		outputFile<<"Null"<<endl;
	}

	// if it is a vaild search
	else
	{
		int i = 0;	
		
		// obtain the search path from root to leaf node and push it on to a stack
		stack<Node*>* path = new stack<Node*>;
		Search_Path(root, key, path);
		
		// search for the key in the leaf node, which is at the top of the stack
		vector<float> keys = path->top()->Get_Keys();
		vector< vector <string> > values = path->top()->Get_Values(); 
		vector<float>::iterator index = lower_bound(keys.begin(), keys.end(), key);

		// check if key is found
		if(key == keys[index - keys.begin()])
		{
			// display the values
			for(i = 0; i < values[index - keys.begin()].size() - 1; i++)
			{
				outputFile<<values[index - keys.begin()][i]<<",";
			}
			outputFile<<values[index - keys.begin()][i]<<endl;
		}

		// if key is not found
		else
		{
			outputFile<<"Null"<<endl;
		}

		delete(path);
	}
}


// operation: Search(key1, key2)
void BPlusTree :: Search(float key1, float key2)
{
	// check if tree is empty
	if(NULL == root)
	{
		outputFile<<"Null"<<endl;
	}

	// if it is a valid range search
	else
	{
		int i = 0;
		bool firstPass = true;
		float firstKey = ERROR;
		
		// obtain the search path from root to leaf node and push it on to a stack
		stack<Node*>* path = new stack<Node*>;
		Search_Path(root, key1, path);
		
		// search for the key in the leaf node, which is at the top of the stack
		vector<float> keys = path->top()->Get_Keys();
		vector< vector <string> > values = path->top()->Get_Values(); 
		Node* next = path->top()->Get_Next();
		vector<float>::iterator index = lower_bound(keys.begin(), keys.end(), key1);

		// display all the keys in the search range, along with their corresponding values
		while(1)
		{
			// check if end of the current leaf node is reached
			if((index - keys.begin()) == keys.size())
			{
 				// go to the next leaf node
				keys = next->Get_Keys();
                		values = next->Get_Values();
                		next = next->Get_Next();
				index = keys.begin();
			}	
			
			// save the smallest key in the given search range
			if(firstPass)
			{	
				firstKey = keys[index - keys.begin()];						
			}


			// check if already iterated through the doubly linked list once
			if(!(firstPass || (keys[index - keys.begin()] != firstKey)))
			{
				// exit the loop
				break;
			}

			// check if key is within the search range
			if((key1 <= keys[index - keys.begin()]) && (keys[index - keys.begin()] <= key2)) 
			{
				if(!firstPass)
				{
					outputFile<<",";
				}

				// display the key and its corresponding values
				for(i = 0; i < values[index - keys.begin()].size() - 1; i++)
				{
					outputFile<<"("<<keys[index - keys.begin()]<<","<<values[index - keys.begin()][i]<<"),";
				}
				outputFile<<"("<<keys[index - keys.begin()]<<","<<values[index - keys.begin()][i]<<")";
			}

			// if key is not within the search range
			else
			{
				// check if atleast one key was in the search range
				if(!firstPass)
				{
					outputFile<<endl;
				}

				// if no keys belonged within the search range
				else
				{
					outputFile<<"Null"<<endl;
				}

				// exit the loop
				break;
			}

			firstPass = false;
			index++;
		}

		delete(path);
	}
}


// function to open the output file
void BPlusTree :: Open_Output_File()
{
	// open output file for writing
	outputFile.open(OUTPUT_FILE, ios::out | ios::trunc);
}


// function to close the output file
void BPlusTree :: Close_Output_File()
{
	// close the output file
	outputFile.close();
}


// destructor for tree
BPlusTree :: ~BPlusTree ()
{
	Destroy(root);
}


#ifdef DEBUG
// function to print the current state of the tree
void BPlusTree :: Print_Tree()
{
	Reveal_Tree(root);
}
#endif
