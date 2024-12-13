import random

N = 100000000  # 模拟次数
total = 0.0
for i in range(N):
    x = random.uniform(1, 2)
    y = random.uniform(1, 2)
    z = random.uniform(1, 2)
    total += x + y**z
expected_value = total / N
print(expected_value)
