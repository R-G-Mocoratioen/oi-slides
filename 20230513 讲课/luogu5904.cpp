#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, son[200005], len[200005];
vector<int> gg[200005];
ll *f[200005], *g[200005], F[800005], *nowf, ans;
void DFS1(int x, int fa) {
	len[x] = 1;
	for (int y : gg[x]) {
		if (y == fa) continue;
		DFS1(y, x);
		if (len[y] + 1 > len[x]) len[x] = len[y] + 1, son[x] = y;
	}
}
void assign(int x) { f[x] = nowf, nowf += len[x] << 1, g[x] = nowf, nowf += len[x] << 1; }
void DFS2(int x, int fa) {
	// cout << x << ' ' << len[x] << '\n';
	if (son[x]) {
		f[son[x]] = f[x] + 1, g[son[x]] = g[x] - 1;
		DFS2(son[x], x);
	}
	f[x][0] = 1, ans += g[x][0]; // 注意这里，统计只有重儿子一个分支的贡献，其它贡献在下面能统计到！
	for (int y : gg[x]) {
		if (y == fa || y == son[x]) continue;
		assign(y), DFS2(y, x);
		// cout << x << ' ' << y << '\n';
		for (int i = 0; i < len[y]; i++) {
			if (i) ans += f[x][i - 1] * g[y][i];
			ans += g[x][i + 1] * f[y][i];
		}
		for (int i = 0; i < len[y]; i++) {
			g[x][i + 1] += f[x][i + 1] * f[y][i]; // 注意这里
			f[x][i + 1] += f[y][i];
			if (i) g[x][i - 1] += g[y][i];
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) scanf("%d%d", &x, &y), gg[x].push_back(y), gg[y].push_back(x);
	DFS1(1, 0);
	nowf = F, assign(1);
	DFS2(1, 0);
	printf("%lld\n", ans);
}