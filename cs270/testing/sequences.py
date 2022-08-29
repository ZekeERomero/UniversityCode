john = ['John Smith',19]
mary = ['Mary Smith',20]
namelist = [john,mary]
print namelist[1][0]
print john[1]

greet = 'Hello'
print greet[-1]

print 'Hello'[3]

tag = 'The Answer is: 45'
print tag[15:17]

concat = john + [tag[15:17]]

concatNum = [1,2,3] + [4,5,6]

print concat[2]

print 'go'*3

listNum = [11]*7

print listNum

#Membership

example = 'hello'

print 'l' in example
print 'x' in example
print 'ell' in example

#Length

values = [7,32,435]

# ??? concatString = max(values) + 'hi'

print len(values)
print 'Max:',max(values)
print 'Min:',min(values)
print 'Max:',max(1,2,3)
print 'Min:',min([1,2,3])

#List functions

print list('Python')

print ''.join(list('Python'))

#Deleting

students = ['Mary','John']
print students
del students[0]
print students
students.append('Zach')
print students
print students.count('John')
print students.count('Jerry')

a = [1,2,3]
b = [4,5,6]

a.extend(b)
#a.join(b) does not work

print a

#Index

indexNum = ['hello','hi','howdy']
print indexNum

# ?? for i in indexNum:
#	print indexNum[i]

print indexNum.index('hi')
#print indexNum.index('hell') does not find and crashes

#Insert

numbers = [1,2,3,4,5,6]

print numbers

numbers.insert(3,'four') #replaces '4'

print numbers

#Stacks

stack = [1,2,3,4,5]
print stack

stack.pop()

print stack

stack.pop(0)

stack



