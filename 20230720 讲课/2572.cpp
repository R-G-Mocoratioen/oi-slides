#include <bits/stdc++.h>
using namespace std;
struct P {
	int lm, rm, lmz, rmz, ansz, len, ans, sum;
} t[400005];
P operator+(P a, P b) {
	P ret;
	ret.lm = a.lm;
	if (a.lm == a.len) ret.lm = a.len + b.lm;
	ret.rm = b.rm;
	if (b.rm == b.len) ret.rm = b.len + a.rm;
	ret.lmz = a.lmz;
	if (a.lmz == a.len) ret.lmz = a.len + b.lmz;
	ret.rmz = b.rmz;
	if (b.rmz == b.len) ret.rmz = b.len + a.rmz;
	ret.len = a.len + b.len;
	ret.ans = max(a.rm + b.lm, max(a.ans, b.ans));
	ret.ansz = max(a.rmz + b.lmz, max(a.ansz, b.ansz));
	ret.sum = a.sum + b.sum, ret.len = a.len + b.len;
	return ret;
}
int n, m, tag[400005], tag2[400005];
void Build(int p, int l, int r) {
	if (l == r) {
		int x;
		scanf("%d", &x), t[p] = {x, x, !x, !x, !x, 1, x, x};
		return;
	}
	int mid = (l + r) / 2;
	Build(p * 2, l, mid), Build(p * 2 + 1, mid + 1, r);
	t[p] = t[p * 2] + t[p * 2 + 1];
}
void Tag2(int p) {
	swap(t[p].lm, t[p].lmz), swap(t[p].rm, t[p].rmz), swap(t[p].ans, t[p].ansz),
	    t[p].sum = t[p].len - t[p].sum;
	tag2[p] ^= 1;
}
void Tag(int p, int x) {
	if (!x) t[p].lmz = t[p].rmz = t[p].ansz = t[p].len, t[p].lm = t[p].rm = t[p].sum = t[p].ans = 0;
	else t[p].lmz = t[p].rmz = t[p].ansz = 0, t[p].lm = t[p].rm = t[p].sum = t[p].ans = t[p].len;
	tag[p] = x, tag2[p] = 0;
}
void Pushdown(int p) {
	if (~tag[p]) Tag(p * 2, tag[p]), Tag(p * 2 + 1, tag[p]), tag[p] = -1;
	if (tag2[p]) Tag2(p * 2), Tag2(p * 2 + 1), tag2[p] = 0;
}
void Make(int p, int l, int r, int x, int y, int z) {
	if (x <= l && r <= y) return Tag(p, z), void();
	Pushdown(p);
	int mid = (l + r) / 2;
	if (x <= mid) Make(p * 2, l, mid, x, y, z);
	if (mid < y) Make(p * 2 + 1, mid + 1, r, x, y, z);
	t[p] = t[p * 2] + t[p * 2 + 1];
}
void Rev(int p, int l, int r, int x, int y) {
	if (x <= l && r <= y) return Tag2(p), void();
	Pushdown(p);
	int mid = (l + r) / 2;
	if (x <= mid) Rev(p * 2, l, mid, x, y);
	if (mid < y) Rev(p * 2 + 1, mid + 1, r, x, y);
	t[p] = t[p * 2] + t[p * 2 + 1];
}
P Query(int p, int l, int r, int x, int y) {
	if (x <= l && r <= y) return t[p];
	Pushdown(p);
	int mid = (l + r) / 2;
	if (x > mid) return Query(p * 2 + 1, mid + 1, r, x, y);
	if (y <= mid) return Query(p * 2, l, mid, x, y);
	return Query(p * 2, l, mid, x, y) + Query(p * 2 + 1, mid + 1, r, x, y);
}
int main() {
	memset(tag, -1, sizeof(tag)), cin >> n >> m, Build(1, 1, n);
	for (int i = 1, opt, x, y; i <= m; i++) {
		scanf("%d%d%d", &opt, &x, &y), x++, y++;
		if (opt == 0) Make(1, 1, n, x, y, 0);
		if (opt == 1) Make(1, 1, n, x, y, 1);
		if (opt == 2) Rev(1, 1, n, x, y);
		if (opt == 3) printf("%d\n", Query(1, 1, n, x, y).sum);
		if (opt == 4) printf("%d\n", Query(1, 1, n, x, y).ans);
	}
}