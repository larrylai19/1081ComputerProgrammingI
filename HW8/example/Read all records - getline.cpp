/*  File name: ex13-3a.c  */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

int main()
{
   ifstream inFile( "clients.txt", ios::in );

   if ( !inFile )
	{
      cout << "File could not be opened" << endl;
      exit( 1 );
   }

   char clients[ 20 ];

/*
   while( !inFile.eof() )
   {
      inFile.getline( clients, 20 );
      cout << clients << setw( 4 ) << inFile.eof() << endl;
//		cout << "inFile.tellg()  " << setw(2) << inFile.tellg() << endl;
   }
   cout << endl;

   inFile.clear();
   inFile.seekg( 0 );

   while( inFile.getline( clients, 20 ) )
   {
      cout << clients << setw( 4 ) << inFile.eof() << endl;
//      cout << "inFile.tellg()  " << setw(2) << inFile.tellg() << endl;
   }
   cout << endl;

   inFile.clear();
   inFile.seekg( 0 );
*/
/*
   while( inFile )
   {
      inFile.getline( clients, 20 );
      cout << clients << setw( 4 ) << inFile.eof() << endl;
//      cout << "inFile.tellg()  " << setw(2) << inFile.tellg() << endl;
   }
   cout << endl;
*/
	inFile.close();

	system( "pause" );
}
