#include <iostream>
using namespace std;

int *result; // 结果
int mid;     // 中间值的index

int *binary_search(int *arr, int left, int right, int key) {
    mid = (left + right) / 2;
    if (left > right) {
        result = new int[2]{right, left};
        return result;
    }
    if (arr[mid] > key)
        return binary_search(arr, left, mid - 1, key);
    else if (arr[mid] < key)
        return binary_search(arr, mid + 1, right, key);
    else {
        result = new int[2]{mid, mid};
        return result;
    }
}

int main() {
    int *arr = new int[4]{1, 2, 4, 5};
    int *tmp = binary_search(arr, 0, 3, 3);
    cout << "(" << tmp[0] << "," << tmp[1] << ")" << endl;
}