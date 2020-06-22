// Determine whether a number is a palindrome.
#include <iostream>
using namespace std; 

int main()
{
   char number[5]; // user input number
   int i;
   cout <<"Enter a 5-digit number: ";
   for(i=0;i<=4;i++)
   {
   	cin >> number[i];
   	cout << number[i];
   }
   if(number[0]==number[4]&&number[1]==number[3])
    cout <<" is a palindrome¡I¡I¡I"<<endl;
   else
    cout <<" is not a palindrome."<<endl;
   system( "pause" );
} // end main
