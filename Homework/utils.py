from time import perf_counter as pc

# 获取函数大致运行时间的装饰器
def getTime(func):
    def tmp(*arg):
        t0 = pc()
        func(*arg)
        print("Func {} cost {} s".format(func.__name__,pc()-t0))
    return tmp

def is_eq(list1,list2):
    if list1 == list2:
        return True
    return sorted(list1)==sorted(list2)