import numpy as np
import matplotlib.pyplot as plt

a_negative1 = 0.5
a_1 = 0.5
a_negative3 = 1j
a_3 = -1j

X = np.arange(-5,6)
Y = np.array([0, 0, a_negative3, 0, a_negative1, 0, a_1, 0, a_3, 0, 0])
Y_magnitude = np.abs(Y)
Y_phase = np.angle(Y, deg=True)

figs, axs = plt.subplots(1, 2, figsize=(20,10))
axs[0].scatter(X, Y_magnitude)
axs[0].set_xticks(np.arange(-5,6))
axs[0].set_yticks(np.arange(0.0, 1.1, 0.1))
axs[0].set_xlabel("k")
axs[0].set_ylabel("Magnitude of a_k")
axs[0].set_title("Magnitude plot")
axs[1].scatter(X, Y_phase)
axs[1].set_xticks(np.arange(-5,6))
axs[1].set_yticks(np.arange(-180, 181, 30))
axs[1].set_xlabel("k")
axs[1].set_ylabel("Phase of a_k (in degrees)")
axs[1].set_title("Phase plot")
plt.show() 

print("The fundamental period is: 6")
print("The simplified Fourier series representation is:")
print(f"\t a_(-1) = {a_negative1},")
print(f"\t a_(1) = {a_1},")
print(f"\t a_(-3) = {a_negative3},")
print(f"\t a_(3) = {a_3},")
print("\t and a_k = 0 for all other k.")