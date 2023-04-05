def matrix_display(list):
    print("\n")
    for i in range(len(list)):
        for j in range(len(list[0])):
            print("{:<5}".format(list[i][j]), end = " ")
        print()

r,c = list(map(int, input("Enter the number of rows and columns respectively, separated by a space: ").split()))
m1 = [[]*c]*r
m2 = [[]*c]*r

print("Enter the value of Matrix 1: ")
for i in range(r):
    m1[i] = list(map(int, input().split()))
    
print("Matrix 1: ")
matrix_display(m1)

print("Enter the value of Matrix 2: ")
for i in range(r):
    m2[i] = list(map(int, input().split()))
    
print("Matrix 2: ")
matrix_display(m2)

sum_matrix = [[m1[i][j] + m2[i][j]  for j in range(len(m1[0]))] for i in range(len(m1))]
print("Sum of Matrix 1 and Matrix 2: ")
matrix_display(sum_matrix)

sub_matrix = [[m1[i][j] - m2[i][j]  for j in range(len(m1[0]))] for i in range(len(m1))]
print("Subtraction of Matrix 1 and Matrix 2: ")
matrix_display(sub_matrix)

prod_matrix = [[0]*r]*c
for i in range(len(m1)):
    for j in range(len(m2[0])): #columns of m2
        for k in range(len(m2)): #rows of m2 in the same column
            prod_matrix[i][j] += m1[i][k]*m2[k][j]

print("Product of m1 and m2: ")
matrix_display(prod_matrix)

trans_matrix = [[0 for p in range(r)] for _ in range(c)]

for i in range(len(m1)):
   for j in range(len(m1[0])):
       trans_matrix[j][i] = m1[i][j]
print("Transpose of Matrix 1 is: ")
matrix_display(trans_matrix)
