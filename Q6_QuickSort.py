def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1

    for j in range(low, high):

        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]

    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def quicksort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quicksort(arr, low, pi - 1)
        quicksort(arr, pi + 1, high)


print("Enter floating point marks separated by a space: ")
marks = list(map(float, input().split()))

print("\nMarks unsorted:")
print(*marks, sep=" ")

quicksort(marks, 0, len(marks) - 1)

print("\n\nMarks Sorted: ")
print(*marks, sep=" ")
