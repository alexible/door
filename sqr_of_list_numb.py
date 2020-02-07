string = input("Input integer numbers separated by dashes '-'  ")
def square_it():
  new_dict = {}
  for num in string:
   if(num == '-'):
      continue
   else:
      new_dict[int(num)] = int(num) ** 2
  return new_dict
print('Your answer in square numberis:')
print(square_it())
