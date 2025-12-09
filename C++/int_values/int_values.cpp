/*****************************************************************
 * 								 *
 * 								 *
 * 	Simple code to show min and max of an int type		 *
 * 								 *
 * 								 *
 ****************************************************************/

# include <iostream>
# include <climits> 		//Defines min and max values
using namespace std;

int main()
{
	cout << " Range of types int and unsigned int "
		<< endl << endl;
	cout << "Type	Minimum		Maximum "
		<< endl 
		<< "______________________________________"
		<< endl;
	cout << "int	" << INT_MIN << "	" << INT_MAX << " "
		<< endl;

	cout << "Uint	" << " 	0 	"	 	<< UINT_MAX << endl;
	return 0;
}


		


