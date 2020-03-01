//
// Created by �μκ� on 2020/2/29.
//
#include "menu.h"
#include "serach.h"

void printMenu() {
    cout << "=====��������ϵͳ=====" << "\n"
         << "1.\t�鿴����վ��" << "\n"
         << "2.\t�鿴���й���" << "\n"
         << "3.\t��ѯվ����Ϣ" << '\n'
         << "4.\t��ѯ������·" << '\n'
         << "5.\t��ѯ·��" << '\n'
         << "6.\t���վ��" << '\n'
         << "7.\t�޸�վ��" << '\n'
         << "8.\tɾ��վ��" << '\n'
         << "9.\t�����·" << '\n'
         << "10.\t�޸���·" << '\n'
         << "11.\tɾ����·" << '\n'
         << "12.\t��ӹ���" << '\n'
         << "13.\t�޸Ĺ���" << '\n'
         << "14.\tɾ������" << '\n'
         << "15.\t��������" << '\n'
         << "0.\t�˳�" << '\n'
         << "===================" << '\n'
         << "������ָ���ţ�";
}

//���ݹ��������Ҹù���������
static int findBus(string name) {
    for (int i = 0; i < g_BusMap.buses.size(); i++) {
        if (g_BusMap.buses[i].name == name) return i;
    }
    return -1;
}

//������㣬�յ㣬����������route������
static int findRoute(int from, int to, int bus) {
    for (int i = 0; i < g_BusMap.routes.size(); i++) {
        auto &route = g_BusMap.routes[i];
        if (route.from == from && route.to == to && route.bus == bus) {
            return i;
        }
    }
    return -1;
}

//����վ������ֲ���վ�������
int findStation(string name) {
    for (int i = 0; i < g_BusMap.stations.size(); i++) {
        if (g_BusMap.stations[i].name == name) {
//            cout<<i<<"--"<<name;
            return i;
        }
    }
    return -1;
}

//1.�鿴����վ��
static void listStations() {
    for (int i = 0; i < g_BusMap.stations.size(); i++) {
        cout << i << "--" << g_BusMap.stations[i].name << endl;
    }
}

//2.�鿴���й���
static void listBuses() {
    for (int i = 0; i < g_BusMap.buses.size(); i++) {
        const auto &bus = g_BusMap.buses[i];
        cout << bus.name << " \t"
             << g_BusMap.stations[bus.start].name
             << "-->"
             << g_BusMap.stations[bus.end].name << endl;
    }
}

//3.��ѯվ����Ϣ
static void printStationInfo() {
    string temp;
    cout << "����վ�����ƣ�";
    cin >> temp;
    int index = findStation(temp);
    if (index != -1) {
        for (const auto &route : g_BusMap.routes)
            if (route.from == index || route.to == index) {
                cout << g_BusMap.stations[route.from].name << "-->" << g_BusMap.buses[route.bus].name
                     << "-->" << g_BusMap.stations[route.to].name << endl;
            }
    } else {
        cout << "�������!" << endl;
    }
}

//��ӡ������·
static void doPrintBusInfo(int station, int bus) {
    for (auto it = g_BusMap.stations[station].routes.cbegin(); it != g_BusMap.stations[station].routes.cend(); it++) {
        if ((*it)->bus == bus) {
            cout << "-->" << g_BusMap.stations[(*it)->to].name;
            doPrintBusInfo((*it)->to, bus);
        }
    }
}

//4.��ѯ������·
static void printBusInfo() {
    string temp;
    cout << "���빫�����ƣ�";
    cin >> temp;
    int index = findBus(temp);
    if (index != -1) {
        int start = g_BusMap.buses[index].start;
        cout << g_BusMap.stations[start].name;
        doPrintBusInfo(start, index);
        cout << endl;
    } else {
        cout << "�������!" << endl;
    }
}

//5.������վ֮�����з���������·��
//static void takeBus() {}

//6.���վ��
static void addStation() {
    string name;
    cout << "��������վ�������:";
    cin >> name;
    if (findStation(name) == -1) {
        g_BusMap.stations.push_back(Station(name));
    } else {
        cout << "����ռ��!" << endl;
    }
}

