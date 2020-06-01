def binary_search(arr, left, right, key):
    mid = int((left+right)/2)
    if left == right:
        if arr[mid] == key:
            return (mid)
        else:
            return (left-1, right)
    else:
        if arr[mid] == key:
            return (mid)
        elif arr[mid] > key:
            right = mid-1
            return binary_search(arr, left, right, key)
        else:
            left = mid+1
            return binary_search(arr, left, right, key)


def tmp(arr, left, right, key):
    # key不在起始值范围之内
    if arr[left] > key:
        return ("~", left)
    elif arr[right] < key:
        return (right, "~")
    # key值在起始值范围之内
    else:
        return binary_search(arr, left, right, key)


if __name__ == '__main__':
    # arr = [1,2,3,5]
    arr = [1, 2]
    print(tmp(arr, 0, len(arr)-1, 3))
