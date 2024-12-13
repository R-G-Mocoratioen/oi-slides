#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pr;
int n, m, cnt, h[200005], p[200005][20], d[200005], c2[200005], c1[200005];
long long ans = 0;
map<pr, int> mp;
struct Edge {
	int to, next;
} e[400005];
void Add_Edge(int x, int y) {
	e[++cnt].to = y;
	e[cnt].next = h[x];
	h[x] = cnt;
}
void DFS(int x, int fa) {
	p[x][0] = fa, d[x] = d[fa] + 1;
	for (int i = h[x]; i; i = e[i].next) {
		int y = e[i].to;
		if (y == fa) continue;
		DFS(y, x);
	}
}
void MakeST() {
	for (int j = 1; j <= 18; j++) {
		for (int i = 1; i <= n; i++) p[i][j] = p[p[i][j - 1]][j - 1];
	}
}
int LCA(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	for (int i = 18; i >= 0; i--)
		if (d[p[x][i]] >= d[y]) x = p[x][i];
	if (x == y) return x;
	for (int i = 18; i >= 0; i--)
		if (p[x][i] ^ p[y][i]) x = p[x][i], y = p[y][i];
	return p[x][0];
}
int Getson(int x, int lca) {
	if (x == lca) return 0;
	for (int i = 18; i >= 0; i--)
		if (d[p[x][i]] > d[lca]) x = p[x][i];
	return x;
}
void DFS2(int x) {
	for (int i = h[x]; i; i = e[i].next) {
		int y = e[i].to;
		if (y != p[x][0]) DFS2(y), c1[x] += c1[y], c2[x] += c2[y];
	}
	ans -= 1ll * c1[x] * (c1[x] - 1) / 2;
	ans += 1ll * c2[x] * (c2[x] - 1) / 2;
	// cout << x << ' ' << c1[x] << ' ' << c2[x] << '\n';
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), Add_Edge(x, y), Add_Edge(y, x);
	DFS(1, 0);
	MakeST();
	for (int i = 1, x, y; i <= m - n + 1; i++) {
		scanf("%d%d", &x, &y);
		int lca = LCA(x, y);
		// c1[x]++, c1[y]++;
		// c1[lca]--;
		// c1[p[lca][0]]--;
		c2[x]++, c2[y]++;
		c2[lca] -= 2;
		if (x != lca && y != lca) {
			c1[x]++;
			c1[y]++;
			int u = Getson(x, lca), v = Getson(y, lca);
			c1[u]--;
			c1[v]--;
			if (u > v) swap(u, v);
			mp[pr(u, v)]++;
		} else {
			if (d[x] > d[y]) swap(x, y);
			if (p[y][0] == x) continue;
			c1[y]++;
			c1[Getson(y, lca)]--;
		}
	}
	DFS2(1);
	for (auto [x, y] : mp) ans -= 1ll * y * (y - 1) / 2;
	printf("%lld\n", ans);
}