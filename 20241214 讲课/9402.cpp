#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353, inf = 1e9;
int n, ispre[1000005], issuf[1000005], ssuf[1000005];
char a[1000005];
int kmp[1000005], aabb[1000005];
int ch[1000005][128], fa[1000005], len[1000005], lst = 0, tot = 1;
int sfa[1000005], dif[1000005], pos[1000005], g[1000005];
void Ins(int i) {
	int p = lst, x = a[i];
	while (a[i - len[p] - 1] != x) p = fa[p];
	if (!ch[p][x]) {
		len[++tot] = len[p] + 2;
		int q = fa[p];
		while (a[i - len[q] - 1] != x) q = fa[q];
		fa[tot] = ch[q][x], ch[p][x] = tot, dif[tot] = len[tot] - len[fa[tot]];
		if (dif[tot] == dif[fa[tot]]) sfa[tot] = sfa[fa[tot]];
		else sfa[tot] = fa[tot];
	}
	lst = ch[p][x];
}
int main() {
	scanf("%s", a + 1);
	n = strlen(a + 1), a[0] = '?';
	fa[0] = 1, fa[1] = 1, len[1] = -1;
	for (int i = 1; i <= n; i++) {
		Ins(i);
		pos[i] = lst;
		if (len[lst] == i && i % 2 == 0) ispre[i] = 1;
	}
	int tmn = pos[n];
	while (tmn > 1) {
		if (len[tmn] % 2 == 0) issuf[n - len[tmn] + 1] = 1;
		tmn = fa[tmn];
	}
	ispre[0] = 1;
	for (int i = n; i >= 1; i--) ssuf[i] = ssuf[i + 1] + issuf[i];
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		if (issuf[i] && i > 1) {
			ans++;
		}
		if (!ispre[i]) continue;
		int mr = i / 2 + n / 2 + 2;
		if (mr <= n) ans += ssuf[n - 2 * (n - mr + 1) + 1];
		ans++;
	}
	for (int i = 2, j = 0; i <= n; i++) {
		while (j && a[j + 1] != a[i]) j = kmp[j];
		if (a[j + 1] == a[i]) j++;
		kmp[i] = j;
	}
	for (int i = 1; i < n; i++)
		if (ispre[i] && issuf[i + 1]) ans++;
	for (int i = 1; i <= n; i++) {
		for (int p = pos[i]; len[p] > 0; p = sfa[p]) {
			g[p] = ispre[i - len[sfa[p]] - dif[p]];
			if (sfa[p] != fa[p]) g[p] += g[fa[p]];
			aabb[i] += g[p];
		}
	}
	int bo = n;
	while (bo) {
		int w = n - bo;
		if (w < n && w % 2 == 0) ans += aabb[w];
		bo = kmp[bo];
	}
	cout << ans + 1;
}