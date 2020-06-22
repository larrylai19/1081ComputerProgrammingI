#include <iostream>
using namespace std;

int f(int n)
{
	if (n / 10 == 0)
		return n;
	else
		return n % 10 + f(n/10);
}

int main()
{
	int n, ans = 0;

	for (;;)
	{
		cin >> n;
		
		if (n == 0)
			break;
		else
		{
			ans = f(n);
			while (ans >= 10)
				ans = f(ans);
			cout << ans << endl;
		}
	}

	return 0;
}
