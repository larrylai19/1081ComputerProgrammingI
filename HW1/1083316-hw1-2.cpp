#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   char number[5]; // integer read from user
   int i;
   cout << "Enter a five-digit integer: "; // prompt
   for(i=0;i<=4;i++)
   {
   	cin >> number[i];
   	cout << number[i] << "   ";
   }
   system( "pause" );
} // end main
