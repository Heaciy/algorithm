#include <iostream>
using namespace std;

int QUEEN[20], N;         // NΪ�ʺ���
int COLUMN[20];           // ��¼�б�ռ�õ����
int MAIN_DIAGONAL[40];    // ��¼���Խ��߱�ռ�õ����
int COUNTER_DIAGONAL[20]; // ��¼���Խ��߱�ռ�õ����

void dfs(int n);   // n���ʺ������������
bool check(int n); // ��n���ʺ����1��n-1���ʺ���û�г�ͻ
// �����з���false,���з���true
void output(int n); // ���n���ʺ��λ��

int main() {
    int i;
    cout << "����Nֵ:";
    cin >> N;
    // ��ʼ��
    for (i = 1; i <= N; i++)
        COLUMN[i] = 0;
    for (i = 1; i <= 2 * N - 1; i++)
        MAIN_DIAGONAL[i] = 0;
    for (i = 2; i < 2 * N; i++)
        COUNTER_DIAGONAL[i] = 0;
    dfs(N);
    return 0;
}

void dfs(int n) {
    int i, j;
    QUEEN[i] = 0;
    i = 1; // i���к�
    while (i > 0) {
        QUEEN[i]++;
        while (QUEEN[i] <= N && !check(i)) // ��ǰ�в�����
            QUEEN[i]++;
        if (QUEEN[i] <= N) {
            if (i == N)
                output(N);
            else { // ��¼�С��Խ�����Դռ��
                j = QUEEN[i];
                COLUMN[j] = 1;
                MAIN_DIAGONAL[i - j + N] = 1;
                COUNTER_DIAGONAL[i + j] = 1;
                i++;
                QUEEN[i] = 0;
            }
        } else { // �ص���һ�У���һ�еĻʺ�ǰλ�ò�����
            i--;
            if (i <= 0)
                break;
            j = QUEEN[i]; // �ͷ��С��Խ�����Դ
            COLUMN[j] = 0;
            MAIN_DIAGONAL[i - j + N] = 0;
            COUNTER_DIAGONAL[i + j] = 0;
        }
    }
}

bool check(int i) {
    int j; // j�ǵ�i�еĻʺ������к�
    j = QUEEN[i];
    if (COLUMN[j] == 1 || MAIN_DIAGONAL[i - j + N] == 1 ||
        COUNTER_DIAGONAL[i + j] == 1)
        return false; //��ǰ�в�����
    else
        return true;
}

void output(int n) {
    int i;
    for (i = 1; i <= n; i++)
        cout << QUEEN[i] << " ";
    cout << endl;
}