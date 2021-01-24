def lcm(x, y):
  if x > y:
    z = y
  else:
    z = x
  while (True):
    if z % x == 0 and z % y == 0:
      lcm_last = z
      break
    z += 1
  return lcm_last

user_1 = int(input('please print a first positive integer: '))
user_2 = int(input('please input a second positive integer: '))
print(lcm(user_1, user_2))
