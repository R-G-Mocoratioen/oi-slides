#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
int n, dfn[N + 5], sign, len[N + 5], son[N + 5], mxv[N + 5], mxd[N + 5], d[N + 5], f[N + 5];
vector<int> g[N + 5];
void dfs(int x, int fa) {
	d[x] = d[fa] + 1;
	for (int y : g[x]) {
		if (y == fa) continue;
		dfs(y, x);
		if (len[y] + 1 > len[x]) len[x] = len[y] + 1, son[x] = y;
	}
}
void dfs2(int x, int fa) {
	dfn[x] = ++sign;
	if (son[x]) dfs2(son[x], x);
	for (int y : g[x]) {
		if (y == fa || y == son[x]) continue;
		dfs2(y, x);
	}
}
void Upd(int x, int val, int dep) {
	if (val > mxv[x] || (val == mxv[x] && dep < mxd[x])) mxv[x] = val, mxd[x] = dep;
}
void dfs3(int x, int fa) {
	if (son[x]) {
		dfs3(son[x], x);
		mxv[x] = mxv[son[x]], mxd[x] = mxd[son[x]];
	}
	f[dfn[x]] = 1, Upd(x, 1, d[x]);
	for (int y : g[x]) {
		if (y == fa || y == son[x]) continue;
		dfs3(y, x);
		for (int i = 0; i <= len[y]; i++) {
			f[dfn[x] + i + 1] += f[dfn[y] + i];
			Upd(x, f[dfn[x] + i + 1], d[y] + i);
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1, 0), dfs2(1, 0), dfs3(1, 0);
	for (int i = 1; i <= n; i++) cout << mxd[i] - d[i] << '\n';
}