//7.�޸�վ��(����)
static void changeStation() {
    string oldName, newName;
    cout << "������޸�վ�������:";
    cin >> oldName;
    int index = findStation(oldName);
    if (index != -1) {
        cout << "����������:";
        cin >> newName;
//        cout<<index<<"--"<<g_BusMap.stations[index].name;
        g_BusMap.stations[index].name = newName;
    } else cout << "����վ�㲻����!";
}

//8.ɾ��վ��
static void deleteStation() {
    string name;
    cout << "�����ɾ��վ�������:";
    cin >> name;
    int index = findStation(name);
    if (index != -1) {
        for (int i = 0; i < g_BusMap.buses.size(); i++) {
            pair<int, int> temp = searchRoute(index, i);
            if (temp.first == -1 && temp.second == -1)// ��bus��û�д˵�
                continue;
            else if (temp.first == -1) {//Ϊ��bus�����
                g_BusMap.buses[i].start = g_BusMap.routes[temp.second].to;
                g_BusMap.routes.erase(g_BusMap.routes.begin() + temp.second);
            } else if (temp.second == -1) {//Ϊ��·�ߵ��յ�
                g_BusMap.buses[i].end = g_BusMap.routes[temp.first].from;
                g_BusMap.stations[g_BusMap.buses[i].end].routes.remove(&g_BusMap.routes[temp.first]);
                g_BusMap.routes.erase(g_BusMap.routes.begin() + temp.first);
            } else {//Ϊ��תվ
                g_BusMap.routes[temp.first].to = g_BusMap.routes[temp.second].to;
                g_BusMap.routes[temp.first].distance += g_BusMap.routes[temp.second].distance;
                g_BusMap.routes.erase(g_BusMap.routes.begin() + temp.second);
            }
            // ��g_BusMap��ɾ����վ��
            g_BusMap.stations.erase(g_BusMap.stations.begin() + index);
            // ����route��station�ı��
            for (int i = index; i < g_BusMap.stations.size(); i++) {
                for (auto &route : g_BusMap.routes) {
                    if (route.from == i + 1) route.from--;
                    if (route.to == i + 1) route.to--;
                }
            }
            // ����bus��station�ı��
            for (int i = index; i < g_BusMap.stations.size(); i++) {
                for (auto &bus : g_BusMap.buses) {
                    if (bus.start == i + 1) bus.start--;
                    if (bus.end == i + 1) bus.end--;
                }
            }
        }
        cout << "ɾ���ɹ�!" << endl;
    } else cout << "����վ�㲻����!";
}

//9.�����·
static void addRoute(int from, int to, int bus, int distance) {
    g_BusMap.routes.push_back(Route(from, to, bus, distance));
    g_BusMap.stations[from].routes.push_back(&(g_BusMap.routes.back()));
}

//10.�޸���·
static void changeRoute(int from, int to, int bus, int distance) {
    int index = findRoute(from, to, bus);
    if (index != -1) {
        g_BusMap.routes[index].distance = distance;
    } else cout << "�����·�߲�����,��������!";
}

//11.ɾ����·
static void deleteRoute(int from, int to, int bus) {
    int index = findRoute(from, to, bus);
    if (index != -1) {
        g_BusMap.stations[from].routes.remove(&(g_BusMap.routes[index]));
        g_BusMap.routes.erase(g_BusMap.routes.begin() + index);
    } else cout << "�����·�߲�����,��������!";
}

//14.ɾ������
static void deleteBus(string name) {
    int index = findBus(name);
    int from = g_BusMap.buses[index].start;
    int end = g_BusMap.buses[index].end;
    while (from != end) {
        for (auto route: g_BusMap.stations[from].routes)
            if (route->bus == index) {
                int tmp = route->to;
                deleteRoute(from, route->to, index);
                from = tmp;
            }
    }
    //����route�е�bus
    for (int i = index; i < g_BusMap.buses.size(); i++) {
        for (auto route: g_BusMap.routes)
            if (route.bus == index + 1) route.bus--;
    }
    g_BusMap.buses.erase(g_BusMap.buses.begin() + index);
}

