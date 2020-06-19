#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	int num,c,sum; // int num for a positive integer, sum for the answer
	start:
	cout << "Enter a positive integer of at most 8 digits: "; // let the user enter the integer
	cin >> num;
	cout << "The sum of all digits of " << num << " is "; // print the result on the screen
	if(0>num||num>99999999)
	goto start;
	for(int i=7;i>=0;i--) // separate the digits and add all of them into sum
	{
		c = num / pow(10,i); 
		sum += c;
		if(c!=0)
		num -= c*pow(10,i);
	}
	cout << sum << endl; // print the result on the screen
	system("pause");
} 
