#for number in range(1,11):
#	print number

import math

print "Enter Number:",
x = input()

def factorial(x,n):
	if (n > 1):
		return factorial(x*(n-1),n-1)
	else:
		return x

def myfunc(x):
	return (x**3*math.exp(--x) if x >= 0 else 0.0)

print factorial(x,x)

print myfunc(x)
