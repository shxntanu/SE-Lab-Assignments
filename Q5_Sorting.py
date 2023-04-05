def InsertionSort(list):

    for i in range(1,len(list)):

        key = list[i]
        j = i-1

        while j>=0 and key<list[j]:
            list[j+1]=list[j]
            j-=1
        list[j+1]=key

    return list

def ShellSort(list):

    n = len(list)
    interval = n//2
    while interval>0:

        for i in range(interval,n):
            temp = list[i]
            j=i

            while j>=interval and list[j-interval]>list[j]:
                list[j] = list[j-interval]
                j-=interval
            list[j] = temp

        interval//=2

    return list

scores = []
print("Enter float scores separated by a space: ",end="")
my_list = list(map(float, input().split()))
sort_by_insertion = my_list
print("Insertion-Sorted Scores: ",InsertionSort(sort_by_insertion))

print("\nShell Sort Scores: ",ShellSort(my_list))

print("Top 5 Scores: ")
j=1
for i in range(-1,-5,-1):
    print(j,": ",my_list[i])
    j+=1



