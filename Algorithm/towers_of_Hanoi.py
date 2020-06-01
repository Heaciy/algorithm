# class TowersOfHanoi:
#     def __init__(self, N: int):
#         self.A = 'A'
#         self.B = 'B'
#         self.C = 'C'
#         self.counter = 0

#     def move(self, disks: int, m: str, n: str):
#         self.counter += 1
#         print("第{}次移动：把{}号圆盘从{}移动到{}".format(self.counter, disks, m, n))

#     def hanoi(self, n: int, a: str,  b: str, c: str):
#         if n == 1:
#             self.move(1, self.A, self.C)  # 圆盘只有一个时，只需将其从A塔移到C塔
#         else:
#             self.hanoi(self,n-1,self.A,self.C,self.B)

counter = 0


def move(disks: int, m: str, n: str):
    global counter
    counter += 1
    print("第{}次移动：把{}号圆盘从{}移动到{}".format(counter, disks, m, n))


def hanoi(n: int, a: str,  b: str, c: str):
    if n == 1:
        move(1, a, c)  # 圆盘只有一个时，只需将其从A塔移到C塔
    else:
        hanoi(n-1, a, c, b)  # 递归，把A塔上编号1~n-1的圆盘移到B上，以C为辅助塔
        move(n, a, c)  # 把A塔上编号为n的圆盘移到C上
        hanoi(n-1, b, a, c)  # 递归，把B塔上编号1~n-1的圆盘移到C上，以A为辅助塔


if __name__ == "__main__":
    A = "A"
    B = "B"
    C = "C"
    n = int(input("输入圆盘数n: "))
    hanoi(n, A, B, C)
