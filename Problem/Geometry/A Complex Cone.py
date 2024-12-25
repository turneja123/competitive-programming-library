#https://www.spoj.com/problems/ACC/
import math

def union(z, r, h, a, b):
    R = r * (1 - z/h)
    if R <= 1e-14:
        return 0.0
    d = (a + b) * z / h
    s = math.pi * R * R
    if d >= 2 * R:
        return 2 * s
    t = d / (2 * R)
    t = min(t, 1.0)
    t = max(t, -1.0)
    I = 2 * (R * R) * math.acos(t) - (d / 2.0) * math.sqrt(4 * (R * R) - d * d)
    return 2 * s - I

def integrate(r, h, a, b):
    N = 20000
    dz = h / N
    total = 0.5 * (union(0, r, h, a, b) + union(h, r, h, a, b))
    for i in range(1, N):
        z = i * dz
        total += union(z, r, h, a, b)
    volume = total * dz
    return volume

def trunc(value):
    s = f"{value:.10f}" 
    j = s.find('.')
    if j != -1:
        s = s[:j + 2]  
    return s


for _ in range(int(input())):
    input_line = input()
    r,h,a,b = map(int, input_line.strip().split())
    print(trunc(integrate(r,h,a,b)))
