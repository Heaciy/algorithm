//
// Created by 何嘉豪 on 2020/3/1.
//
#include "menu.h"
#include "serach.h"

//打印直达路线
static void printThru(int from, int to, int bus) {
    auto routes = g_BusMap.stations[from].routes;
    if (from != to) {
        cout << g_BusMap.stations[from].name << "--" << g_BusMap.buses[bus].name << "-->";
        for (auto route: routes) {
            if (route->bus == bus)
                printThru(route->to, to, bus);
        }
    } else cout << g_BusMap.stations[from].name << endl;
}

//判断从from经bus是否能到to
static bool test(int from, int to, int bus) {
    for (const auto &route : g_BusMap.stations[from].routes) {
        if (route->bus != bus)
            continue;
        else {
            if (route->to == to) return true;
            return test(route->to, to, bus);
        }
    }
    return false;
}

//返回所有的直达方案
static pair<bool, vector<int>> isThru(int from, int to) {
    vector<int> thru;
    pair<bool, vector<int>> temp;
    for (const auto &route : g_BusMap.stations[from].routes)
        if (from != to) { if (test(from, to, route->bus)) thru.push_back(route->bus); }
        else {
            temp.first = true;
            temp.second.push_back(-1);
        }
    if (!temp.first && thru.size() == 0) {
        temp.first = false;
        return temp;
    } else {
        temp.first = true;
        temp.second = thru;
        return temp;
    }
}

//打印非直达路线
static void printTurn(int from, int to, int bus, vector<int> preStation) {
    if (isThru(from, to).first) {
        for (auto busNum:isThru(from, to).second) {
            if (busNum != bus) {//换乘站后买的bus不能与换乘站前面的bus相等(直达),否则转乘就是直达(无意义/重复输出)
                for (auto station: preStation) {
                    cout << g_BusMap.stations[station].name << "--" << g_BusMap.buses[bus].name
                         << "-->";
                }
                printThru(from, to, busNum);
            }
        }
    } else if (from != g_BusMap.buses[bus].end) {
        preStation.push_back(from);
        for (auto route:g_BusMap.stations[from].routes)
            if (route->bus == bus)
                printTurn(route->to, to, bus, preStation);
    }
}

//5.找到两站之间符合要求的路线
void takeBus() {
    string from, to;
    cout << "输入起始站 终点站(如A B):";
    int from_, to_;
    cin >> from >> to;
    while (((from_ = findStation(from)) == -1) || ((to_ = findStation(to)) == -1)) {
        cout << "输入错误!重新输入:";
        cin >> from >> to;
    }
    pair<bool, vector<int>> temp = isThru(from_, to_);
    if (temp.first) {//如果可以直达
        for (auto bus:temp.second) printThru(from_, to_, bus);
    } else {//不能直达
        cout << "两站不能直达!"<<endl;
    }
    //需要中转的路线
    list<const Route *> routeFrom = g_BusMap.stations[from_].routes;
    vector<int> preStation;
    for (auto route:routeFrom) {
        if(from_!=to_){
            preStation.push_back(from_);
            printTurn(route->to, to_, route->bus, preStation);
            preStation.clear();
        }
    }
}
