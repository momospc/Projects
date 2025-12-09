/****************************************************************
 * 								*
 * 		size of fundamental types			*
 * 								*
 ****************************************************************/

#include <iostream>
using namespace std;

int main()
{
	cout << "\nSize of Fundamental Types\n"
	     << "\nTYPE			SIZE\n"
	     << "______________________________________" << endl;
	cout << " char:			" << sizeof (char) << " byte " << endl;
	cout << " short:			" << sizeof (short) << " bytes " << endl;
	cout << " int:			" << sizeof (int) << " bytes " << endl;
	cout << " long:			" << sizeof (long) << " bytes " << endl;
	cout << " float:			" << sizeof (float) << " bytes " << endl;
	cout << " double:		" << sizeof (double) << " bytes " << endl;
	cout << " long double:		" << sizeof (long double) << " bytes " << endl;

	return 0;
}
		
