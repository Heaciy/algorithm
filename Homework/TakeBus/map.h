//
// Created by 何嘉豪 on 2020/2/25.
//

#ifndef TAKEBUS_MAP_H
#define TAKEBUS_MAP_H

#include "data.h"
#include "model.h"
#include <iostream>
#include <vector>

using namespace std;

void LoadMapData();

int FindBus(string bus);

int GetBus(string bus);

int FindStation(string station);

int GetStation(string station);

void AddBus(string bus, string pStart, string pEnd);

bool AddRoute(int nBus, int nStart, int nEnd, int distance);

int QueryStation(string pStation, string *buses);

int QueryBus(string pBus, string *route);

#endif //TAKEBUS_MAP_H
