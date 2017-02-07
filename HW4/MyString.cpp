//Justin Harper
//WSU ID: 10696738

// Cpt S 223 Homework 4 - MyString class


#include "MyString.h"

using namespace std;

MyString::MyString()
{
    // Make an empty string. Note that this is different from a NULL string.
	m_str = new char[1];
	m_str[0] = 0;
	m_length = 0;
}

//this is the constructor that split calls
MyString::MyString(const char* str)
{
    // Special case for a null string
	if (!str)
	{
		m_str = new char[1];
		m_str[0] = 0;
		return;
	}
	
	int len = Length(str);    
    m_str = new char[len + 1];
    Copy(m_str, str, len + 1);
	m_length = len;
}

MyString::MyString(const char* str, bool mine)
{
	if (!str)
	{
		m_str = new char[1];
		m_str[0] = '\0';
		return;
	}
	int len = Length(str);
	m_length = len;
	m_str = new char[len + 1]; //plus 1 for null terminator


	int i = 0;
	while (i < len)
	{
		m_str[i] = str[i];
		if (m_str == '\0')
		{
			break;
		}
		
		i++;
	}
	m_str[i] = '\0';


}


// This is a private constructor that assumes both parameters are valid, 
// thus there isn't any error checking done on these parameters.
MyString::MyString(const char* str, int charCount)
{
	m_str = new char[charCount + 1];
	Copy(m_str, str, charCount);
	m_str[charCount] = 0;
	m_length = charCount;
}

MyString::~MyString()
{
    if (m_str)
	{
		delete[]  m_str;
		m_str = NULL;
	}
#if defined(DEBUG) || defined(_DEBUG)
	else
	{
		std::cout << "DEBUG: WARNING, destructor called when m_str is NULL!" << std::endl;
	}
#endif
}

//copy constructor?...seems to work
MyString::MyString(const MyString& other)
{
	int l = other.Length();
	m_str = new char[l + 1];
	Copy(m_str, other.m_str, l);
	m_str[l] = '\0';
	m_length = l;

}




// Compares the desired number of characters in two strings and returns true if
// they are all equal. If the null-terminator on either string is encountered
// before the desired number of characters have been compared, then false
// will be returned.
bool MyString::AreEqual(const char* str1, const char* str2, int numCharsToCompare)
{
    while (numCharsToCompare--)
    {
        if (!str1[0])
        {
            return (0 == str2[0] && 0 == numCharsToCompare);
        }
        
        if (str1[0] != str2[0])
        {
            return false;
        }
        
        str1++;
        str2++;
    }
    
    // Coming here means we compared the desired number of characters
    // and didn't encounter a mismatch, so we return true.
    return true;
}

// Copies the specified number of characters from the source to destination. 
// No null terminators are used for anything. The specified number of characters 
// will be copied exactly and this could potentially go past a null terminator.
void MyString::Copy(char* destination, const char* source, int count)
{
	while (count--)
	{
		*destination++ = *source++;
	}
}

int MyString::GetAnagrams(vector<MyString>& candidates, vector<MyString>& output)
{
    // You must implement this function
	// Return the number of strings that you add to the output vector
	bool* table1 = makeTable();
	for (int i = 0; i < m_length; i++)
	{
		table1[m_str[i]] = true;
	}
	int times = candidates.size();
	int count = 0;
	
	for (int i = 0; i < times; i++)
	{
		bool* table2 = makeTable();
		for (int j = 0; j < candidates[i].m_str[j]; j++)
		{
			table2[candidates[i].m_str[j]] = true;
		}
		if (equalTables(table1, table2) && m_length == candidates[i].m_length)
		{
			count++;
			output.push_back(candidates[i]);
		}

	}
	
	return count;
}


bool* MyString::makeTable(void) const
{
	bool* table = new bool[256];
	memset(table, false, 256);
	return table;
}

//returns true if tables t1 and t2 have equal
//entires...note this is desinged to work with
//two bool tables of length 256
bool MyString::equalTables(bool* t1, bool* t2)
{

	for (int i = 0; i < 256; i++)
	{
		//no need to keep checking
		if (t1[i] != t2[i])
		{
			return false;
		}
	}

	//every value must be equal
	return true;

}


//returns the index of charcitor c if it exits in the string
//if not it returns -1
int MyString::IndexOf(char c, int startIndex) const
{
    // Implement this function
	// Start the search for the character at the specified index
	// Return the index of the character if it is found, -1 if it isn't
	int index = -1;
	
	for (int i = 0; m_str[i] != '\0'; i++)
	{
		if (m_str[i] == c)
		{
			index = i;
			break;
		}
	}

	return index;

}

