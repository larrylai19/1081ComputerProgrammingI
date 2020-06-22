// Fig. 12.4: fig12_04.cpp 
// Using member functions get, put and eof.
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
   system( "mode con cols=50 lines=20" );
   system( "color F0" );

	cout << "Input one character: ";
	int ch = cin.get();
	cout << endl << ch << endl << endl;

//	if( ch != 10 )
//	cin.ignore();

	cout << "Input one character: ";
	ch = cin.get();
	cout << endl << ch << endl << endl;
	
	system("pause");
} // end main

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
 * Hall. All Rights Reserved.                                             *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
