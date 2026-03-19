#Linear Search
def linear_search(arr, target):
    for num in range(len(arr)):
        if arr[num] == target:
            return True, num+1
    return False, -1

nums = [4, 2, 3, 1, 5]
print(linear_search(nums, 3))

----------------------------------------------------------------------------
def binarySearch(arr, left, right, target):
    while left <= right:
        mid = (left + right) // 2
        print(f"Left: {left}, Right: {right}, Mid: {mid}, MidValue: {arr[mid]}")
        if arr[mid] == target:
            return True, mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return False, -1

num = [4, 2, 3, 1, 5, 23, 56, 78, 12, 89, 45, 67, 34, 90]
num.sort()
print(binarySearch(num, 0, 13, 78))  #True, 7
print(binarySearch(num, 0, 13, 100)) #False, -1
-----------------------------------------------------------------------------------
def selectionSort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(i+1, n):
            if(arr[i] > arr[j]):
                temp = arr[i]
                arr[i] = arr[j]
                arr[j] = temp
         
    return arr

num = [64, 25, 12, 22, 11 ]
sorted_arr = selectionSort(num)
for arr in sorted_arr:
    print(arr, end=" ")  
---------------------------------------------------------------------------------------
def bubbleSort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(n-1-i):
            if(arr[j] > arr[j+1]):
                temp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = temp
         
    return arr

num = [64, 25, 12, 22, 11 ]
sorted_arr = bubbleSort(num)
for arr in sorted_arr:
    print(arr, end=" ")  
-------------------------------------------------------------------------------------------

def insertionSort(arr):
    n = len(arr)
    for i in range(n):
        j = i
        while j > 0 and arr[j-1] > arr[j]:
            temp = arr[j]
            arr[j] = arr[j-1]
            arr[j-1] = temp
            j -= 1
    return arr
   
num = [64, 25, 12, 22, 11 ]
sorted_arr = insertionSort(num)
for arr in sorted_arr:
    print(arr, end=" ")

------------------------------------------------------------------------------------------------
def partition(a, lower, upper):
    pivot = a[lower]
    p = lower + 1
    q = upper

    while q >= p:
        while p <= upper and a[p] < pivot:
            p += 1

        while q >= lower and a[q] > pivot:
            q -= 1

        # Swap a[p] and a[q]
        if q > p:
            a[p], a[q] = a[q], a[p]

    # Swap pivot and a[q]
    a[lower], a[q] = a[q], a[lower]

    return q

def quicksort(a, lower, upper):
    if lower <= upper:
        i = partition(a, lower, upper)
        quicksort(a, lower, i - 1)
        quicksort(a, i + 1, upper)


# --- Main ---
arr = [11, 13, 2, 45, 10, 56, 20]
quicksort(arr, 0, len(arr) - 1)

for x in arr:
    print(x)
-----------------------------------------------------------------------------------