int MyString::IndexOf(const char* str, int startIndex) const
{

	//not working ;(


	// Implement this function
	// Start the search for the string at the specified index
	// Return the starting index of the string if it is found, -1 if it isn't
	//this is a default string
	//is
	int len = Length(str);
	switch (len)
	{
	case 0: return -1;
		break;
	case 1: return IndexOf(str[0], startIndex);
		break;
	default:
		return mySearch(str, startIndex, len);
	}


	return -1;
}



//returns index of "needle" within "haystack" or -1 if it does not exist
//note this function does not change the strings
int MyString::boyermoore (const unsigned char* haystack, int hlen, const unsigned char* needle, int nlen) const
{
	int scan = 0;
	int haystackLength = hlen;
	int bad_char_skip[256 + 1]; 

	int foundIndex = -1;

	//parameter validation...just in case
	if (nlen <= 0 || !haystack || !needle)
	{
		return foundIndex;
	}

	
	// Initialize the table to default value 
	// used for skip ahead
	
	for (scan = 0; scan <= 256; scan = scan + 1)
	{
		bad_char_skip[scan] = nlen;
	}

	
	int last = nlen - 1;

	//now fill table with values from needle
	for (scan = 0; scan < last; scan = scan + 1)
	{
		bad_char_skip[needle[scan]] = last - scan;
	}

	

	// Search the haystack, while the needle can still be within it
	while (hlen >= nlen)
	{
		// scan from the end of the needle
		// Note scanning from right to left
		for (scan = last; haystack[scan] == needle[scan]; scan = scan - 1)
		{
			if (0== scan) /* If the first byte matches, we've found it. */
			{
				//found a match so return the index of the first charictor
				foundIndex = haystackLength - hlen;
				return foundIndex;
				
			}
		}
		// other wise skip ahead and search again...skip value is based
		//on table values

		
		hlen -= bad_char_skip[haystack[last]];
		haystack += bad_char_skip[haystack[last]];
	}
	
	// we didn't find it so return unmoddified foundIndex(-1)
	return foundIndex;
}


//helper function used to make sure parameters are right for boyermoore
int MyString::mySearch(const char* str, int startIndex, int strLength) const
{
	
	return  boyermoore((unsigned char*)m_str, m_length,(unsigned char*)str, strLength);

}


int MyString::Length() const
{
    return Length(m_str);
}

int MyString::Length(const char* str)
{
    int len = 0;
    while (*str++)
    {
        len++;
    }
    return len;
}

// Sets the string to a new string value. This is the kind of function 
// that only a mutable string class would have.
void MyString::Set(const char* str)
{
	// First delete the old string
	if (m_str)
	{
		delete [] m_str;
	}

	if (str)
	{
		int len = Length(str);    
		m_str = new char[len + 1];
		char* dst = m_str;
		while (*dst++ = *str++);
	}
	else
	{
		m_str = new char[1];
		m_str[0] = 0;
	}
}

void MyString::Split(char c, std::vector<MyString>& outputVector) const
{
	// You must implement the split function
	// Examples:
	// 1. If the string is "This is a string" then Split(' ') adds 4 strings to 
	//    the output vector:
	//      "This"
	//      "is"
	//      "a"
	//      "string"
	// 2. If the string is "Cpt S 223 is a prerequisite for 322" then Split('3') 
	//    adds 3 strings to the output vector:
	//      "Cpt S 22"
	//      " is a prerequisite for "
	//      "22"

	char* temp = m_str;
	
	
	int i = 0;
	while (i < m_length)
	{
		char* buffer = new char[m_length];
		
		
		int j = 0;
		while (temp[i] && temp[i] != c)
		{
		
			buffer[j] = temp[i];
			j++;
			i++;
		}
		buffer[j] = '\0';
		i++;

		
		outputVector.push_back(MyString{ buffer });
		
	}
	
}

// Gets a substring from this string and stores it in the output string. If 
// the substring cannot be parsed, then false is returned and the output 
// string is not modified.
bool MyString::Substring(int startIndex, int length, MyString& output) const
{

	//maybe works...?

	// You must implement this function

	if (startIndex < 0 || length < 0 || length > m_length)
	{
		return false;
	}
	else
	{
		char* buffer = new char[length + 1];
		int i = 0;
		int strLength = Length();

		while (i < length && startIndex < strLength)
		{
			buffer[i++] = m_str[startIndex++];
		}
		buffer[i] = '\0';

		//need to reallocate m_str because it was created using the default constructor
		//which only has size 1
		delete[] output.m_str;
		output.m_str = new char[length + 1];

		Copy(output.m_str, buffer, length + 1);
		output.m_length = output.Length();
		
		//now we are done with buffer
		//bye bye
		delete[] buffer;
		buffer = nullptr;
		
		return true;
	}

}

void MyString::Write(std::ostream& stream)
{
	stream << m_str;
}