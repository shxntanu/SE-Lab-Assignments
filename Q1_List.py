cric = []
badm = []
foot = []
studentlist = []
corb = []
candb = []
fonly = []
cfnotb = []

n = int(input("Total Number of students: "))

for i in range(n):

    name = input("Enter Name of student: ")
    studentlist.append(name)

    c = input("Input y if you play cricket: ")
    b = input("Input y if you play badminton: ")
    f = input("Input y if you play football: ")

    if c == 'y':
        cric.append(name)
    if b == 'y':
        badm.append(name)
    if f == 'y':
        foot.append(name)

for i in studentlist:

    if (i in cric) and (i in badm):
        candb.append(i)

    if (i in cric) and (i not in badm):
        corb.append(i)
    if (i not in cric) and (i in badm):
        corb.append(i)

    if (i not in cric) and (i not in badm):
        fonly.append(i)

    if (i in cric and i in foot) and (i not in badm):
        cfnotb.append(i)

print("Students playing both cricket and badminton: ", end="")
for i in candb:
    print(i , end=" ")
print()

print("Students playing either cricket or badminton but not both: ")
for i in corb:
    print(i,end=" ")
print()

print("Number of students playing Neither Cricket not Badminton: ", len(fonly))

print("Number of students playing Cricket and Football but not Badminton: ",len(cfnotb))
