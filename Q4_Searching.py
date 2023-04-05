def part_a():
    def sentinel(list, n, key):
        last = list[n - 1]
        list[n - 1] = key
        i = 0

        while list[i] != key:
            i += 1

        list[n - 1] = last

        if i < n - 1 or list[n - 1] == key:
            return i
        else:
            return -1

    def linear(list, key):
        for i in range(len(list)):
            if list[i] == key:
                return i
            else:
                return -1

    print("Enter roll numbers in a single line separated by a space: ", end="")

    rnos = list(map(int, input().split()))
    key = int(input("Enter the roll number you want to search: "))
    choice = int(input("""Enter:
    1 for Linear Search
    2 for Sentinel Search: """))

    if choice == 1:
        op = linear(rnos, key)
        if op != -1:
            print("The roll number '{}' was found at position {} and index number '{}'".format(key, op + 1, op))
        else:
            print("Element not found")

    elif choice == 2:
        op = sentinel(rnos,len(rnos),key)
        if op != -1:
            print("The roll number '{}' was found at position {} and index number '{}'".format(key, op + 1, op))
        else:
            print("Element not found")


def part_b():

    def bubbleSort(arr):
        n = len(arr)

        swapped = False
        for i in range(n - 1):
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    swapped = True
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]

            if not swapped:
                return

    def binary(list, lb, ub, key):

        if ub >= lb:
            mid = (lb + ub) // 2

            if list[mid] == key:
                return mid

            elif list[mid] > key:
                return binary(list, lb, mid - 1, key)

            elif list[mid] < key:
                return binary(list, mid + 1, ub, key)

        else:
            return -1

    def fibonacci(arr,x,n):
    
        fibMMm2 = 0
        fibMMm1 = 1
        fibM = fibMMm2 + fibMMm1

        while (fibM < n):
            fibMMm2 = fibMMm1
            fibMMm1 = fibM
            fibM = fibMMm2 + fibMMm1
        offset = -1

        while (fibM > 1):


            i = min(offset + fibMMm2, n - 1)


            if (arr[i] < x):
                fibM = fibMMm1
                fibMMm1 = fibMMm2
                fibMMm2 = fibM - fibMMm1
                offset = i


            elif (arr[i] > x):
                fibM = fibMMm2
                fibMMm1 = fibMMm1 - fibMMm2
                fibMMm2 = fibM - fibMMm1

            else:
                return i

        if (fibMMm1 and arr[n - 1] == x):
            return n - 1


        return -1
    
    print("Enter roll numbers in a single line separated by a space: ", end="")

    rnos = list(map(int, input().split()))
    key = int(input("Enter the roll number you want to search: "))
    choice = int(input("""Enter:
    1 for Binary Search
    2 for Fibonacci Search: """))
    bubbleSort(rnos)

    if choice == 1:
        op = binary(rnos,0,len(rnos),key)
        if op != -1:
            print("The roll number '{}' was found at position {} and index number '{}'".format(key, op + 1, op))
        else:
            print("Element not found")

    elif choice == 2:
        op = fibonacci(rnos,key,len(rnos))
        if op != -1:
            print("The roll number '{}' was found at position {} and index number '{}'".format(key, op + 1, op))
        else:
            print("Element not found")

part_b()
