from my_stack import *
def finalOps(L):
	st=create_stack()
	i=0
	while i<len(L):
		if L[i]!="undo":
			push(L[i],st)
			i+=1
		else:
			pop(st)
			i+=1
	return st