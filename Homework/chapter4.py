# 数列最大子段之和
origin = [-1, -2, 11, -5, -7, 13, -1, -2, 12, -1, -4, 11]
origin1 = [-1, -2, 11, -5, -7, 13, -1, -12, 13, -1, -14, 11]
origin2 = [-1, -2, -3, 4]


def findMax(origin):
    index = [i for i in range(len(origin)) if origin[i] > 0]
    if len(index) == 0:  # 如果全部为负数，返回最小值......
        print(repr([min(origin)]))
        return

    # 不全为负数
    max_ = [(0, 0, -1)]  # 初始化

    def sum_(list, start, end):
        if start == end:
            return list[start]
        else:
            return sum(list[start:end])

    for s in range(len(index)):  # s --> start
        for e in range(s, len(index)):  # e --> end
            tmp = sum_(origin, index[s], index[e])
            if tmp > 0:
                if e != s:
                    tmp += origin[index[e]]
                if tmp == max_[0][2]:
                    max_.append((index[s], index[e], tmp))
                elif tmp > max_[0][2]:
                    max_ = [(index[s], index[e], tmp)]
            else:
                break
    print(repr(max_))


if __name__ == "__main__":
    findMax(origin)
