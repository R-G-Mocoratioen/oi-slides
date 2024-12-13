#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng;
int rnd(int l, int r) { return l + rng() % (r - l + 1); }
int rrnd(int l, int r) { return ((rnd(0, 1) || l == r) ? r : rrnd(l, r - 1)); }
int pl[10005];
    int main() {
	unsigned long long seed;
	freopen("seed.txt", "r", stdin);
	cin >> seed;
	rng = mt19937_64(seed);
	freopen("seed.txt", "w", stdout);
	cout << rng() + time(0) << endl;
	freopen("1.in", "w", stdout);
	/*int n = rrnd(1, 10);
	cout << n << endl;
	for (int i = 1; i <= n; i++) pl[i] = i;
	shuffle(pl + 1, pl + n + 1, rng);
	for (int i = 2; i <= n; i++) {
	    int x = pl[i], y = pl[rnd(max(1, i - 5), i - 1)];
	    if (rnd(0, 1)) swap(x, y);
	    cout << x << ' ' << y << endl;
	}*/
	// 建造军营
	// 边双结构比较复杂
	// 边的跨度不能太大
	// 5 个点五个点地加
	/*for (int i = 1; i <= n; i += 5) {
	    // 在 [i,i+4] 之间随机连 [1,10] 条边
	    // [i,i+4] 和之前的某个 [i-k*5,i-k*5+4] 连一条边
	}*/
	// 字符串
	// 字符集不要太大 a,b
	// SSSSSSSS
}
