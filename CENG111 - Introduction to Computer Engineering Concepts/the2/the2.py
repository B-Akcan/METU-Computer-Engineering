a=str(input())
if "?" not in a:
	b=[int(a[0]), int(a[1]), int(a[2]), int(a[3]), int(a[5])]
	c=(2*(b[0])+3*(b[1])+5*(b[2])+7*(b[3]))%11
	if c==b[4]:
		print("VALID")
	else:
		print("INVALID")
elif a[5]=="?":
	d=[int(a[0]), int(a[1]), int(a[2]), int(a[3])]
	e=(2*(d[0])+3*(d[1])+5*(d[2])+7*(d[3]))%11
	if e==10:
		print(a[0:5]+"X")
	else:	
		print(a[0:5]+str(e))
elif a[0]=="?":
	f=[int(a[1]), int(a[2]), int(a[3]), int(a[5])]
	g=0
	if (2*g+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g)+a[1:])
	elif (2*(g+1)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+1)+a[1:])
	elif (2*(g+2)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+2)+a[1:])
	elif (2*(g+3)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+3)+a[1:])
	elif (2*(g+4)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+4)+a[1:])
	elif (2*(g+5)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+5)+a[1:])
	elif (2*(g+6)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+6)+a[1:])
	elif (2*(g+7)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+7)+a[1:])
	elif (2*(g+8)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+8)+a[1:])
	elif (2*(g+9)+3*(f[0])+5*(f[1])+7*(f[2])-(f[3]))%11==0:
		print(str(g+9)+a[1:])
elif a[1]=="?":
	h=[int(a[0]), int(a[2]), int(a[3]), int(a[5])]
	i=0
	if (2*(h[0])+3*i+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i)+a[2:])
	elif (2*(h[0])+3*(i+1)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+1)+a[2:])
	elif (2*(h[0])+3*(i+2)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+2)+a[2:])
	elif (2*(h[0])+3*(i+3)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+3)+a[2:])
	elif (2*(h[0])+3*(i+4)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+4)+a[2:])
	elif (2*(h[0])+3*(i+5)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+5)+a[2:])
	elif (2*(h[0])+3*(i+6)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+6)+a[2:])
	elif (2*(h[0])+3*(i+7)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+7)+a[2:])
	elif (2*(h[0])+3*(i+8)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+8)+a[2:])
	elif (2*(h[0])+3*(i+9)+5*(h[1])+7*(h[2])-(h[3]))%11==0:
		print(a[0]+str(i+9)+a[2:])
elif a[2]=="?":
	j=[int(a[0]), int(a[1]), int(a[3]), int(a[5])]
	k=0
	if (2*(j[0])+3*(j[1])+5*k+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+1)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+1)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+2)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+2)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+3)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+3)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+4)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+4)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+5)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+5)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+6)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+6)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+7)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+7)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+8)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+8)+a[3:])
	elif (2*(j[0])+3*(j[1])+5*(k+9)+7*(j[2])-(j[3]))%11==0:
		print(a[0:2]+str(k+9)+a[3:])
elif a[3]=="?":
	l=[int(a[0]), int(a[1]), int(a[2]), int(a[5])]
	m=0
	if (2*(l[0])+3*(l[1])+5*(l[2])+7*m-(l[3]))%11==0:
		print(a[0:3]+str(m)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+1)-(l[3]))%11==0:
		print(a[0:3]+str(m+1)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+2)-(l[3]))%11==0:
		print(a[0:3]+str(m+2)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+3)-(l[3]))%11==0:
		print(a[0:3]+str(m+3)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+4)-(l[3]))%11==0:
		print(a[0:3]+str(m+4)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+5)-(l[3]))%11==0:
		print(a[0:3]+str(m+5)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+6)-(l[3]))%11==0:
		print(a[0:3]+str(m+6)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+7)-(l[3]))%11==0:
		print(a[0:3]+str(m+7)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+8)-(l[3]))%11==0:
		print(a[0:3]+str(m+8)+a[4:])
	elif (2*(l[0])+3*(l[1])+5*(l[2])+7*(m+9)-(l[3]))%11==0:
		print(a[0:3]+str(m+9)+a[4:])



