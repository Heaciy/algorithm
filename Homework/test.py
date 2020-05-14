from utils import getTime, is_eq


@getTime
def test(num):
    print([i for i in range(num)])


@getTime
def test1(list1, list2):
    print(is_eq(list1, list2))


if __name__ == "__main__":
    test(20)
    test1([1, 2], [1, 2])
