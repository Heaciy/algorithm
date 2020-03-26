#include <iostream>
using namespace std;
const int n = 10;

int main() {
    int i, j, t, flag = 1; // flag用于优化冒泡排序
    int a[n] = {8, 9, 10, 7, 6, 5, 4, 3, 2, 1};
    for (i = 0; i < n - 1; i++) {
        if (flag == 1) {
            flag = 0;
            for (j = 0; j < n - 1 - i; j++) {
                if (a[j] > a[j + 1]) {
                    t = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = t;
                    flag = 1;
                }
            }
        } else
            break;
    }
    for (i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
}