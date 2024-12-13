#include <bits/stdc++.h>
using namespace std;
int n, mod, a[605][605];
int Calc() {
	int ret = 1, flag = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			while (a[j][i]) {
				if (!a[i][i]) {
					for (int k = i; k <= n; k++) swap(a[i][k], a[j][k]);
					flag = mod - flag;
					break;
				}
				int x = a[i][i], y = a[j][i];
				ret = 1ll * ret * x * y % mod;
				for (int k = i; k <= n; k++) {
					a[i][k] = 1ll * a[i][k] * y % mod;
					a[j][k] = 1ll * a[j][k] * x % mod;
					a[j][k] = (a[j][k] - a[i][k] + mod) % mod;
				}
			}
		}
		ret = 1ll * ret * (a[i][i] % mod + mod) % mod;
	}
	return 1ll * ret * flag % mod;
}
int main() {
	scanf("%d%d", &n, &mod);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	printf("%d\n", Calc());
}