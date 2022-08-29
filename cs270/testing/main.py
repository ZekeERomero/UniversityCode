def square(x):
	'Calculates the square of the number x'
	return x*x

print "Square of 2: ", square(2)

def recur(x):	
	if x < 10:
		return recur(x+1)
	else:
		return x

print recur(1)

