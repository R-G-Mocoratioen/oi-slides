/*
for (int i = 2; i * i <= n; i++) {
    if (n % i) continue;
    p[++cnt] = i;
    while (n % i == 0) n /= i, pk[cnt]++;
}

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

for (int i = 2; i <= n; i++) {
    if (vst[i]) continue;
    for (int j = i + i; j <= n; j += i) {
        vst[j] = 1;
    }
}

for (int i = 2; i <= n; i++) {
    if (!vst[i]) {
        p[++cnt] = i, pk[i] = i;
    }
    if (pk[i] == i) {
        val[i] = gcd(i, x); // i 为质数幂
    }
    for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
        vst[i * p[j]] = 1;
        if (i % p[j] == 0) {
            pk[i * p[j]] = pk[i] * p[j];
            val[i * p[j]] = val[i] / val[pk[i]] * val[pk[i] * p[j]];
            break;
        } else {
            pk[i * p[j]] = p[j];
            val[i * p[j]] = val[i] * val[p[j]];
        }
    }
}

void Exgcd(int a, int b, int &x, int &y) {
    if (!b) return x = 1, y = 0, void();
    int xx, yy;
    Exgcd(b, a % b, xx, yy);
    x = yy, y = xx - (a / b) * yy;
}*/

#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
int ys[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
LL n, anx, ans;
void dfs(int u, int m, LL cnt, LL x) {
	if (cnt > ans) {
		ans = cnt;
		anx = x;

	} else if (cnt == ans && x < anx) {
		anx = x;
	}
	if (u == 15) return;
	for (int i = 1; i <= m; i++) {
		x = x * ys[u];
		if (x > n) break;
		dfs(u + 1, i, cnt * (i + 1), x);
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		anx = 0;
		ans = 0;
		dfs(0, 60, 1, 1);
		cout << ans << endl;
	}
}

for (int i = 1, j; i <= n; i = j + 1) {
	j = n / (n / i);
	ans += (j - i + 1) * f(n / i);
}

for (int i = 1, j; i <= n && i <= m; i = j + 1) {
	j = min(n / (n / i), m / (m / i));
	ans += ... * f(n / i, m / i);
}