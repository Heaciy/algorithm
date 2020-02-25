//
// Created by 何嘉豪 on 2020/2/25.
//

#ifndef TAKEBUS_MODEL_H
#define TAKEBUS_MODEL_H

#include <string>

using namespace std;

typedef struct Bus {
    string name; // 名字
    int start; // 起点
    int end; // 终点
} Bus;

typedef struct Route {
    int station; // 指向站点的索引号
    int bus; // 公交索引号
    int distance; // 两站之间的距离
    struct Route* next; // 起始站点相同的，下一条下行路线
} Route;

typedef struct Station {
    string station; // 站点名
    struct Route *routes; // 从该点出发的所有下行路线的链域
} Station;

typedef struct BusMap {
    Bus *buses; // 公交线路数组
    Station *stations; // 站点数组
    int station_num; // 站点数
    int bus_num; // 公交线路数
} BusMap;

#endif // TAKEBUS_MODEL_H
