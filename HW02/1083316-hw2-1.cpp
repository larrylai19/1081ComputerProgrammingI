#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	int num,num2,num8,i2,i8,c,k; // int number, num2 for Binary digit, num8 for Octal digit 
	start:
	cout << "Enter a positive decimal integer of at most 8 digits: ";
	cin >> num; // input the integer into num;
	if(0>num||num>99999999) // if num is more than 8 digits or num<0 then
	goto start; // go to start to enter the integer again
	//******************************************************
	num2 = num; 
	for(i2=1;;i2++) // know the number has how many digits in brinary digit
	{
		c = num2 / pow(2,i2);
		if(c==0)
		break;
	}
	int n2[i2-1]; 
	for(k=i2-1;k>=0;k--) // change the number into binary digit from decimal digit
	{
		n2[k] = num2 % 2;
		num2 /= 2;
	}
	cout << "The binary equivalent of " << num <<" is ";
	for(k=0;k<=i2-1;k++)
	cout << n2[k]; // print the number's binary digit on the screen
	cout << endl;
	//******************************************************
	num8 = num;
	for(i8=1;;i8++)// know the number has how many digits in octal digit
	{
		c = num8 / pow(8,i8);
		if(c==0)
		break;
	}
	int n8[i8-1];
	for(k=i8-1;k>=0;k--) // change the number into octal digit from decimal digit
	{
		n8[k] = num8 % 8;
		num8 /= 8;
	}
	cout << "The octal equivalent of " << num <<" is ";
	for(k=0;k<=i8-1;k++)
	cout << n8[k]; // print the number's octal digit on the screen
	cout << endl;
	system("pause");
} 
