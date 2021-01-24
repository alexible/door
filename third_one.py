# Synchronizing binary
from random import choice

def create_binary_list(lenght):
    seq = [0, 1]
    bin_list = []

    for _ in range(lenght):
        bin_list.append(choice(seq))

    return bin_list 
# print(create_binary_list(4))

def binary_samples(num_samples=16, lenght=4):
    bin_samps = []
    for _ in range(num_samples):
        bin_samps.append(create_binary_list(lenght))
    return bin_samps
    
bin_list = binary_samples(num_samples=1000, lenght=8)



# Analize binary
# def dec_binary_calc(bin_list):
#     d = {}
#     for dec, val in enumerate(bin_list):
#         d[dec] = val
#     return d

# d_c = dec_binary_calc(bin_list)
# for k, v in d_c.items():
#     print(f'{k}:\t{v}')


# How many times occures
def occer_binary(bin_list):
    d1 = {}
    for i in bin_list:
        sum_ = sum(i)
        if sum_ not in d1:
            d1[sum_] = 0
        d1[sum_] += 1
    return d1

d_occur = occer_binary(bin_list)

for p, g in sorted(d_occur.items()):
    print(f'{p}: {g}')
