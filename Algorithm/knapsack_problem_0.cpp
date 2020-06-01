// https://blog.csdn.net/sinat_35261315/article/details/71512308
// 有n个物品和一个容量为c的背包，从n个物品中选取装包的物品。
// 物品i的重量为w[i]，价值为p[i]。
// 一个可行的背包装载是指，装包的物品总重量不超过背包的重量。
// 一个最佳背包装载是指，物品总价值最高的可行的背包装载。
// 我们要求出x[i]的值。x[i] == 1表示物品i装入背包，x[i] ==
// 0表示物品i没有装入背包。 问题的公式描述是：
//总价值最高的可能的背包装载，x[i]只能等于0或者1
// max { p[1] * x[1] + p[2] * x[2] + ... + p[i] * x[i] + ... + p[n] * x[n] }

#include <iostream>
#include <math.h>
using namespace std;

int *Weight;  // Weight[i]表示物品的重量
int *Profit;  // Profit[i]表示物品的价值
int n;        // 物品个数
int Capacity; // 背包的容量
int *pTree; // 解空间树pTree[i]表示节点i的重量，同时又可以判断是否装入物品i
int pNodeSize;  // 节点数量
int pLastNode;  // 最优解的叶子节点索引
int pMaxProfit; // 最优解的值，初始为0
int pHeight;    // 当前高度，初始为0，始终表示当前结点的高度
int pCurrentProfit; // 当前价值量，初始为0
int pCurrentWeight; // 当前加入背包的总重量，初始为0
int pRemainingProfit; // 剩余的物品总价值
void init(int n);
void Backpack(size_t pCurrentNode);
void output();

void init(int n) {
    //节点个数为2的n+1次方-1
    size_t pNodeSize = pow(2, n + 1) - 1;
    //根节点的索引为1,权值为0
    pTree = new int[pNodeSize + 1]; // 数组从1开始计算
    pTree[1] = 0;
    size_t pStartNode;
    for (size_t pHeight = 1; pHeight <= n; pHeight++) {
        pStartNode =pow(2, pHeight); // 高度为pHeight的第一个节点的索引为2的pHeight次方
        for (size_t i = pStartNode; i < pStartNode * 2; i += 2) {
            pTree[i] = Weight[pHeight]; // 左孩子权重为其质量
            pTree[i + 1] = 0;
        }
    }
}
void Backpack(size_t pCurrentNode) {
    // 到达叶子节点，更新最优解，记录最优解的叶子结点
    if (pCurrentNode * 2 > pNodeSize) {
        if (pCurrentProfit > pMaxProfit) {
            pMaxProfit = pCurrentProfit;
            pLastNode = pCurrentNode;
        }
        return;
    }
    // 高度加一，此时表示的是下一个物品（pCurrentNode左孩子和右孩子表示的物品）
    pHeight++;
    //如果pCurrentNode表示物品i,则加一后的pHeight表示物品i+1，pRemainingProfit应该把物品i+1的价值减掉
    pRemainingProfit-=Profit[pHeight];

    if (pCurrentWeight + Weight[pHeight] <= Capacity) {
        pCurrentWeight += Weight[pHeight];
        pCurrentProfit += Profit[pHeight];
        Backpack(pCurrentNode *
                 2); // 跳转到左孩子，表示将物品i+1(pHeight)装入背包
        // 回溯到该节点后，物品i+1装入背包的情况已经考虑完，开始考虑物品i+1没有装入的情况
        // 将物品i+1的重量和价值减去
        pCurrentWeight -= Weight[pHeight];
        pCurrentProfit -= Profit[pHeight];
    }
    // 跳转到右孩子节点，表示物品i+1(pHeight)没有装入背包
    if (pRemainingProfit+pCurrentProfit > pMaxProfit)
        Backpack(pCurrentNode * 2 + 1);
    // 返回后回溯到该节点,物品i+1没有装入的情况也已经考虑完，需向上回溯，高度减一
    pHeight--;
}
void output(){
    pHeight = n;
    while(pLastNode!=1){
        if(pTree[pLastNode] == 0)
            cout<<"Backpack"<<pHeight<<":"<< 0 <<endl;
        else
            cout<<"Backpack"<<pHeight<<":"<< 1 <<endl;
        pLastNode/=2;
        pHeight--;
    }
}

int main() {
    cout<<"Input num n: ";
    cin>>n;
    init(n);
    Backpack(1);
    output();
}