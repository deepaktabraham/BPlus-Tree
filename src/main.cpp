#include "main.h"


// main function
int main(int argc, char* argv[])
{
	int m = ERROR, pos = ERROR;
	float key = ERROR, key1 = ERROR, key2 = ERROR;
	string line, value;
	class BPlusTree tree;

	// check command-line arguments
	if(NUM_ARGS != argc)
	{
		cout<<"Invalid argument!"<<endl;
		cout<<"Usage: ./treesearch <input_filename>"<<endl;
		exit(-1);
	}

	// check if input file is valid
	ifstream file(argv[1]);
	if(!file)
	{
		cout<<"Invalid input file!"<<endl;
		exit(-1);
	}

	// get the B+ tree order
	getline(file, line);
	try
	{
		m = stoi(line);
	}
	catch(...)
	{
		cout<<"Invalid B+ tree order!"<<endl;
		exit(-1);
	}

	// check if order is atleast 3
	if(m < MIN_ORDER)
	{
		cout<<"Invalid B+ tree order!"<<endl;
		exit(-1);
	}

	// initialize the B+ tree of order m
	tree.Initialize(m);

	// open the output file for writing results
	tree.Open_Output_File();

	// read the input file and perform the corresponding operations
	while (getline(file, line))
	{
		pos   = ERROR;
		key   = ERROR;
		value = ERROR;
		key1  = ERROR;
		key2  = ERROR;

		// operation: Insert(key, value)
		if(0 == line.compare(0, 6, "Insert"))
		{
			pos = line.find(",");
			key = atof(line.substr(7, pos - 7).c_str());
			value = line.substr(pos + 1, line.size() - pos - 2);

			// insert the key-value pair
			tree.Insert(key, value);		
		}

		// if it is a search operation
		else if (0 == line.compare(0, 6, "Search"))
		{
			// operation: Search(key)
			pos = line.find(",");
			if(ERROR == pos)
			{
				key = atof(line.substr(7, line.size() - 8).c_str());

				// search for the key and display the correpsonding value(s)
				tree.Search(key);
			}

			// operation: Search(key1, key2)
			else
			{
				key1 = atof(line.substr(7, pos - 7).c_str());
				key2 = atof(line.substr(pos + 1, line.size() - pos -2).c_str());

				// search for keys between key1 and key2, and display the corresponding value(s)
				tree.Search(key1, key2);	
			}
		}
	}

	// close the output file
	tree.Close_Output_File();

#ifdef DEBUG
	// print the current state of the B+ tree
	tree.Print_Tree();
#endif

	cout<<endl<<"Check "<<OUTPUT_FILE<<" for results!"<<endl<<endl;
}
