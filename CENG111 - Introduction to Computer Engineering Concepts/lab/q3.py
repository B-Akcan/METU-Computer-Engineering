a=input()
b=list(a)
max(b[0])
max(b[1])
max(b[2])
if max(b[0])>max(b[1]) and max(b[0])>max(b[2]):
	print(max(b[0]))
elif max(b[1])>max(b[0]) and max(b[1])>max(b[2]):
	print(max(b[1]))
elif max(b[2])>max(b[0]) and max(b[2])>max(b[1]):
	print(max(b[2]))
