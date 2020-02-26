#include <iostream>
#include "model.h"
#include "map.h"
#include "data.h"

using namespace std;


int main() {
    //输出界面
    cout << "=====公交管理系统=====" << endl;
    cout << "1.查询公交线路" << endl;
    cout << "2.查询站点信息" << endl;
    cout << "3.查询两个站点公交信息" << endl;
    cout << "0.退出" << endl;
//    cout << "" << endl;
    LoadMapData();
    return 0;
}
