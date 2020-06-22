#include <iostream>
using namespace::std;

int main()
{
   system( "mode con cols=50 lines=20" );
   system( "color F0" );

	char string[ 80 ];

	cout << "Enter a string: ";
	cin >> string;
   cout << "\nIs the state of the input stream good? " << cin.good() << endl;
   cout << "Is the state of the input stream fail? " << cin.fail() << endl;
   cout << string << endl;

//	cin.ignore();

	cout << "\nEnter a string: ";
	cin.get( string, 10, '\n' );
   cout << "\nIs the state of the input stream good? " << cin.good() << endl;
   cout << "Is the state of the input stream fail? " << cin.fail() << endl;
   cout << string << endl;
	
	system("pause");
}