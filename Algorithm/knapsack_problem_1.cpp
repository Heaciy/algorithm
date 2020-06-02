// https://zh.wikipedia.org/wiki/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98
// https://blog.csdn.net/mu399/article/details/7722810//

// 动态规划解法
// 01背包的状态转换方程 f[i,j] = Max{ f[i-1,j-Wi]+Pi( j >= Wi ),  f[i-1,j] }
// f[i,j]表示前i件物品中选择若干件放在承重为j的背包中可以取得的最大价值
// 决策: 为了使背包中物品总价值最大化，第i件物品应该放入背包中吗?
// 对于f[i,j] = Max{ f[i-1,j-Wi]+Pi( j >= Wi ),  f[i-1,j] }
// f[i-1,j-Wi]+Pi 表示放入第i件物品后背包的内物品价格的总值
// f[i-1,j] 表示不放入第i件物品背包所能承载物品的(最大)价值
// f[i-1,j-Wi]+Pi中的f[i-1,j-Wi]表示在承重为j的背包中预留第i件物品的重量(Wi:
// 换来的价值是后面的Pi)
// f[i-1,j-Wi]则表示扣除为第i件物品的预留的重量后，剩余的承载量所能装载物品的最大价值总和

#include <iostream>
#include <vector>
using namespace std;

vector<int> items; // 当价值最大时背包内所装的物品
int n;             // 物品个数
int Capacity;      // 背包的容量
int *Weight;       // Weight[i]表示物品的重量
int *Profit;       // Profit[i]表示物品的价值
int **table;       // 构建的表(二维数组)
int pMaxProfit;    //最大价值

void init();
void packageItem();
void output();

void init() {
    n = 5;
    Capacity = 10;
    Weight = new int[n]{2, 2, 6, 5, 4};
    Profit = new int[n]{6, 3, 5, 4, 6};
    table = new int *[n + 1]; // 初始化表
    for (int i = 0; i < n + 1; i++)
        table[i] = new int[Capacity + 1]{0};
}

void packageItem() {
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < Capacity + 1; j++) {
            if (Weight[i - 1] <= j)
                pMaxProfit = table[i - 1][j - Weight[i - 1]] + Profit[i - 1];
            else
                pMaxProfit = table[i - 1][j];
            table[i][j] =
                pMaxProfit > table[i - 1][j] ? pMaxProfit : table[i - 1][j];
        }
    }
    // find answer
    int curSize = Capacity;
    for (int i = n; i > 0; i--) {
        if (curSize == 0) {
            break;
        }
        if (i == 1 && curSize > 0) {
            items.push_back(i);
            break;
        }
        if (table[i][curSize] - table[i - 1][curSize - Weight[i - 1]] ==
            Profit[i - 1]) {
            items.push_back(i);
            curSize -= Weight[i - 1];
        }
    }
}

void output() {
    cout << table[n][Capacity] << endl;
    for (auto &item : items)
        cout << "item" << item << endl;
}

int main() {
    init();
    packageItem();
    output();
}