#include <cstring>
#include <iostream>
using namespace std;

int main() {
    long b, c, d;
    int a[256], i, j, n;
    char s1[256];
    cout << "input a great number:";
    cin >> s1;
    cout << "input a long integet:";
    cin >> c;
    n = strlen(s1);
    d = 0; //进位
    for (i = 0, j = n - 1; i < n; i++, j--) {
        b = (s1[j] - 48) * c + d;
        a[i] = b % 10; //取最后一位(个位数)
        d = b / 10;    //进位
    }
    while (d > 0) {
        a[n] = d % 10;
        d /= 10;
        n++;
    }
    while (n - 1 >= 0) {
        cout << a[n - 1];
        n--;
    }
    return 0;
}