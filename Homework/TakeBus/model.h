//
// Created by �μκ� on 2020/2/25.
//

#ifndef TAKEBUS_MODEL_H
#define TAKEBUS_MODEL_H

#include <string>

using namespace std;

typedef struct Bus {
    string name; // ����
    int start; // ���
    int end; // �յ�
} Bus;

typedef struct Route {
    int station; // ָ��վ���������
    int bus; // ����������
    int distance; // ��վ֮��ľ���
    struct Route* next; // ��ʼվ����ͬ�ģ���һ������·��
} Route;

typedef struct Station {
    string station; // վ����
    struct Route *routes; // �Ӹõ��������������·�ߵ�����
} Station;

typedef struct BusMap {
    Bus *buses; // ������·����
    Station *stations; // վ������
    int station_num; // վ����
    int bus_num; // ������·��
} BusMap;

#endif // TAKEBUS_MODEL_H
