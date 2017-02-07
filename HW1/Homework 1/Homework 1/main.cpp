// Justin Harper
// 10696738
// CptS 223 - Advanced Data Structures
// Homework assignment #1



/**********************************************************************************
*																				  *
* Note currently main is set to "parse" the first argument passed into main		  *
*																				  *
**********************************************************************************/



#include <string>
#include <iostream>
#include <fstream>
#include "ReversibleStack.h" // You need to create ReversibleStack.h

using namespace std;

void Display(ReversibleStack& rs)
{
	// Implement this function (use only Push, Pop and IsEmpty member functions of stack)
	// After the function completes, the stack should be unmodified (see assignment instructions)
	
	ReversibleStack tempBackwards;


	while (rs.isEmpty() == false)
	{
		int x = rs.pop();
		tempBackwards.push(x);
		cout << x << " ";
	}
	while (tempBackwards.isEmpty() == false)
	{
		rs.push(tempBackwards.pop());
	}
	cout << endl;

	return;


}


int Push(string text)
{
	int x = 4;
	string temp = "";
	while (text[x] != '\0')
	{
		temp += text[x];
		x++;
	}
	x = stoi(temp);
	return x;
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
			cout << rs.header() << endl;
		}
		else if (0 == line.compare(0, 7, "display"))
		{
			Display(rs);
			
		}
		// You'll need to implement several other commands in here
		else if (0 == line.compare(0, 4, "push"))
		{
			rs.push(Push(line));
		}

		else if (0 == line.compare(0, 7, "reverse"))
		{
			rs.reverse();
		}
		else if (0 == line.compare(0, 3, "pop"))
		{
			rs.pop();
		}
		else if (0 == line.compare(0, 7, "isempty"))
		{
			if (rs.isEmpty())
			{
				cout << "true" << endl;
			}
			else
			{
				cout << "false" << endl;
			}
			
		}

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