# Iterator
class Cart:
    def __init__(self, a, b):
        self.a = a
        self.b = b
        self.i = 0
        self.i_max = len(a)
        self.j = 0
        self.j_max = len(b)
        self.stop_flag = False

    def __iter__(self):
        return self
    
    def __next__(self):
        if self.stop_flag:
            raise StopIteration
        
        curr_i = self.i
        curr_j = self.j

        self.j += 1
        if self.j == self.j_max:
            self.j = 0
            self.i += 1
            if self.i == self.i_max:
                self.stop_flag = True
        
        return (self.a[curr_i], self.b[curr_j])

for i in Cart([1,2], ["a", "b", "c"]):
    print(i)


# Generator
def cart(a, b):
    for i in a:
        for j in b:
            yield (i, j)

for i in cart([1,2], ["a", "b", "c"]):
    print(i)