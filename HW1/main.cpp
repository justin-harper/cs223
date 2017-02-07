// (put your name here)
// (put your ID number here)
// CptS 223 - Advanced Data Structures
// Homework assignment #1

#include <string>
#include <iostream>
#include <fstream>
#include "ReversibleStack.h" // You need to create ReversibleStack.h

void Display(ReversibleStack& rs)
{
	// Implement this function (use only Push, Pop and IsEmpty member functions of stack)
	// After the function completes, the stack should be unmodified (see assignment instructions)
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Missing required argument for input file" << endl;
		return 0;
	}

	ReversibleStack rs;
	ifstream inFile;
	inFile.open(argv[1], ifstream::in);
	if (!inFile.is_open())
	{
		cout << "Could not open: " << argv[1] << endl;
		return 0;
	}

	while (!inFile.eof())
	{
		string line;
		getline(inFile, line);

		// Process the command here
		if (0 == line.compare(0, 6, "header"))
		{
			// Display the header line here, as the instructions describe
		}
		else if (0 == line.compare(0, 7, "display"))
		{
			Display(rs);
			cout << endl;
		}
		// You'll need to implement several other commands in here
		else
		{
			cout << "Unknown command: " << line;
		}
	}

	// Complete
	inFile.close();
	cout << endl << "Done" << endl;
	return 1;
}