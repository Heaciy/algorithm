//
// Created by 何嘉豪 on 2020/2/25.
//

#ifndef TAKEBUS_DATA_H
#define TAKEBUS_DATA_H

#include <string>
using namespace std;

#define  ROUTE_NUM 18 // 线路中路段数目
#define  BUS_NUM 6 // 公交车数目
#define  STATION_NUM 7 //公交站数目

extern int ROUTES[ROUTE_NUM][4];
extern string  BUSES[BUS_NUM][3];
extern string STATION[STATION_NUM];


#endif //TAKEBUS_DATA_H
