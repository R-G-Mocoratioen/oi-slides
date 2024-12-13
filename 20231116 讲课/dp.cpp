#include <bits/stdc++.h>
using namespace std;
int ptr = 1000000;
char buf[1000005];
char gc() {
	if (ptr >= 1000000) ptr = 0, fread(buf, 1, 1000000, stdin);
	return buf[ptr++];
}
int rd() {
	int x = 0;
	char ch = gc();
	while (!isdigit(ch)) ch = gc();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
	return x;
}
int main() {
	int n = rd();
	int s = 0;
	while (n--) s += rd();
	cout << s;
}
// 1 2 3
