def calc_min(a, b, eps, f):
   SQRT5 = 5**(1 / 2)
   x1 = a + (3 - SQRT5) / 2 * (b - a)
   x2 = a + (SQRT5 - 1) / 2 * (b - a)

   f1 = 0.0
   f2 = 0.0
   a1 = 0.0
   b1 = 0.0

   n = 0

   while abs(b - a) > eps:
      f1 = f(x1)
      f2 = f(x2)
      a1 = a
      b1 = b

      if f1 < f2:
         b = x2 
         x2 = x1
         x1 = a + (3 - SQRT5) / 2 * (b - a)
      else:
         a = x1
         x1 = x2
         x2 = a + (SQRT5 - 1) / 2 * (b - a)

      n = n + 1
   return a, n