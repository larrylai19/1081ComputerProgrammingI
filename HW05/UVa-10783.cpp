#include <iostream>
using namespace std;
int oddsum(int a, int b)
{
	if (a < b)
		return a + oddsum(a + 2, b);
	else if (a == b)
		return a;
	else
		return 0;
}
int main()
{
	int a, b, Casenum, change;
	
	cin >> Casenum;

	for (int i = 1; i <= Casenum; i++)
	{
		cin >> a >> b;
		
		if (a > b)
		{
			change = a;
			a = b;
			b = change;
		}
		
		if (a % 2 == 0)
			a++;
			
		cout << "Case " << i << ": " << oddsum(a, b) << endl;
	}
	
	return 0;
}
