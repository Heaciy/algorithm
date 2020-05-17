#include <iostream>
using namespace std;

typedef struct Position {
    int y; //行坐标
    int x; //列坐标
} Position;

void output(Position *seq, int index);

bool check(int newy, int newx);

//地图
int MAZE[5][5] = {{0, 1, 1, 1, 1},
                  {0, 0, 0, 0, 1},
                  {1, 0, 1, 1, 1},
                  {1, 0, 0, 0, 1},
                  {1, 1, 1, 0, 0}};

int main() {
    int y = 0, x = 0, index = 0, k;
    Position seq[100];
    int fy[4] = {0, 0, -1, 1}, fx[4] = {1, -1, 0, 0};
    int newy, newx;
    seq[0].y = 0;
    seq[0].x = 0;
    MAZE[0][0] = 3; //标记当前点为3，表示走过的点
    while (index >= 0) {
        for (k = 0; k <= 3; k++) {
            newy = y + fy[k];
            newx = x + fx[k];
            if (check(newy, newx)) { //新点可行
                index++;
                seq[index].y = newy;
                seq[index].x = newx;
                y = newy;
                x = newx;
                MAZE[y][x] = 3; //标记当前点为3，表示走过的点
                if (newy == 4 && newx == 4) {
                    output(seq, index);
                    return 0;
                }
                break;
            }
        }
        if (k == 4) {       //在当前点（y,x）无路可走，需回溯
            MAZE[y][x] = 2; //把当前点（死胡同）标记为2
            index--;
            y = seq[index].y;
            x = seq[index].x;
        }
    }
    printf("没有可行路径");
}

void output(Position *seq, int index) {
    int i;
    for (i = index; i >= 0; i--) {
        printf("y=%d,", seq[i].y);
        printf("x=%d\n", seq[i].x);
    }
}

bool check(int newy, int newx) {
    if (newy < 0 || newy >= 5 || newx < 0 || newx >= 5) //越界
        return false;
    // 1是墙，2是死胡同， 3是走过的点 
    if (MAZE[newy][newx] != 0) return false;
    return true;
}