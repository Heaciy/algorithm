#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
int a[100], b[100];
bool cmp(const int &x, const int &y) { return x > y; }
int main() {
    int n, m, i;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    // n个任务，m台机器，先输入n,m再分别输入n个任务每个任务的耗时
    cin >> n >> m;
    for (i = 0; i < n; i++)
        cin >> a[i];
    //对n个作业按时间从大到小排序
    sort(a, a + n, cmp);
    for (i = 0; i < n; i++) {
        *min_element(b, b + m) += a[i]; // b数组为机器
    }
    cout << *max_element(b, b + m);
    return 0;
}