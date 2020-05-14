# 最长公共子序列
def lcs(str1, str2, code=0):  # 参数列表为(第一个字符串,第二个字符串,标识符)
    str0 = []  # 用来存储最长子序列
    len1 = len(str1)
    len2 = len(str2)
    tmp = [[0]*(len1+1) for i in range(len2+1)]  # 生成一个元素全为零的矩阵
    for i in range(1, len2+1):
        for j in range(1, len1+1):
            if str1[j-1] == str2[i-1]:  # 若两字符相等，则矩阵对应位置的值为其左上角值加一
                tmp[i][j] = tmp[i-1][j-1]+1
            else:
                # 两字符不等，则为其左边或是上边相邻值中的最大值
                tmp[i][j] = max(tmp[i][j-1], tmp[i-1][j])

    def dp(x, y):
        if(tmp[x][y] == 0):
            return
        else:
            if str1[y-1] == str2[x-1]:  # 两字符相等则加入到str0中
                str0.append(str1[y-1])
                return dp(x-1, y-1)  # 继续探索其左上角的值
            else:  # 两字符不相等时
                if tmp[x][y-1] > tmp[x-1][y]:  # 左边值大于上边值
                    return dp(x, y-1)
                elif tmp[x][y-1] < tmp[x-1][y]:  # 左边值小于上边值
                    return dp(x-1, y)
                else:  # 左边值和上边值相等
                    if code == 0:  # 标识符为0,优先探索左边值(默认优先探索左边值)
                        return dp(x, y-1)
                    else:  # 标识符不为0,优先探索上边值
                        return dp(x-1, y)

    dp(len2, len1)  # 从矩阵右下角的值开始
    return (tmp[-1][-1], str0[::-1])  # 返回元组(长度,最长子序列)


# 最长不下降子序列
def lcs_(list_):
    tmp = [[int(i), 1] for i in list_]
    stack = [tmp[0]]

    def getNum(tmp, index):
        tmp_ = []
        for i in range(index-1, -1, -1):
            if tmp[i][0] < tmp[index][0]:
                tmp_.append(tmp[i][1])
        if len(tmp_) == 0:
            return tmp[index][1]
        else:
            return max(tmp_)+1

    for i in range(1, len(list_)):
        tmp[i][1] = getNum(tmp, i)
        if tmp[i][1] > stack[-1][1]:
            stack.append(tmp[i])
        elif tmp[i][1] == stack[-1][1]:
            stack[-1] = tmp[i]

    # return tmp, len(stack), stack
    return len(stack), [i[0] for i in stack]


# 最长公共子串
def lcs__(str1, str2):
    len1 = len(str1)
    len2 = len(str2)
    tmp = [[0]*(len1+1) for i in range(len2+1)]
    # max_ = 0
    max_ = [[0, 0, 0]]
    result = []
    for i in range(1, len2+1):
        for j in range(1, len1+1):
            if str1[j-1] == str2[i-1]:
                tmp[i][j] = tmp[i-1][j-1]+1
                # result = max(max_,tmp[i][j])
                if tmp[i][j] > max_[0][0]:
                    max_ = [[tmp[i][j], i, j]]
                elif tmp[i][j] == max_[0][0]:
                    max_.append([tmp[i][j], i, j])

    # 获取最长子串
    def getString(tmp_, i, j):
        if tmp[i][j] == 0:
            return tmp_
        else:
            tmp_.append(str2[i-1])
            return getString(tmp_, i-1, j-1)
            
    for i in max_:
        tmp_ = []
        tmp_ = getString(tmp_, i[1], i[2])
        result.append(tmp_[::-1])

    return result


if __name__ == "__main__":
    # 测试lcs (最长子序列)
    print(lcs("357486782", "13456778"))
    # 输出(5, ['3', '5', '7', '7', '8'])
    print(lcs("357486782", "13456778", code=1))
    # 输出(5, ['3', '4', '6', '7', '8'])
    print(lcs("ABCBDAB", "BDCABA"))
    # 输出(4, ['B', 'C', 'B', 'A'])
    print(lcs("ABCBDAB", "BDCABA", code=1))
    # 输出(4, ['B', 'D', 'A', 'B'])
    # 测试lcs_ (最长不下降子序列)
    print(lcs_("357486782"))
    print(lcs_([3, 18, 7, 14, 10, 12, 23, 41, 16, 24]))
    print(lcs_([3, 18, 7, 14, 10, 12, 23, 17, 16, 24]))
    # 测试lcs__ (最长公共子串)
    print(lcs__("helloworld", "loop"))
    print(lcs__("abbbc", "abbc"))
    print(lcs__([1, 2], [1, 2]))
