def two_num(x, y):
  if x + y > x and x + y > y:
    print('Summ of two number are positive')
  elif x + y == x or x + y == y:
    print('One of the number is 0')
  else:
    print('At list one number is negative')
two_num(10, -2)
