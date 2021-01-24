########################################                           
# lst = [3, 5, 7, 1, 3, 9, 5, 3, 7]

# new_lst = sorted(lst)
# # print(new_lst)
# new_ser = []
# def no_par_list(lst1):
#     for it in new_lst:
#         if not it in new_ser:
#             new_ser.append(it)

#     return new_ser

# no_par_list(new_lst)

# for idx, value in enumerate(new_ser):
    
#     # new_lst[idx] = value
#     print(f'{idx}:  {value}')

# ###################################################                   enumerate


# alpha = list('abcdefghijklmnopqrstuvwxyz')

# def number_alpha(ls):
#     # alpha = list('abcdefghijklmnopqrstuvwxyz')
#     alpha2 = []
#     nums = []
    
#     for num, let in enumerate(ls, 1):
#         alpha2.append(let)
#         nums.append(num)
    
#     return alpha2, nums

# # print(number_alpha(alpha))
# new_lst_1 = number_alpha(alpha)
# print(new_lst_1)

# # for k, v in new_lst_1.items():                             # I'm stuck here
# #   print(f' {k}: {v} ')


# ################################################                  ???

# food_lst = ['Pancakes', 'Omlet', 'Toast', 'Waffles', 'Bacon', 'Sausage', 'Orange Juice']
# def food(food_new):
#   idx = 0
#   for i in food_new:
#     # idx = 0
#     idx += 1
#     print(idx, i) 
#   return 
# food(food_lst)

# for idx, food in enumerate (food_lst, 1):
#   print(f'Press {idx} for {food}.')

# ###############################################                 dictionary

lst_dic = ['apple', 'orange', 'banana', 'potetoes', 'rice', 'tomato', 'pig', 'dog']

new_dic = {}

for i in range(len(lst_dic)):
    new_dic[i + 1] = lst_dic[i]
print(new_dic)

for k, v in new_dic.items():
    print(f'{k}: {v}')