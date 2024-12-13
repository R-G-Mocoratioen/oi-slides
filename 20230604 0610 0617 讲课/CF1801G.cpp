#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int Power(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = 1ll * r * x % mod;
		x = 1ll * x * x % mod, y >>= 1;
	}
	return r;
}
int n, a[5005], p[5005], ta[5005];
void Solve() {
	cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y, p[i] = 1ll * x * Power(y, mod - 2) % mod;
	}
	for (int i = 0; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (j) ta[j - 1] = (ta[j - 1] + 1ll * a[j] * p[i]) % mod;
			if (j + 1 <= n) ta[j + 1] = (ta[j + 1] + 1ll * a[j] * (1 - p[i] + mod)) % mod;
			if (j == 0) ta[j] = (ta[j] + 1ll * a[j] * (1 - p[i] + mod)) % mod;
		}
		for (int j = 0; j <= n; j++) a[j] = ta[j], ta[j] = 0;
		cout << a[0] << ' ';
	}
	puts("");
}
int main() {
	int t;
	cin >> t;
	while (t--) Solve();
}