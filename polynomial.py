def p(coefficient_in_list, x, power):
  return coefficient_in_list * x ** power

def polynom(lst, n):
  sm = 0
  size_list = len(lst) - 1
  for i in range(size_list, -1, -1):
    idx_in_list = size_list - i
    # test comment print(power, idx)
    # test comment  print(p(lst[idx] , n, power))
    sm += p(lst[idx_in_list] , n, i)
  return sm
print(polynom([1, 4, 2, 7], 23))
