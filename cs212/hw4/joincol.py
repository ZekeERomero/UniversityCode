#!/usr/bin/env python3
import sys

d = {}
setKeys = []

spacing = 7

if __name__ == "__main__":
	
	for i in range(len(sys.argv)):
		if(i > 0 and i % 2 != 0):
			try:
				arg = sys.argv[i]
				col = sys.argv[i+1]

				file = open(arg, "r")

				for j, line in enumerate(file):
					arr = line.split()

					if arr[int(col)-1] not in setKeys:
						setKeys.append(arr[int(col)-1])

			except IOError:
				print(f"File '{arg}' is not accessible")

	for key in setKeys:
		print(key, end=" ")#*(spacing+3-len(key)))

		for i in range(len(sys.argv)):
			if(i > 0 and i % 2 != 0):
				try:
					arg = sys.argv[i]
					col = sys.argv[i+1]

					file = open(arg, "r")

					num = 0
					address = '-'

					for j, line in enumerate(file):
						arr = line.split()
						count = 0
						for i in range(len(arr)):
							newline = arr[:count] + arr[count+1:]
							if (i == int(col)-1):
								if key == arr[i]:
									if newline:
										address = newline
							count += 1
					
					if (address == '-'):
						address = ('-')*(len(arr)-1)

					d.setdefault(arg, {})[key] = address
					for i in range(len(arr) - 1):
						line = d[arg][key][i]
						print(line, end=" ")#*(spacing-len(line)))
				except IOError:
					print(f"File '{arg}' is not accessible")
		print("")


