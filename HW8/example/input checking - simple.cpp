#include <iostream>
using namespace::std;

int inputAnInteger();

int main()
{
   system("mode con cols=40");
   system( "color F0" );

	int number;
	while( ( number = inputAnInteger() ) == 0 )
		;

	cout << "\nThe first " << number << " fibonacci numbers:\n";

	int n1 = 1;
	int n2 = 1;
	cout << endl << n1 << endl << n2 << endl;

	int n3;
	for ( int i = 3; i <= number; i++ )
   {
		n3 = n1 + n2;
		cout << n3 << endl;
		n1 = n2;
		n2 = n3;
	}
	cout << endl;

   system("pause");
}

int inputAnInteger()
{
	cout << "Input a positive integer (2-46): ";
	int number;
	cin >> number;

	if( number >= 2 && number <= 46 )
		return number;
	else
		return 0;
}
