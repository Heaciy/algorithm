#include <cmath>
#include <time.h>
#include <iostream>
using namespace std;

void a();               //求一个数阶乘末尾有多小个0
int modx(int n, int x); // 若一个数(n)的因子中包含x^y，则返回y的最大值
                        //长整数的阶乘

int main() {
    // clock_t start;
    a();
    // cout << "Cost " << (double)(clock() - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}

//封装到Class中？？？
int modx(int n, int x) {
    int i, tmp = 0;
    if (n % x == 0) {
        return tmp + 1 + modx(n / x, x);
    } else {
        return 0;
    }
}

void a() {
    int n, temp = 0;
    cout << "input the number n:";
    cin >> n;
    for (int i = n; i >= 5; i--) { // 可优化(5的倍数)
        temp += modx(i, 5);
    }
    cout << "the number of 0: " << temp << endl;
}