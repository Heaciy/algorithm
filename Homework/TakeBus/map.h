//
// Created by 何嘉豪 on 2020/2/25.
//

#ifndef TAKEBUS_MAP_H
#define TAKEBUS_MAP_H

#include "data.h"
#include "model.h"

BusMap BusMap_g;

void LoadMapData(BusMap* BusMap_g);

int FindBus(string bus);

int GetBus(string bus);

int FindStation(string station);

int GetStation(string station);

void AddBus(string bus, string pStart, string pEnd);

bool AddRoute(string pBus, string pStart, string pEnd, int distance);

#endif //TAKEBUS_MAP_H
