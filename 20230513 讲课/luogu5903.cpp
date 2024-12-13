#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
const int N = 1e6;
ui s;
inline ui get(ui x) {
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x;
}
int n, q, root;
ll ans = 0;
int sign, len[N + 5], son[N + 5], l2[N + 5] = {-1}, top[N + 5], p[N + 5][21], f[N + 5], pos[N + 5],
                                         d[N + 5];
vector<int> g[N + 5];
void DFS1(int x, int fa) {
	d[x] = d[fa] + 1, p[x][0] = fa;
	for (int i = 1; i <= 18; i++) p[x][i] = p[p[x][i - 1]][i - 1];
	for (int y : g[x]) {
		DFS1(y, x);
		if (len[y] + 1 > len[x]) len[x] = len[y] + 1, son[x] = y;
	}
}
void DFS2(int x, int tp) {
	top[x] = tp;
	if (son[x]) DFS2(son[x], tp);
	for (int y : g[x]) {
		if (y == son[x]) continue;
		DFS2(y, y);
	}
}
int Query(int x, int k) {
	if (!k) return x;
	x = p[x][l2[k]], k -= (1 << l2[k]);
	return f[pos[top[x]] + (d[x] - d[top[x]]) - k];
}
int main() {
	scanf("%d%d%u", &n, &q, &s);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		if (x) g[x].push_back(i);
		else root = i;
	}
	for (int i = 1; i <= n; i++) l2[i] = l2[i / 2] + 1;
	DFS1(root, 0);
	DFS2(root, root);
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		if (i != top[i]) continue;
		pos[i] = cur + len[i] + 1;
		for (int j = len[i], x = i; j >= 0; j--, x = p[x][0]) f[cur + j + 1] = x;
		for (int j = 0, x = i; j <= len[i]; j++, x = son[x]) f[cur + len[i] + 1 + j] = x;
		cur += len[i] * 2 + 1;
	}
	ui lastans = 0;
	for (int i = 1; i <= q; i++) {
		int x = (get(s) ^ lastans) % n + 1;
		int k = (get(s) ^ lastans) % d[x];
		lastans = Query(x, k);
		ans ^= (1ll * i * lastans);
	}
	printf("%lld\n", ans);
}