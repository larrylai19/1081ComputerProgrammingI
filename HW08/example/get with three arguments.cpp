#include <iostream>
using namespace::std;

int main()
{
   system("mode con cols=50 lines=24");
   system( "color F0" );

   char string[ 80 ];

   for( int i = 1; i <= 3; i++ )
   {
      cout << "Enter a string: ";
      cin.get( string, 80, '\n' );
      cout << "\nIs the state of the input stream good? " << cin.good() << endl;
      cout << "Is the state of the input stream fail? " << cin.fail() << endl;
      cout << "Is the state of the input stream fail? " << cin.bad() << endl;
      cout << "Is the state of the input stream fail? " << cin.eof() << endl;
//      cin.ignore();
//      cin.clear();
      cout << string << endl << endl;
   }
   
   system("pause");
}