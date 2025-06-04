import numpy as np
from scipy.optimize import root_scalar
import math

def f1(x):
    if x <= -1.0 or x == -3.0:
        return np.nan
    
    return math.log(math.e, x + 1.0) - 1.0 / (x + 3.0)


def f2(x):
    if x == 0:
        return np.nan

    return math.pow(x, 3) + 30 * math.cos(x) - 1/x

def f3(x):
    if x == -2 or x == -4:
        return np.nan
    
    return math.sin(3 * math.pi * x) / (x + 2) + 1 / (x + 4)

def find_roots(f, a, b, steps=1000, tol=1e-7, max_val=1e6, fval_tol=1e-5):
    xs = np.linspace(a, b, steps + 1)
    roots = []

    for i in range(steps):
        x0, x1 = xs[i], xs[i+1]
        try:
            f0, f1 = f(x0), f(x1)
            if np.isnan(f0) or np.isnan(f1):
                continue
            
            if f0 * f1 <= 0 and abs(f0) < max_val and abs(f1) < max_val:
                res = root_scalar(f, bracket=[x0, x1], method='brentq', xtol=tol)
                if res.converged:
                    root = res.root
                    if abs(f(root)) < fval_tol:
                        if not any(np.isclose(root, r, atol=tol) for r in roots):
                            roots.append(root)
        except Exception:
            pass

    return sorted(roots)

if __name__ == "__main__":
    roots = find_roots(f1, -0.99, 4)
    print("Znalezione pierwiastki w przedziale [-1,4]:")
    print(len(roots))
    for r in roots:
        print(f"{r:.12f}, {f1(r)}")

    roots_left = find_roots(f2, -3, -0.01)
    roots_right = find_roots(f2, 0.01, 4)
    roots = roots_left + roots_right
    print("Znalezione pierwiastki w przedziale [-3,4]:")
    print(len(roots))
    for r in roots:
        print(f"{r:.12f}, {f2(r)}")
    
    roots = find_roots(f3, -3, 4)
    print("Znalezione pierwiastki w przedziale [-3,4]:")
    print(len(roots))
    for r in roots:
        print(f"{r:.12f}, {f3(r)}")
