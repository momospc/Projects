/****************************************************************
 * 								*
 * 			Read input and use it			*
 * 								*
 ****************************************************************/

#include <iostream>		// Defines cin and cout
#include <string>		// DDeclares class string

using namespace std;
int main()
{
	//Defining four strings:
	string prompt ("What is your name :  "),
	       name,
	       line( 40, '-' ),
	       total = " Hello ";

	cout << prompt;
	getline(cin, name);

	total = total + name;

	cout << line << endl
	     << total << endl;
	cout << " Your name is "
		<< name.length() << " characters long !" << endl;
	cout << line << endl;
	return 0;
}
