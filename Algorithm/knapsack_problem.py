# https://zh.wikipedia.org/wiki/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98
# https://blog.csdn.net/mu399/article/details/7722810

# 01背包的状态转换方程 f[i,j] = Max{ f[i-1,j-Wi]+Pi( j >= Wi ),  f[i-1,j] }
# f[i,j]表示前i件物品中选择若干件放在承重为j的背包中可以取得的最大价值
# 决策: 为了使背包中物品总价值最大化，第i件物品应该放入背包中吗?
# 对于f[i,j] = Max{ f[i-1,j-Wi]+Pi( j >= Wi ),  f[i-1,j] }
# f[i-1,j-Wi]+Pi 表示放入第i件物品后背包的内物品价格的总值
# f[i-1,j] 表示不放入第i件物品背包所能承载物品的(最大)价值
# f[i-1,j-Wi]+Pi中的f[i-1,j-Wi]表示在承重为j的背包中预留第i件物品的重量(Wi)(换来的价值是后面的Pi)
# f[i-1,j-Wi]则表示扣除为第i件物品的预留的重量后，剩余的承载量所能装载物品的最大价值总和