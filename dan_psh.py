from golden_ratio import calc_min
import numpy as np

def grad(f, x, eps):
    return (f(x + eps) - f(x)) / eps

def calc_min(f, x0, eps):
   S0 = -grad(f, x0, 1e-8)

   lambd = np.zeros(2)

   k = 0