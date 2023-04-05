sen = input("Enter the sentence: ")
sen_list = sen.split()

max = 0
for i in sen_list:
    if len(i) > max:
        max = len(i)
        global word
        word = i
print("The longest word in '{}' is '{}' of length '{}' characters".format(sen,word,max))

occurrence = sen.count(input("Enter the character whose frequency of occurrence you want to check: "))
print("Number of occurrences: ", occurrence)
is_palindrome = (sen == sen[::-1])
print("Is the input string a palindrome: ", is_palindrome)

try:
    index = sen.index(input("Enter the substring whose index you want to check: "))
    print("Starting index of substring: ", index)
except:
    print("Value Error: No such substring exists, Enter a valid input!")

set_list = set(sen_list)
for i in set_list:
    print("Number of times '{}' has occurred: ".format(i), sen_list.count(i))
