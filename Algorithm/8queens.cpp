#include <iostream>
using namespace std;

int QUEEN[20], N;         // N为皇后数
int COLUMN[20];           // 记录列被占用的情况
int MAIN_DIAGONAL[40];    // 记录主对角线被占用的情况
int COUNTER_DIAGONAL[20]; // 记录副对角线被占用的情况

void dfs(int n);   // n个皇后，深度优先搜索
bool check(int n); // 第n个皇后与第1至n-1个皇后有没有冲突
// 不可行返回false,可行返回true
void output(int n); // 输出n个皇后的位置

int main() {
    int i;
    cout << "输入N值:";
    cin >> N;
    // 初始化
    for (i = 1; i <= N; i++)
        COLUMN[i] = 0;
    for (i = 1; i <= 2 * N - 1; i++)
        MAIN_DIAGONAL[i] = 0;
    for (i = 2; i < 2 * N; i++)
        COUNTER_DIAGONAL[i] = 0;
    dfs(N);
    return 0;
}

void dfs(int n) {
    int i, j;
    QUEEN[i] = 0;
    i = 1; // i是行号
    while (i > 0) {
        QUEEN[i]++;
        while (QUEEN[i] <= N && !check(i)) // 当前列不可行
            QUEEN[i]++;
        if (QUEEN[i] <= N) {
            if (i == N)
                output(N);
            else { // 纪录列、对角线资源占用
                j = QUEEN[i];
                COLUMN[j] = 1;
                MAIN_DIAGONAL[i - j + N] = 1;
                COUNTER_DIAGONAL[i + j] = 1;
                i++;
                QUEEN[i] = 0;
            }
        } else { // 回到上一行，上一行的皇后当前位置不可行
            i--;
            if (i <= 0)
                break;
            j = QUEEN[i]; // 释放列、对角线资源
            COLUMN[j] = 0;
            MAIN_DIAGONAL[i - j + N] = 0;
            COUNTER_DIAGONAL[i + j] = 0;
        }
    }
}

bool check(int i) {
    int j; // j是第i行的皇后所在列号
    j = QUEEN[i];
    if (COLUMN[j] == 1 || MAIN_DIAGONAL[i - j + N] == 1 ||
        COUNTER_DIAGONAL[i + j] == 1)
        return false; //当前列不可行
    else
        return true;
}

void output(int n) {
    int i;
    for (i = 1; i <= n; i++)
        cout << QUEEN[i] << " ";
    cout << endl;
}