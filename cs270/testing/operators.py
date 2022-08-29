x = 5
y = 6

if (x == y):
	print ("x == y")
if (x < y):
	print ("x < y")
if (x <= y):
	print ("x <= y")
if (x != y):
	print ("x != y")
if (x is y):
	print ("x is y")
if (x is not y):
	print ("x is not y")

#Equation Operators
#f(x)=x^3*e^(-x), x >= 0
def myfunc(x):
	if x > 0.0:
		return x**3*math.exp(-x)
	else:
		return 0.0

print myfunc(5)
#if (x in y):
#	print ("x in y")
#if (x not in y):
#	print ("x not in y")

assert x < 10 #assert only allows for True statements
assert x < 3, 'value must be greater than 3' #end here because its False
