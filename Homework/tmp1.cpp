#include <iostream>
#include <vector>
using namespace std;

void print(int n, vector<int> &re) {
    if (n < 0)
        return;
    if (n == 0) {
        for (auto i : re) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        int start = 1;
        int length = re.size();
        if (length != 0)
            start = re.at(length - 1);
        for (int i = start; i <= n; i++) {
            re.push_back(i);
            print(n - i, re);
            re.pop_back();
        }
    }
}
int main() {
    vector<int> re;
    print(9, re);
    return 0;
}