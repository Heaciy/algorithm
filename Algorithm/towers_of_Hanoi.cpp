#include <iostream>
using namespace std;

int counter = 0;

void move(int disks, string m, string n) {
    cout << "第" << ++counter << "次移动: 把" << disks << "号圆盘从" << m
         << "移动到" << n << endl;
}

void hanoi(int n, string a, string b, string c) {
    if (n == 1)
        move(1, a, c); // 圆盘只有一个时，只需将其从A塔移到C塔
    else {
        // 递归，把A塔上编号1~n-1的圆盘移到B上，以C为辅助塔
        hanoi(n - 1, a, c, b);
        move(n, a, c); // 把A塔上编号为n的圆盘移到C上
        // 递归，把B塔上编号1~n-1的圆盘移到C上，以A为辅助塔
        hanoi(n - 1, b, a, c);
    }
}

int main() {
    string A = "A";
    string B = "B";
    string C = "C";
    int n;
    cout << "Input disks num n:";
    cin >> n;
    hanoi(n, A, B, C);
}