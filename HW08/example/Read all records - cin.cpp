/*  File name: ex13-3a.c  */
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

int main()
{
   system( "mode con:cols=30 lines=20" );
   system( "color F0" );

   ifstream inFile( "Number.txt", ios::in );

   if ( !inFile )
	{
      cout << "File could not be opened" << endl;
      exit( 1 );
   }

   int number;
/*
   while( !inFile.eof() )
   {
      inFile >> number;
      cout << setw( 4 ) << number << setw( 2 ) << inFile.eof() << endl;
   }
   cout << endl;

   inFile.clear();
   inFile.seekg( 0 );
*/
   while( inFile >> number )
      cout << setw( 4 ) << number << setw( 2 ) << inFile.eof() << endl;
   cout << endl;
/*
   inFile.clear();
   inFile.seekg( 0 );

   while( inFile )
   {
      inFile >> number;
		cout << setw(4) << number << setw(2) << inFile.operator bool() << endl;
   }
   cout << endl;
*/
	inFile.close();

	system( "pause" );
}
