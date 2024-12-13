#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, nxt[N];
long long s[N], a[N], b[N], sum, ans;
vector<int> to[N];
int main() {
	cin >> n;
	for (int i = 1, j = 0; i <= n; i++) {
		cin >> s[i] >> a[i] >> b[i];
		s[i] = (s[i] + ans) % n;
		while (j && s[i] != s[j + 1]) to[i].push_back(j), sum -= b[i - j];
		nxt[i] = j += (s[i] == s[j + 1] && i > 1);
		// if (s[i] == s[1]) sum += b[i];
		// for (auto x : to[nxt[i]]) sum -= b[i - x], to[i].push_back(x);
		cout << (ans += (sum + b[1]) * a[i]) << '\n';
	}
	return 0;
}