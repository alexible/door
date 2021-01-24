def do_somthing(x):
    return x **2 +25 
print(do_somthing(4))


# Synchronizing binary
def binary_calc():
    lst_binary = []

    for a in range(2):
        for b in range(2):
            for c in range(2):
                for d in range(2):
                    lst_binary.append([a, b, c, d])
    return lst_binary

lst_binary = binary_calc()
# print(lst_binary)

# for i in lst_binary:
#     print(i)


# Analize binary
def dec_binary_calc(lst_binary):
    d = {}
    for dec, val in enumerate(lst_binary):
        d[dec] = val
    return d

d_c = dec_binary_calc(lst_binary)
for k, v in d_c.items():
    print(f'{k}:\t{v}')


# How many times occures
def occer_binary(lst_binary):
    d1 = {}
    for i in lst_binary:
        sum_ = sum(i)
        if sum_ not in d1:
            d1[sum_] = 0
        d1[sum_] += 1
    return d1

d_occur = occer_binary(lst_binary)
for p, g in sorted(d_occur.items()):
    # print(f'{p}:\t{g}')
    print(f'{p}:{"*"*g}')


# Create random binary list
from random import choice

def create_binary_list(lenghs):
    seq = [0, 1]
    bin_list = []

    for _ in range(lenghs):
        bin_list.append(choice(seq))
    return bin_list

print(create_binary_list(4))


