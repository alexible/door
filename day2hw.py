while True:
  x = float(input('Input any number\n(only numer from 0 to 9)  '))
  z = int(x)
  if z == 7:
    print(' Your number is 7, you are all set!')
    break
  else:
    print(f'Your number is {x} \nWe expect 7 \nTry again')
