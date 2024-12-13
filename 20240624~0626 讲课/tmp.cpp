#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;
typedef long long ll;
int miu[5000005], p[5000005], vst[5000005], sm[5000005], phi[5000005], f[2005];
void Mobius(int n) {
	miu[1] = 1, phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vst[i]) {
			p[++p[0]] = i;
			miu[i] = -1, phi[i] = i - 1;
		}
		for (int j = 1; j <= p[0] && i * p[j] <= n; j++) {
			vst[i * p[j]] = 1;
			if (i % p[j]) miu[i * p[j]] = -miu[i], phi[i * p[j]] = phi[i] * phi[p[j]];
			else {
				miu[i * p[j]] = 0, phi[i * p[j]] = phi[i] * p[j];
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++) sm[i] = sm[i - 1] + miu[i];
}
unordered_map<ll, ll> mu;
int n, m, k;
ll ans = 0;
ll F(ll x) { return (x / k) * phi[k] + f[x % k]; }
ll S(ll n) {
	if (mu.count(n)) return mu[n];
	if (n <= 5000000) return sm[n];
	ll ans = 1;
	for (ll i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ans -= (j - i + 1) * S(n / i);
	}
	return mu[n] = ans;
}
unordered_map<ll, ll> mp;
ll G(ll n, ll k) {
	if (!n) return 0;
	if (k == 1) return S(n);
	if (mp.count(k * 1000000001ll + n)) return mp[k * 1000000001ll + n];
	ll ans = 0;
	for (int i = 1; i * i <= k; i++) {
		if (k % i) continue;
		ans += miu[i] * miu[i] * G(n / i, i);
		if (i * i != k) ans += miu[k / i] * miu[k / i] * G(n / (k / i), k / i);
	}
	return mp[k * 1000000001ll + n] = ans;
}
int main() {
	cin >> n >> m >> k;
	Mobius(5000000);
	for (int i = 1; i < k; i++) f[i] = f[i - 1] + (__gcd(i, k) == 1);
	for (int i = 1, j; i <= n && i <= m; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		ans += (G(j, k) - G(i - 1, k)) * (n / i) * F(m / i);
	}
	cout << ans;
	return 0;
}