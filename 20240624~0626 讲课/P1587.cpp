#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int s1[2005], is[2005], n, m, K, f[200005], a[200005], g[200005], tot;
int p[200005], cnt, s2[2005], sq, fir1[40005], fir2[40005];
double inv[200005];
int pos(int u) {
	if (u <= sq) return u;
	int x = n / u, y = m / u;
	return max(fir1[x], fir2[y]);
}
ll F(ll x) { return (x / K) * s1[K] + s1[x % K]; }
int main() {
	cin >> n >> m >> K, sq = sqrt(max(n, m));
	for (int i = 1; i <= K; i++) {
		s1[i] = s1[i - 1] + (is[i] = (gcd(i, K) == 1));
		s2[i] = s2[i - 1];
		if (i > 1 && K % i == 0) {
			bool ok = 1;
			for (int j = 2; j * j <= i; j++)
				if (i % j == 0) ok = 0;
			s2[i] += ok;
		}
	}
	int P = min(n, m);
	for (int i = 1, j; i <= P; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		a[++tot] = j, g[tot] = j - 1;
		if (j <= sq) continue;
		if (!fir1[n / i]) fir1[n / i] = tot;
		if (!fir2[m / i]) fir2[m / i] = tot;
	}
	for (int i = 2; i * i <= P; i++) {
		if (g[i] == g[i - 1]) continue;
		p[++cnt] = i, inv[cnt] = 1.00000000000001 / i;
		for (int j = tot; a[j] >= i * i; j--) {
			g[j] -= g[pos(a[j] * inv[cnt])] - cnt + 1;
		}
	}
	for (int i = 1; i <= tot; i++) {
		f[i] = -g[i] + s2[min(K, a[i])];
	}
	for (int i = cnt; i; i--) {
		if (K % p[i] == 0) continue;
		for (int j = tot; a[j] >= p[i] * p[i]; j--) {
			int u = pos(a[j] * inv[i]), w = min(p[i], u);
			f[j] += -f[u] - g[w] + s2[min(K, a[w])];
		}
	}
	for (int i = 1; i <= tot; i++) f[i]++;
	ll ans = 0;
	for (int i = 1; i <= tot; i++) {
		ans += 1ll * (f[i] - f[i - 1]) * (n / a[i]) * F(m / a[i]);
	}
	cout << ans << '\n';
}