//
// Created by 何嘉豪 on 2020/2/25.
//

#include "map.h"

using namespace std;
BusMap g_sMap;

void LoadMapData() {
    g_sMap.bus_num = BUS_NUM;
    g_sMap.buses = (Bus *) malloc(sizeof(Bus) * BUS_NUM);
    for (int i = 0; i < BUS_NUM; i++) {
        g_sMap.buses[i].name = BUSES[i][0];
        g_sMap.buses[i].start = g_sMap.buses[i].end = -1;
    }
    g_sMap.station_num = STATION_NUM;
    g_sMap.stations = (Station *) malloc(sizeof(Station) * STATION_NUM);
    for (int i = 0; i < STATION_NUM; i++) {
        g_sMap.stations[i].station = STATION[i]; // 初始化站点名
        g_sMap.stations[i].routes = NULL; // 下行路线暂时设置为空
    }
    for (int i = 0; i < BUS_NUM; i++) {
        AddBus(BUSES[i][0], BUSES[i][1], BUSES[i][2]);
    }
    for (int i = 0; i < BUS_NUM; i++) {
        AddRoute(ROUTES[i][0],ROUTES[i][1],ROUTES[i][2],ROUTES[i][3]);
    }
}

int FindBus(string bus) {
    for (int i = 0; i < g_sMap.bus_num; i++) {
        if (g_sMap.buses[i].name == bus) {
            return i;
        }
    }
    return -1;
}

int GetBus(string bus) {
    int nBus = FindBus(bus);
    if (nBus == -1) {
        g_sMap.buses = (Bus *) realloc(g_sMap.buses, sizeof(Bus) * (g_sMap.bus_num + 1));
        Bus *pBus = g_sMap.buses + g_sMap.bus_num;
        pBus->name = bus;
        pBus->start = pBus->end = -1;
        nBus = g_sMap.bus_num;
        g_sMap.bus_num++;
    }
    return nBus;
}

int FindStation(string station) {
    for (int i = 0; i < g_sMap.station_num; i++) {
        if (g_sMap.stations[i].station == station) {
            return i;
        }
    }
    return -1;
}

int GetStation(string station) {
    int nStation = FindStation(station);
    if (nStation == -1) {
        g_sMap.stations = (Station *) realloc(g_sMap.stations, sizeof(Station) * g_sMap.station_num + 1);
        Station *pStation = g_sMap.stations + g_sMap.station_num;
        pStation->station = station;
        pStation->routes = NULL;
        g_sMap.station_num++;
    }
    return nStation;
}

void AddBus(string bus, string pStart, string pEnd) {
    int nBus = GetBus(bus);
    int nStart = GetStation(pStart);
    int nEnd = GetStation(pEnd);
    Bus *pBus = g_sMap.buses + nBus;
    pBus->start = nStart;
    pBus->end = nEnd;
}

bool AddRoute(string pBus, string pStart, string pEnd, int distance) {
    int nBus = GetBus(pBus);
    int nStart = GetStation(pStart);
    int nEnd = GetStation(pEnd);
    Station *pStStation = &g_sMap.stations[nStart];
    Route *pStRoute = pStStation->routes; // 数组的第一个route
    while (pStRoute != NULL && pStRoute->next != NULL) {
        if (pStRoute->bus == nBus && pStRoute->station == nEnd) {
            return false;
        }
        pStRoute = pStRoute->next; // 起始点相同的route(属于不同路线)
    }
    // 未找到与之匹配的,则创建新的路线
    Route *pNewRoute = (Route *) malloc(sizeof(Route));
    pNewRoute->bus = nBus;
    pNewRoute->station = nEnd;
    pNewRoute->distance = distance;
    pNewRoute->next = NULL;
    //若是起始顶点的第一条边
    if (pStRoute == NULL) {
        pStStation->routes = pNewRoute;
    } else {
        pStRoute->next = pNewRoute;
    }
    return true;
}