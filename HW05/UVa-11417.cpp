#include <iostream>
using namespace std;

int GCD(int i, int j)
{
	if (j % i == 0)
		return i;
	else
		GCD(j % i, i);
}
int main()
{
	int N = 0, G = 0;
	
	for (;;)
	{
		cin >> N;
		
		if (N == 0)
			break;
		else
		{
			for (int i = 1; i < N; i++)
				for (int j = i + 1; j <= N; j++)
					G += GCD(i, j);
			cout << G << endl;
			G = 0;
		}
	}

	return 0;
}
