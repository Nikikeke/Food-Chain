#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
int a[50010];
int val[50010];
int main()
{
	int findparent(int x);
	void crlcle(int a, int b, int x, int y, int d);
	int i, j, n, m, s, t, res;
	int d, x, y, parent_x, parent_y;
	cin >> n >> m;

	memset(val, 0, sizeof(val));
	for (i = 1; i <= n; i++)
	{
		a[i] = i;
	}
	res = 0;
	for (i = 1; i <= m; i++)
	{
		cin >> d >> x >> y;
		
		if ((x>n || y>n) || (d == 2 && x == y))
		{
			res++; continue;
		}
		parent_x = findparent(x);
		parent_y = findparent(y);
		if (parent_x != parent_y)
		{
			crlcle(parent_x, parent_y, x, y, d);
		}
		else
		{
			if (d == 1)
			{
				if (val[x] != val[y])
				{
					res++;
				}
			}
			else
			{
				if ((3 - val[x] + val[y]) % 3 != 1)
				{
					res++;
				}
			}
		}
	}
	cout << res << endl;

	return 0;
}
int findparent(int x)
{
	int k1, k2, s, t;
	k1 = x; s = 0;
	while (x != a[x])
	{
		s += val[x]; x = a[x];
	}
	while (k1 != a[k1])
	{
		t = s % 3; s -= val[k1]; val[k1] = t;
		k2 = a[k1];
		a[k1] = x;
		k1 = k2;
	}
	return x;
}
void crlcle(int c, int b, int x, int y, int d)
{
	int i, j;
	a[b] = c;
	val[b] = (3 - val[y] + (d - 1) + val[x]) % 3;
}