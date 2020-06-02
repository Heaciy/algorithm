def binary_search(arr, left, right, key):
    mid = int((left+right)/2)
    if left > right:
        return ("Not Found", right, left)
    else:

        if arr[mid] > key:
            return binary_search(arr, left, mid-1, key)
        elif arr[mid] < key:
            return binary_search(arr, mid+1, right, key)
        else:
            return ("Found", mid)


def tmp(arr, left, right, key):
    # key不在起始值范围之内
    if arr[left] > key:
        return ("Not Found", "~", left)
    elif arr[right] < key:
        return ("Not Found", right, "~")
    # key值在起始值范围之内
    else:
        return binary_search(arr, left, right, key)


if __name__ == '__main__':
    # arr = [1,2,3,5]
    arr = [1, 2]
    print(tmp(arr, 0, len(arr)-1, 3))
