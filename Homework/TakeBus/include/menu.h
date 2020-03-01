//
// Created by ºÎ¼ÎºÀ on 2020/2/27.
//

#ifndef TAKEBUS_MENU_H
#define TAKEBUS_MENU_H

#include <algorithm>
#include "map.h"

using namespace std;

void printMenu();

static int findBus(string name);

static int findRoute(int from, int to, int bus);

int findStation(string name);

static void listBuses();

static void printStationInfo();

static void doPrintBusInfo(int station, int bus);

static void printBusInfo();

static void addStation();

static void changeStation();

static void deleteStation();

static void addRoute(int from, int to, int bus, int distance);

static void changeRoute(int from, int to, int bus, int distance);

static void deleteRoute(int from, int to, int bus);

static void deleteBus(string name);

static void addBus(string name);

static void changeBus();

static vector<int> enter_check();

static void doAddRoute();

static void doChangeRoute();

static void doDeleteRoute();

static void doDeleteBus();

static void doAddBus();

void run(int index);

#endif //TAKEBUS_MENU_H
