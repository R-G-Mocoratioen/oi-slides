#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
const int mod = 998244353;
mt19937 rng(time(0));
int main() {
	freopen("1.in", "w", stdout);
	puts("20");
	for (int i = 1; i <= 20; i++) {
		puts("60");
		for (int j = 1; j <= 60; j++) {
			for (int k = 1; k <= 60; k++) {
				cout << (rng() % 100 == 0);
			}
			cout << '\n';
		}
	}
}