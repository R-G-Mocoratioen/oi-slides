int st[N + 5], top;

st[0] = top = 0; // 特别是多次单调栈不能忘！
for (int i = 1; i <= n; i++) {
	while (top && a[i] >= a[st[top]]) top--;
	st[++top] = i;
	// 此时 st 就存储了 [1..i] 的后缀最大值
}

st[0] = top = 0;
for (int i = 1; i <= n; i++) {
	while (top && a[i] >= a[st[top]]) top--;
	st[++top] = i;
	for (int j = 1; j <= top; j++) {
		printf("%d\n", st[j]);
	}
}