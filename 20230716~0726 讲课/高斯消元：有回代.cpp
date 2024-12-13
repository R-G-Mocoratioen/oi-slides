#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const db eps = 1e-8;
int n;
db a[105][105], ans[105];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n + 1; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		db mx = -1;
		int mxp = i;
		for (int j = i; j <= n; j++) {
			if (fabs(a[j][i]) > mx) {
				mx = fabs(a[j][i]), mxp = j;
			}
		}
		if (mx < eps)
			return puts("No Solution"), 0;
		for (int j = i; j <= n + 1; j++)
			swap(a[i][j], a[mxp][j]);
		for (int j = i + 1; j <= n; j++) {
			db v = a[j][i] / a[i][i];
			for (int k = i; k <= n + 1; k++) {
				a[j][k] -= a[i][k] * v;
			}
		}
	}
	for (int i = n; i >= 1; i--) {
		ans[i] = a[i][n + 1] / a[i][i];
		for (int j = i - 1; j >= 1; j--)
			a[j][n + 1] -= a[j][i] * ans[i];
	}
	for (int i = 1; i <= n; i++)
		printf("%.2lf\n", ans[i]);
}