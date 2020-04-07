#include <iostream>
using namespace std;

//输出各种数字图形

//使用一个一维数组输出杨辉三角
void yh();

int main() { yh(); }

void yh() {
    int n, a[100];
    cout << "input num n:";
    cin >> n;
    a[0] = 1;
    a[1] = 1;
    if (n > 0)
        cout << a[0] << endl;
    if (n > 1)
        cout << a[0] << " " << a[1] << endl;
    if (n > 2) {
        for (int i = 3; i <= n; i++) {
            a[i-1] = 1;
            for (int j = i - 2; j > 0; j--) {
                a[j] = a[j] + a[j - 1];
            }
            for (int k = 0; k < i - 1; k++)
                cout << a[k] << ' ';
            cout << a[i - 1] << endl;
        }
    }
}