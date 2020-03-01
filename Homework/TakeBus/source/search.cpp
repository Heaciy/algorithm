//
// Created by �μκ� on 2020/3/1.
//
#include "menu.h"
#include "serach.h"

//��ӡֱ��·��
static void printThru(int from, int to, int bus) {
    auto routes = g_BusMap.stations[from].routes;
    if (from != to) {
        cout << g_BusMap.stations[from].name << "--" << g_BusMap.buses[bus].name << "-->(T)";
        for (auto route: routes) {
            if (route->bus == bus)
                printThru(route->to, to, bus);
        }
    } else cout << g_BusMap.stations[from].name << endl;
}

//�жϴ�from��bus�Ƿ��ܵ�to
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

//�������е�ֱ�﷽��
static pair<bool, vector<int>> isThru(int from, int to) {
    vector<int> thru;
    pair<bool, vector<int>> temp;
    for (const auto &route : g_BusMap.stations[from].routes)
        if (test(from, to, route->bus)) thru.push_back(route->bus);
    if (thru.size() == 0) {
        temp.first = false;
        return temp;
    } else {
        temp.first = true;
        temp.second = thru;
        return temp;
    }
}

//��ӡ��ֱ��·��
static void printTurn(int from, int to, int bus, vector<int> preStation) {
    if (isThru(from, to).first) {
        for (auto busNum:isThru(from, to).second) {
            cout << "bus:" << bus << "busNum" << busNum << endl;
            if (busNum != bus) {//����վ�����bus�����뻻��վǰ���bus���(ֱ��),����ת�˾���ֱ��(������/�ظ����)
                for (auto station: preStation) {
                    cout << g_BusMap.stations[station].name << "--" << g_BusMap.buses[bus].name << "(" << bus << ")"
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

//5.�ҵ���վ֮�����Ҫ���·��
void takeBus() {
    string from, to;
    cout << "������ʼվ �յ�վ(��A B):";
    int from_, to_;
    cin >> from >> to;
    while (((from_ = findStation(from)) == -1) || ((to_ = findStation(to)) == -1)) {
        cout << "�������!��������:";
        cin >> from >> to;
    }
    pair<bool, vector<int>> temp = isThru(from_, to_);
    if (temp.first) {//�������ֱ��
        for (auto bus:temp.second) printThru(from_, to_, bus);
    } else {//����ֱ��
        cout << "��վ����ֱ��!";
    }
    //��Ҫ��ת��·��
    list<const Route *> routeFrom = g_BusMap.stations[from_].routes;
    vector<int> preStation;
    for (auto route:routeFrom) {
        preStation.push_back(from_);
        printTurn(route->to, to_, route->bus, preStation);
        cout << "\n--------------------------------" << endl;
        preStation.clear();
    }
}
