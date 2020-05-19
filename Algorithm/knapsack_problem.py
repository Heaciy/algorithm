# https://zh.wikipedia.org/wiki/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98
# https://blog.csdn.net/mu399/article/details/7722810

# 01背包的状态转换方程 f[i,j] = Max{ f[i-1,j-Wi]+Pi( j >= Wi ),  f[i-1,j] }
# f[i,j]表示前i件物品中选择若干件放在承重为j的背包中可以取得的最大价值
# 决策: 为了使背包中物品总价值最大化，第i件物品应该放入背包中吗?
# 对于f[i,j] = Max{ f[i-1,j-Wi]+Pi( j >= Wi ),  f[i-1,j] }
# f[i-1,j-Wi]+Pi 表示放入第i件物品后背包的内物品价格的总值
# f[i-1,j] 表示不放入第i件物品背包所能承载物品的(最大)价值
# f[i-1,j-Wi]+Pi中的f[i-1,j-Wi]表示在承重为j的背包中预留第i件物品的重量(Wi: 换来的价值是后面的Pi)
# f[i-1,j-Wi]则表示扣除为第i件物品的预留的重量后，剩余的承载量所能装载物品的最大价值总和

from collections import namedtuple

# PackageItem = namedtuple("PackageItem",['name','weight','value'])

# items = {'a': [2, 6], 'b': [2, 3], 'c': [6, 5], 'd': [5, 4], 'e': [4, 6]}
items = {'e': [4, 6], 'd': [5, 4], 'c': [6, 5], 'b': [2, 3], 'a': [2, 6]}
keys = list(items.keys())
# 背包最大承重
weight = int(input("input the max weight of package:"))
# 构造表格
table = [[0]*(weight+1) for i in range(len(items)+1)]

for i in range(1, len(items)+1):
    for j in range(1, weight+1):
        if items[keys[i-1]][0] <= j:
            y = table[i-1][j-items[keys[i-1]][0]]+items[keys[i-1]][1]
        else:
            y = table[i-1][j]
        n = table[i-1][j]
        table[i][j] = max(y,n)

print(table)