//12.��ӹ���
static void addBus(string name) {
    int num, distance;
    cout << "����˹����а�����վ����:";
    cin >> num;
    vector<string> nameList;
    vector<int> numList;
    vector<int> distanceList;
    string from, tmp;
    cout << "����ʼ��վ����:";
    cin >> from;
    num--;
    while (findStation(from) == -1) {
        cout << "�����վ�㲻����!����������:";
        cin >> from;
    }
    nameList.push_back(from);
    while (num--) {
        cout << "������� վ��(��:100 A):";
        cin >> distance >> tmp;
        while (findStation(tmp) == -1) {
            cout << "�����վ�㲻����!����������:";
            cin >> distance >> tmp;
        }
        distanceList.push_back(distance);
        nameList.push_back(tmp);
    }
    //�����ص�route
    for (int i = 0; i < nameList.size() - 1; i++) {
        addRoute(findStation(nameList[i]), findStation(nameList[i + 1]), g_BusMap.buses.size(), distanceList[i]);
    }
    //��ӹ���
    g_BusMap.buses.push_back(Bus(name, findStation(nameList[0]), findStation(nameList.back())));
}

//13.�޸Ĺ���
static void changeBus() {
    string name;
    cout << "������޸Ĺ���������(��:1_U)";
    cin >> name;
    int index = findBus(name);
    if (index != -1) {
        deleteBus(name);
        addBus(name);
    } else cout << "�ù�����������,��������!";
}

//�����û�����
static vector<int> enter_check() {
    string from, to, bus;
    vector<int> tmp;
    cout << "�������վ ����վ ��������(��:A B 1_U):";
    cin >> from >> to >> bus;
    while (findStation(from) == -1 || findStation(to) == -1 || findBus(bus) == -1) {
        cout << "�������!��������:";
        cin >> from >> to >> bus;
    }
    tmp.push_back(findStation(from));
    tmp.push_back(findStation(to));
    tmp.push_back(findBus(bus));
    return tmp;
}

//��route��Ӽ���������溯��
static void doAddRoute() {
    vector<int> tmp = enter_check();
    int distance;
    cout << "�������:";
    cin >> distance;
    while (distance <= 0) {
        cout << "�������!��������:";
        cin >> distance;
    }
    addRoute(tmp[0], tmp[1], tmp[2], distance);
}

static void doChangeRoute() {
    vector<int> tmp = enter_check();
    int distance;
    cout << "�����¾���:";
    cin >> distance;
    while (distance <= 0) {
        cout << "�������!��������:";
        cin >> distance;
    }
    changeRoute(tmp[0], tmp[1], tmp[2], distance);
}

static void doDeleteRoute() {
    vector<int> tmp = enter_check();
    deleteRoute(tmp[0], tmp[1], tmp[2]);
}

static void doDeleteBus() {
    string name;
    cout << "�����ɾ������������:";
    cin >> name;
    while (findBus(name) == -1) {
        cout << "�ù�����������!����������:";
        cin >> name;
    }
    deleteBus(name);
}

static void doAddBus() {
    string name;
    cout << "�������ӹ���������:";
    cin >> name;
    while (findBus(name) != -1) {
        cout << "�ù������Ѵ���!����������:";
        cin >> name;
    }
    addBus(name);
}

void run(int index) {
    switch (index) {
        case 1:
            listStations();
            break;
        case 2:
            listBuses();
            break;
        case 3:
            printStationInfo();
            break;
        case 4:
            printBusInfo();
            break;
        case 5:
            takeBus();
            break;
        case 6:
            addStation();
            break;
        case 7:
            changeStation();
            break;
        case 8:
            deleteStation();
            break;
        case 9:
            doAddRoute();
            break;
        case 10:
            doChangeRoute();
            break;
        case 11:
            doDeleteRoute();
            break;
        case 12:
            doAddBus();
            break;
        case 13:
            changeBus();
            break;
        case 14:
            doDeleteBus();
            break;
        case 15:
            writeMapData();//д������
            break;
        default:
            cout << "�������!" << endl;
            break;
    }
}