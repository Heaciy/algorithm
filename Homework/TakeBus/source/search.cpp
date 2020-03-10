//
// Created by 何嘉豪 on 2020/3/8.
//

#include "menu.h"

int MAX_CHANGE_NUM = 1;//最大换乘次数

static void doSearch(int index, int target, list<int> &visited,
                     list<const Route *> &routes,
                     vector<list<const Route *>> &results,
                     int changed) {
    visited.emplace_back(index);
    for (auto route:g_BusMap.stations[index].routes) {
        bool flag = true;
        for (auto station: visited) {
            if (route->to == station) {
                flag = false;
                break;
            }
        }
        if (flag) { //如果该route符合要求
            int tmp = changed; //用于判断在运行过程中changed是否改变(changed++)了,若发生改变，则在回溯时将其复原(changed--)
            if (!routes.empty() && route->bus != routes.back()->bus) changed += 1;//换乘次数加一
            if (changed <= MAX_CHANGE_NUM) {//换乘次数小于最大换乘次数限制
                routes.emplace_back(route);
                if (route->to == target) {
                    results.emplace_back(routes);
                    routes.pop_back();
                    if (changed > tmp) changed--;
                } else {
                    doSearch(route->to, target, visited, routes, results, changed);
                    if (changed > tmp) changed--;
                }
            } else {
                if (changed > tmp) changed--;
                continue;
            }
        }
    }
    visited.pop_back();
    if (!routes.empty()) routes.pop_back();
}

void takeBus_() {
    string from, to;
    cout << "输入起始站 终点站(如A B):";
    int from_, to_;
    cin >> from >> to;
    while (((from_ = findStation(from)) == -1) || ((to_ = findStation(to)) == -1)) {
        cout << "输入错误!重新输入:";
        cin >> from >> to;
    }
    list<int> visited;
    list<const Route *> routes;
    vector<list<const Route *>> results;
    int changed = 0;
    doSearch(from_, to_, visited, routes, results, changed);
    for (const auto &result : results) {
        for (const auto &route : result) {
            cout << g_BusMap.buses[route->bus].name << ": "
                 << g_BusMap.stations[route->from].name << "-->"
                 << g_BusMap.stations[route->to].name << endl;
        }
        cout << "----------" << endl;
    }
}