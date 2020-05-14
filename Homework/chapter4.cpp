#include <iostream>
using namespace std;

int findMax(int *a, int len) { // a为数组,len为数组长度
    int maxSum, maxTmp;  // maxSum为最大子段和,maxTmp是实时的子段和
    maxTmp = maxSum = 0; // 初始化
    for (int i = 0; i < len; i++) {
        if (maxTmp <= 0)
            maxTmp = a[i]; //如果此时该元素前面的子段和已经小于等于0，则舍弃并从当前元素重新开始
        else
            maxTmp += a[i];
        if (maxTmp > maxSum) //如果maxTmp大于已知最大和，则将maxTmp赋值给maxSum
            maxSum = maxTmp;
    }
    return maxSum;
}

int main() {
    // int len, tmp, a[20];
    // cout << "Input the length of list:";
    // cin >> len;
    // for (int i = 0; i < len; i++) {
    //     cin >> tmp;
    //     a[i] = tmp;
    // }
    // cout<<findMax(a,len)<<endl;
    int tmp[] = {-1, -2, 11, -5, -7, 13, -1, -2, 12, -1, -4, 11};
    cout << findMax(tmp, 12);
}