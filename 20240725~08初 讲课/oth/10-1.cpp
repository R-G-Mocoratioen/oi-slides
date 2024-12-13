/*int sum[4 * N + 5];
void Build(int p, int l, int r) {
    if (l == r) return sum[p] = a[l], void();
    int mid = (l + r) >> 1;
    Build(p * 2, l, mid);
    Build(p * 2 + 1, mid + 1, r);
    sum[p] = sum[p * 2] + sum[p * 2 + 1];
}

int Sum(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[p];
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res += Sum(p * 2, l, mid, x, y);
    if (mid < y) res += Sum(p * 2 + 1, mid + 1, r, x, y);
    return res;
}

void Upd(int p, int l, int r, int x, int y) {
    // a[x] += y, with increment
    sum[p] += y;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) Upd(p * 2, l, mid, x, y);
    else Upd(p * 2 + 1, mid + 1, r, x, y);
}

void pushup(int p) { sum[p] = sum[p * 2] + sum[p * 2 + 1]; }

void Upd(int p, int l, int r, int x, int y) {
    // a[x] += y, with pushup
    if (l == r) return sum[p] += y, void();
    int mid = (l + r) >> 1;
    if (x <= mid) Upd(p * 2, l, mid, x, y);
    else Upd(p * 2 + 1, mid + 1, r, x, y);
    pushup(p);
}

void Tag(int p, int z) { tag[p] += z, sum[p] += (R[p] - L[p] + 1) * z; }
void pushdown(int p) {
    if (tag[p]) {
        Tag(p * 2, tag[p]);
        Tag(p * 2 + 1, tag[p]);
        tag[p] = 0;
    }
}

void Upd(int p, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) return Tag(p, z);
    pushdown(p);
    int mid = (l + r) >> 1;
    if (x <= mid) Upd(p * 2, l, mid, x, y, z);
    if (mid < y) Upd(p * 2 + 1, mid + 1, r, x, y, z);
    pushup(p);
}

// Upd 只需把 z 改成标记结构体！

int Sum(int p, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[p];
    pushdown(p);
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res += Sum(p * 2, l, mid, x, y);
    if (mid < y) res += Sum(p * 2 + 1, mid + 1, r, x, y);
    return res;
}
// Sum 完全不需要修改！
*/
struct Tag {
	int A, B; // x -> Ax + B
};

Tag tag[4 * N + 5];

Tag operator+(const Tag &x, const Tag &y) {
	// 先 x 后 y
	return (Tag){x.A * y.A, x.B * y.A + y.B};
}

void maketag(int p, Tag z) {
	tag[p] = tag[p] + z;
	sum[p] = sum[p] * z.A + z.B * (R[p] - L[p] + 1);
}
// 注意调用 + 的先后顺序

void pushdown(int p) {
	if (tag[p].A != 1 || tag[p].B != 0) {
		maketag(p * 2, tag[p]);
		maketag(p * 2 + 1, tag[p]);
		tag[p] = (Tag){1, 0};
	}
}

Info Query(int p, int l, int r, int x, int y) {
	if (x <= l && r <= y) return t[p];
	int mid = (l + r) >> 1;
	if (y <= mid) return Query(p * 2, l, mid, x, y);
	if (mid < x) return Query(p * 2 + 1, mid + 1, r, x, y);
	return Query(p * 2, l, mid, x, y) + Query(p * 2 + 1, mid + 1, r, x, y);
	// 不用 res，避免赋初值
}

int Find(int p, int l, int r, int x) {
	// assume x >= 1
	if (sum[p] < x) return -1;
	if (l == r) return l;
	pushdown(p); // 别忘了！
	int mid = (l + r) >> 1;
	if (sum[p * 2] >= x) return Find(p * 2, l, mid, x);
	return Find(p * 2 + 1, mid + 1, r, x - sum[p * 2]);
	// 注意第二种情况 x 需要减掉左侧贡献
}

int Find(int p, int l, int r, int x, int y) {
	if (mx[p] < y || r < x) return -1;
	if (l == r) return l;
	pushdown(p);
	int mid = (l + r) >> 1, res = Find(p * 2, l, mid, x, y);
	if (res != -1) return res;
	return Find(p * 2 + 1, mid + 1, r, x, y);
}

void Sqrt(int p, int l, int r, int x, int y) {
	if (mx[p] <= 1) return;
	if (l == r) return sum[p] = mx[p] = sqrt(sum[p]), void();
	// 注意这里的判断条件
	int mid = (l + r) >> 1;
	if (x <= mid) Sqrt(p * 2, l, mid, x, y);
	if (mid < y) Sqrt(p * 2 + 1, mid + 1, r, x, y);
	pushup(p);
}

int sz[N + 5], dfn[N + 5], sign;
void dfs(int x) {
	sz[x] = 1, dfn[x] = ++sign;
	for (int y : g[x]) {
		dfs(y), sz[x] += sz[y];
	}
}