#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	char n1[250], n2[250];
	int hugeInt1[250] = {};
	int hugeInt2[250] = {};
	int Product[500] = {};
	int l1 = 0, l2 = 0, l3 = 0;
	while (cin >> n1 >> n2)
	{
		l1 = strlen(n1);
		l2 = strlen(n2);
		l3 = l1 + l2;
		for (int i = 0; i < 500; i++)
			Product[i] = 0;
		for (int i = 0; i < l1; i++)
			hugeInt1[i] = n1[l1 - i - 1] - '0';
		for (int i = 0; i < l2; i++)
			hugeInt2[i] = n2[l2 - i - 1] - '0';
		for (int i = 0; i < l1; i++)
			for (int j = 0; j < l2; j++)
				Product[j + i] += hugeInt1[i] * hugeInt2[j];
		for (int i = 0; i < l3; i++)
		{
			if (Product[i] >= 10)
			{
				Product[i + 1] += Product[i] / 10;
				Product[i] %= 10;
			}
		}
		for (int i = l3; Product[i - 1] == 0 && i > 1; i--)
			l3--;
		for (int i = l3 - 1; i >= 0; i--)
			cout << Product[i];
		cout << endl;
	}
}
