// Determine whether three values represent the sides of a right triangle.
#include <iostream>
#include <math.h>
using namespace std; 

int main()
{
   int l[4],i,M,k=0;
   for(i=1;i<=3;i++)
   {
   	cout << "Enter side " << i <<" : ";
   	cin >> l[i];
   }
   M=l[1];
   for(i=2;i<=3;i++)
   {
   	if(M<l[i])
   	{
   		k = k + pow(M,2);
   		M=l[i];
	}
	else
	k = k + pow(l[i],2);
   }
   if(pow(M,2)==k)
   cout << "These are the sides of a right triangle.\n";
   else
   cout << "These do not form a right triangle.\n";
   system( "pause" );
} // end main
