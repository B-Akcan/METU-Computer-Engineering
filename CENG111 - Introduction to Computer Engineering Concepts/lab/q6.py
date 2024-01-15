def findPrimeNumbers(n):
	L=[]
	i=range(2,n+1) 
	a=0
	while n>1:
		while a<len(i):
			if n%i[a]!=0:
				a+=1
			else:
				break
		L.append(n)
		n-=1
	return L


