#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
const int mod = 998244353;
int n, a[62][62], st[62], top, ins[62], low[62];
int dfn[62], sign, SCC, bel[62], vst[62], curS, gv[62];
int d1[62], d2[62], vst2[62], is[62][62][62], inq[62];
vector<int> g[62];
vector<pr> ve[62];
void Tarjan(int x) {
	st[++top] = x, ins[x] = 1, dfn[x] = low[x] = ++sign;
	for (int y : g[x]) {
		if (!dfn[y]) Tarjan(y), low[x] = min(low[x], low[y]);
		else if (ins[y]) low[x] = min(low[x], dfn[y]);
	}
	if (low[x] == dfn[x]) {
		int tmp = 0;
		SCC++;
		while (tmp != x) {
			bel[tmp = st[top--]] = SCC, ins[tmp] = 0;
		}
	}
}
void dfs1(int x, int d) {
	d1[x] = d, vst[x] = vst2[x] = 1;
	for (int i = 1; i <= n; i++) {
		if (bel[i] == curS && !vst2[i] && a[x][i]) {
			dfs1(i, d + 1);
		}
	}
}
void dfs2(int x, int d) {
	d2[x] = d, vst[x] = vst2[x] = 1;
	for (int i = 1; i <= n; i++) {
		if (bel[i] == curS && !vst2[i] && a[i][x]) {
			dfs2(i, d + 1);
		}
	}
}
int b[520005], fail[520005];
void Solve() {
	memset(a, 0, sizeof(a));
	memset(st, 0, sizeof(st));
	memset(ins, 0, sizeof(ins));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(bel, 0, sizeof(bel));
	memset(vst, 0, sizeof(vst));
	memset(gv, 0, sizeof(gv));
	top = sign = SCC = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string str;
		cin >> str;
		for (int j = 1; j <= n; j++) {
			a[i][j] = str[j - 1] - '0';
			if (a[i][j]) g[i].push_back(j);
		}
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= n; i++) {
		if (vst[i]) continue;
		curS = bel[i];
		memset(vst2, 0, sizeof(vst2));
		dfs1(i, 0);
		memset(vst2, 0, sizeof(vst2));
		dfs2(i, 0);
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++) {
				if (bel[j] == curS && bel[k] == curS && a[j][k]) {
					gv[curS] = gcd(gv[curS], d1[j] + 1 + d2[k]);
				}
			}
	}
	// for (int i = 1; i <= n; i++) cout << i << ' ' << bel[i] << ' ' << gv[bel[i]] << '\n';
	for (int s = 1; s <= n; s++) {
		memset(is, 0, sizeof(is));
		memset(vst, 0, sizeof(vst));
		memset(inq, 0, sizeof(inq));
		is[s][gv[bel[s]]][0] = 1;
		ve[s].push_back(pr(gv[bel[s]], 0));
		priority_queue<pr> q;
		q.push(pr(bel[s], s)), inq[s] = 1;
		while (!q.empty()) {
			int x = q.top().second;
			q.pop();
			vst[x] = 1;
			for (auto [u, v] : ve[x]) {
				for (int y = 1; y <= n; y++) {
					if (!a[x][y] || vst[y]) continue;
					int nu = gcd(u, gv[bel[y]]), nv = nu ? (v + 1) % nu : v + 1;
					if (!is[y][nu][nv]) {
						is[y][nu][nv] = 1;
						ve[y].push_back(pr(nu, nv));
					}
				}
			}
			for (int y = 1; y <= n; y++) {
				if (a[x][y] && !inq[y]) {
					inq[y] = 1, q.push(pr(bel[y], y));
				}
			}
		}
		for (int t = 1; t <= n; t++) {
			ll lcm = 1;
			for (auto [u, v] : ve[t]) {
				for (auto [uu, vv] : ve[t]) {
					if (u && uu > u && uu % u == 0 && vv % u == v) {
						is[t][uu][vv] = 0;
					}
				}
			}
			for (auto [u, v] : ve[t]) {
				if (is[t][u][v] && u) {
					ll gg = gcd(lcm, (ll)u);
					lcm = lcm / gg * u;
				}
			}
			assert(lcm <= 520000);
			for (auto [u, v] : ve[t]) {
				if (is[t][u][v] && u) {
					for (int j = (v ? v : u); j <= lcm; j += u) {
						b[j] = 1;
					}
				}
			}
			for (int i = 2, j = 0; i <= lcm; i++) {
				while (j && b[j + 1] != b[i]) j = fail[j];
				if (b[j + 1] == b[i]) j++;
				fail[i] = j;
			}
			if (lcm % (lcm - fail[lcm]) == 0) {
				cout << lcm - fail[lcm] << ' ';
			} else cout << lcm << ' ';
			fill(b + 1, b + lcm + 1, 0);
			fill(fail + 1, fail + lcm + 1, 0);
			ve[t].clear();
		}
		cout << '\n';
	}
	for (int i = 1; i <= n; i++) g[i].clear();
}
int main() {
	int t;
	cin >> t;
	while (t--) Solve();
}