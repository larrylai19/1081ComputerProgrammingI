#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	int n,i,a=0;
	start:
	cin >> n;
	if(n!=0)
	{
			for(i=1;i<=n;i++)
			{
				a += pow(i,2);
			}
		cout << a << endl;
		a=0;
		goto start;
	}	
} 
