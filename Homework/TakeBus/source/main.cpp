#include <iostream>
#include "menu.h"

using namespace std;

int main() {
    loadMapData();//��������
    int choice = 0;
    while (true){
        printMenu();
        cin>>choice;
        if(choice!=0){
            run(choice);
            cout<<"���س�������:";
            cin.get();
            cin.get();
        } else{
            cout<<"�˳�"<<endl;
            break;
        }
    }
    return 0;
}
