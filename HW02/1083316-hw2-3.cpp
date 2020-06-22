#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	int i,c,u,t,h; // int i for the number waiting for identifying it is Armstrong number or not
	cout << "all Armstrong numbers of three digits: " << endl;
	for(i=100;i<=999;i++)
	{
		c = i;
		h = c/100; // get the number's hundred digit
		t = (c-100*h)/10; // get the number's ten digit
		u = (c-100*h-10*t); // get the number's unit digit
		if(i==pow(h,3)+pow(t,3)+pow(u,3)) //if the number equal all the number's cube add each other, the number is Armstrong number
		cout << i << " ";
	}
	cout << endl;
	system("PAUSE");
} 
