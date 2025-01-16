def Ceng111Reduce(func,L,initial):
	if len(L)==0:
		return L[-1]
	else:
		return Ceng111Reduce(func,L[1:],L[0])
print(Ceng111Reduce(lambda a,b:a+b, [1,2,3,4,6,8,11],0))