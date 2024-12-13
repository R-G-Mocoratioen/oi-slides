#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi = acos(-1);
struct point {
	int x, y, id;
} a[105];
ll Dot(point x, point y) { return 1ll * x.x * y.x + 1ll * x.y * y.y; }
ll Cross(point x, point y) { return 1ll * x.x * y.y - 1ll * x.y * y.x; }
ll Dis(point x, point y) {
	return 1ll * (x.x - y.x) * (x.x - y.x) + 1ll * (x.y - y.y) * (x.y - y.y);
}
point operator+(point x, point y) { return {x.x + y.x, x.y + y.y}; }
point operator-(point x, point y) { return {x.x - y.x, x.y - y.y}; }
int st[105], top, n;
double ang[105], ans[105];
bool cmp(point x, point y) {
	if (Cross(x - a[1], y - a[1])) return Cross(x - a[1], y - a[1]) > 0;
	return Dis(a[1], x) < Dis(a[1], y);
}
int main() {
	cin >> n;
	int mny = 1e9, mnx = 1e9, mnp = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x >> a[i].y, a[i].id = i;
		if (a[i].y < mny) mny = a[i].y, mnx = a[i].x, mnp = i;
		else if (a[i].y == mny && a[i].x < mnx) mnx = a[i].x, mnp = i;
	}
	swap(a[mnp], a[1]), sort(a + 2, a + n + 1, cmp);
	st[++top] = 1, st[++top] = 2;
	for (int i = 3; i <= n; i++) {
		while (top > 1 && Cross(a[st[top]] - a[st[top - 1]], a[i] - a[st[top - 1]]) <= 0) top--;
		st[++top] = i;
	}
	st[0] = st[top];
	for (int i = 1; i <= top; i++) {
		ang[i] = atan2(a[st[i - 1]].x - a[st[i]].x, a[st[i]].y - a[st[i - 1]].y);
		if (ang[i] < ang[1]) ang[i] += 2 * pi;
	}
	ang[top + 1] = ang[1] + 2 * pi;
	for (int i = 1; i <= top; i++) ans[a[st[i]].id] = (ang[i + 1] - ang[i]) / (2 * pi);
	for (int i = 1; i <= n; i++) printf("%.10lf\n", ans[i]);
}