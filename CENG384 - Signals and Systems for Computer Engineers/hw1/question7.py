import sympy as sp

# Part a
n = sp.Symbol("n")
alpha = sp.Symbol("alpha")
beta = sp.Symbol("beta")

x1 = sp.Function("x1", real=False)(n)
x2 = sp.Function("x2", real=False)(n)
x3 = alpha * x1 + beta * x2

y1 = x1 * n
y2 = x2 * n
y3_1 = x3 * n
y3_2 = alpha * y1 + beta * y2


if y3_1.equals(y3_2):
    print("The given system is a Linear system")
else:
    print("The given system is a Non-Linear system")


# Part b
n = sp.Symbol("n")
alpha = sp.Symbol("alpha")
beta = sp.Symbol("beta")

x1 = sp.Function("x1", real=False)(n)
x2 = sp.Function("x2", real=False)(n)
x3 = alpha * x1 + beta * x2

y1 = x1 ** 2
y2 = x2 ** 2
y3_1 = x3 ** 2
y3_2 = alpha * y1 + beta * y2

if y3_1.equals(y3_2):
    print("The given system is a Linear system")
else:
    print("The given system is a Non-Linear system")
