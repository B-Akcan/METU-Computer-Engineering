from math import exp
def relu(X):
    l=len(X)
    i=0
    X2=[0]*l
    while i<l:
        if X[i]<=0:
            X2[i]=0
            i+=1
        else:
            X2[i]=X[i]
            i+=1
    return X2

def sigmoid(X):
    l=len(X)
    i=0
    X2=[0]*l
    while i<l:
        if X[i]<=-700:
            X2[i]=0
            i+=1
        elif -700<X[i]<700:
            X2[i]=1/(1+exp(-X[i]))
            i+=1
        elif X[i]>=700:
            X2[i]=1
            i+=1
    return X2

def linear(Layer,X):
    weights=Layer[1]
    X2=[0]*len(weights)
    i=0
    j=0
    while i<len(weights):
        while j<len(weights[i]):
            X2[i]+=weights[i][j]*X[j]
            j+=1
        i+=1
        j=0
    return X2

def forward_pass(Network,X):
    i=0
    Xi=[0]*(len(Network)+1)
    Xi[0]=X
    while i<len(Network):
        if type(Network[i])==list:
                Xi[i+1]=linear(Network[i],Xi[i])
                i+=1
        else:
            if str(Network[i]).startswith("relu"):
                Xi[i+1]=relu(Xi[i])
                i+=1
            elif str(Network[i]).startswith("sigmoid"):
                Xi[i+1]=sigmoid(Xi[i])
                i+=1
    return(Xi[-1])


