#include <iostream>
using namespace std;

void output(int *color);

bool colorSame(int (*data)[7], int *color, int index);

int main() {
    int data[7][7] = {{0, 1, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 1, 0},
                      {0, 0, 0, 1, 0, 0, 1}, {0, 1, 1, 0, 0, 1, 1},
                      {1, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 1, 0, 0, 0},
                      {1, 0, 1, 1, 1, 0, 0}};

    int color[7], i, k;
    color[0] = 0;
    for (i = 1; i <= 6; i++) {
        color[i] = -1;
    }
    i = 1;
    while (i >= 0) { // 考虑当前区域的编号是i
        color[i]++;
        while (color[i] <= 3) {
            if (!colorSame(data, color, i)) { // i与之前的区域无冲突
                if (i == 6) {                 // 结束(程序出口)
                    output(color);
                    return 0;
                }
                i++;   // 考虑下一个区域
                break; // 小循环结束
            } else {   // 考虑区域i的下一种颜色
                color[i]++;
            }
        }
        if (color[i] == 4) //当前区域涂任何颜色都不行，需回溯
            i--;
    }
    cout << "None\n" << endl;
}

void output(int *color) {
    for (int i = 0; i <= 6; i++) {
        cout << "color[" << i << "] = " << color[i] << endl;
    }
}

bool colorSame(int (*data)[7], int *color, int index) {
    for (int i = 0; i < index; i++) {
        if (data[i][index] == 1 && color[i] == color[index])
            return true;
    }
    return false;
}