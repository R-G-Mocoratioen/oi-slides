int c[N + 5];
void Upd(int x, int y) { // a[x] += y
	while (x <= n) c[x] += y, x += x & -x;
	// here, x & -x = lowbit(x) always holds
}

int Query(int x) {
	int res = 0;
	while (x) res += c[x], x -= x & -x;
	return res;
}

int Get(int s) {
	int res = 0;
	for (int i = 20; i >= 0; i--) {
		int x = res + (1 << i);
		if (x <= n && c[x] < s) {
			s -= c[x];
			res = x;
		}
	}
	return res;
}

int LCA(int x, int y) {
	if (d[x] < d[y]) swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (d[p[x][i]] >= d[y]) x = p[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i--) {
		if (p[x][i] ^ p[y][i]) {
			x = p[x][i], y = p[y][i];
		}
	}
	return p[x][0];
}

int Query(int l, int r) {
	int k = lg2[r - l + 1];
	return min(f[l][k], f[r - (1 << k) + 1][k]);
}

lg2[0] = -1;
for (int i = 1; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;