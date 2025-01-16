# Toy example for THE3

# You should process the layers in the order they are given in the list. 
# The number in the layers name represents its name, not the processing order.
# 


# Sample input is [2,5,1,1] and has a size of 4 (instead of 784). So that it will be easier for you to make the computations by hand.
# Therefore, utils.display_image() will not work for this example.

# The network has 4 layers
# ['linear_1: 4->3', 'relu_1', 'linear_2: 3->2', 'sigmoid_1']
# You will process this network in this order as well.

# Output of 'linear_1' will have a size 3
# Output of 'relu_1' will have a size 3
# Output of 'linear_2' will have a size 2
# Output of 'sigmoid_1' will have a size 2

# Weights of the first linear layer
# w1 = [[0.70, -0.63, 0.69, -0.02 ], 
#     [0.74, 0.33, -0.09, 0.37],
#     [0.03, -0.12, -0.30, -0.44]]

# Weights of the second linear layer
# w2 = [[0.09, 0.10, 0.98],
#      [0.24, -0.03, -0.24]]
#


import the3

x_sample = [2,5,1,1]
n = [['linear_1',[[0.70, -0.63, 0.69, -0.02], [0.74, 0.33, -0.09, 0.37],[0.03, -0.12, -0.30, -0.44]]],'relu_1',['linear_2',[[0.09, 0.10, 0.98],[0.24, -0.03, -0.24]]],'sigmoid_1']
net_output = the3.forward_pass(n,x_sample)
print(net_output)

# [0.584433414421853, 0.474447280832066]