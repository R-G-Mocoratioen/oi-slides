#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans = 0, a[200005], f[200005];
int n;
vector<int> g[200005];
void dfs(int x, int fa) {
	ll sum = 0, mx = 0, t = 0;
	for (int y : g[x]) {
		if (y == fa)
			continue;
		dfs(y, x), sum += f[y], mx = max(mx, f[y]);
	}
	t = min(sum / 2, sum - mx);
	if (sum <= a[x])
		f[x] = a[x], ans += a[x] - sum;
	else if (t >= sum - a[x])
		ans -= sum - a[x], f[x] = 2 * a[x] - sum;
	else
		ans -= min(t, a[x]), f[x] = max(a[x] - t, 0ll);
}
int rd() {
	int x = 0, ch = getchar();
	while (ch < '0' || ch > '9')
		ch = getchar();
	while (ch <= '9' && ch >= '0')
		x = x * 10 + ch - '0', ch = getchar();
	return x;
}
int main() {
	n = rd();
	for (int i = 1; i <= n; i++)
		a[i] = rd();
	for (int i = 1, x, y; i < n; i++)
		x = rd(), y = rd(), g[x].push_back(y), g[y].push_back(x);
	dfs(1, 0), cout << ans;
}