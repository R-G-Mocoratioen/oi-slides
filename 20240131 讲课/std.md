```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n, m, k, f[100005][2], is[100005];
vector<int> g[100005];
int Power(int x, int y) {
	if (!x) return y == 0;
	int r = 1;
	while (y) {
		if (y & 1) r = 1ll * r * x % mod;
		x = 1ll * x * x % mod, y >>= 1;
	}
	return r;
}
void dfs(int x, int fa) {
	f[x][0] = f[x][1] = 1;
	if (is[x]) f[x][1] = 0;
	for (int y : g[x]) {
		if (y == fa) continue;
		dfs(y, x), f[x][0] = (1ll * f[y][0] * (m - 2) + f[y][1]) % mod * f[x][0] % mod,
		           f[x][1] = 1ll * f[x][1] * f[y][0] % mod * (m - 1) % mod;
	}
}
int main() {
	cin >> n >> m >> k;
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), g[x].push_back(y), g[y].push_back(x);
	for (int i = 1, x; i <= k; i++) scanf("%d", &x), is[x] = 1;
	dfs(1, 0);
	int sum = (1ll * (m - 1) * f[1][0] + f[1][1]) % mod;
	cout << (1ll * m * Power(m - 1, n - 1) % mod - sum + mod) % mod * m % mod;
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353, N = 500, M = 1730;
int v[N + 5][M + 5], f[N + 5], C[N + 5][N + 5], pw[N + 5], prod[M + 5];
int t[M + 5], del[M + 5][M + 5], ny[M + 5];
int main() {
	auto st = clock();
	ny[0] = ny[1] = 1;
	for (int i = 2; i <= M; i++) ny[i] = 1ll * ny[mod % i] * (mod - mod / i) % mod;
	for (int i = 2; i <= M; i++) ny[i] = 1ll * ny[i - 1] * ny[i] % mod;
	for (int i = 0; i <= N; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	prod[0] = 1;
	for (int j = 1; j <= M; j++) {
		for (int k = j - 1; k >= 0; k--) {
			prod[k + 1] = (prod[k + 1] + prod[k]) % mod;
			prod[k] = 1ll * prod[k] * (mod - j) % mod;
		}
		pw[0] = f[0] = 1;
		for (int i = 1; i <= N; i++) {
			pw[i] = 1ll * pw[i - 1] * j % mod, f[i] = 0;
			for (int k = 1; k + k <= i; k++) {
				f[i] = (f[i] + 1ll * f[k - 1] * f[i - k] % mod * C[i - 1][k - 1] % mod *
				                   pw[min(k, i - k + 1) - 1]) %
				       mod;
			}
			f[i] = 2 * f[i] % mod;
			if (i & 1) {
				int k = (i + 1) / 2;
				f[i] = (f[i] + 1ll * f[k - 1] * f[i - k] % mod * C[i - 1][k - 1] % mod *
				                   pw[min(k, i - k + 1) - 1]) %
				       mod;
			}
			v[i][j] = f[i];
		}
	}
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j <= M; j++) t[j] = prod[j];
		for (int j = M; j > 0; j--) {
			del[i][j - 1] = t[j];
			t[j - 1] = (t[j - 1] + 1ll * t[j] * i) % mod;
		}
	}
	auto ed = clock();
	cerr << 1.0 * (ed - st) / CLOCKS_PER_SEC << '\n';
	int t;
	cin >> t;
	while (t--) {
		int n, x;
		cin >> n >> x;
		if (x < n || x - n > 1725) {
			cout << "0\n";
			continue;
		}
		x -= n;
		int ans = 0;
		for (int i = 1; i <= M; i++) {
			// cout << v[n][i] << '\n';
			ans = (ans + 1ll * del[i][x] * v[n][i] % mod * ny[i - 1] % mod * ny[M - i] % mod *
			                 ((M - i) % 2 ? mod - 1 : 1)) %
			      mod;
		}
		cout << ans << '\n';
	}
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, st[300005], top, st2[300005], top2, a[300005], s[300005], ans = 0, tagmi[1200005],
                                                                 tag[1200005], K;
struct P {
	int mi, micnt;
	ll mis, ans;
};
P operator+(P a, P b) {
	P ret;
	ret.mi = min(a.mi, b.mi), ret.micnt = a.micnt * (a.mi <= b.mi) + b.micnt * (b.mi <= a.mi);
	ret.mis = a.mis * (a.mi <= b.mi) + b.mis * (b.mi <= a.mi);
	if (a.mi < b.mi) ret.ans = a.ans;
	else if (a.mi > b.mi) ret.ans = b.ans;
	else ret.ans = a.ans + b.ans + a.micnt * b.mis;
	return ret;
}
P t[1200005];
void Build(int p, int l, int r) {
	tag[p] = tagmi[p] = 0;
	if (l == r) return t[p] = {0, 1, s[l], 0}, void();
	int mid = (l + r) / 2;
	Build(p * 2, l, mid), Build(p * 2 + 1, mid + 1, r), t[p] = t[p * 2] + t[p * 2 + 1];
}
void Tagmi(int p, int z) {
	t[p].mis += t[p].micnt * z, t[p].ans += 1ll * z * t[p].micnt * (t[p].micnt - 1) / 2,
	    tagmi[p] += z;
}
void Tag(int p, int z) { t[p].mi += z, tag[p] += z; }
void Pushdown(int p) {
	if (tag[p]) Tag(p * 2, tag[p]), Tag(p * 2 + 1, tag[p]), tag[p] = 0;
	if (tagmi[p]) {
		if (t[p * 2].mi == t[p].mi) Tagmi(p * 2, tagmi[p]);
		if (t[p * 2 + 1].mi == t[p].mi) Tagmi(p * 2 + 1, tagmi[p]);
		tagmi[p] = 0;
	}
}
void U(int p, int l, int r, int x, int y, int z) {
	if (x <= l && r <= y) return Tag(p, z);
	Pushdown(p);
	int mid = (l + r) / 2;
	if (x <= mid) U(p * 2, l, mid, x, y, z);
	if (mid < y) U(p * 2 + 1, mid + 1, r, x, y, z);
	t[p] = t[p * 2] + t[p * 2 + 1];
}
P Q(int p, int l, int r, int x, int y) {
	if (x <= l && r <= y) return t[p];
	Pushdown(p);
	int mid = (l + r) / 2;
	if (x > mid) return Q(p * 2 + 1, mid + 1, r, x, y);
	if (y <= mid) return Q(p * 2, l, mid, x, y);
	return Q(p * 2, l, mid, x, y) + Q(p * 2 + 1, mid + 1, r, x, y);
}
int main() {
	scanf("%d%d", &n, &K);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	Build(1, 1, n), st[top = 0] = st2[top2 = 0] = n + 1;
	for (int i = n; i; i--) {
		while (top && a[st[top]] < a[i])
			U(1, 1, n, st[top], st[top - 1] - 1, -a[st[top]]), top--; // st:最大值
		while (top2 && a[st2[top2]] > a[i])
			U(1, 1, n, st2[top2], st2[top2 - 1] - 1, a[st2[top2]]), top2--; // st2:最小值
		U(1, 1, n, i, st[top] - 1, a[i]), U(1, 1, n, i, st2[top2] - 1, -a[i]), U(1, 1, n, i, n, -1);
		s[i] = t[1].micnt, st[++top] = i, st2[++top2] = i;
	}
	Build(1, 1, n), st[top = 0] = st2[top2 = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (top && a[st[top]] < a[i])
			U(1, 1, n, st[top - 1] + 1, st[top], -a[st[top]]), top--; // st:最大值
		while (top2 && a[st2[top2]] > a[i])
			U(1, 1, n, st2[top2 - 1] + 1, st2[top2], a[st2[top2]]), top2--; // st2:最小值
		U(1, 1, n, st[top] + 1, i, a[i]), U(1, 1, n, st2[top2] + 1, i, -a[i]), U(1, 1, n, 1, i, -1),
		    Tagmi(1, -1);
		if (i >= K) {
			P tmp = Q(1, 1, n, 1, i - K + 1);
			ans = (ans + tmp.ans * (tmp.mi == -1)) % mod;
		}
		st[++top] = i, st2[++top2] = i;
	}
	printf("%d\n", 2 * ans % mod);
	return 0;
}
```