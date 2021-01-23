data = [.20, .22, .25, .30, .34, .41, .55, .56, 1.42, 1.70, 1.83, 2.20, 2.25, 3.07, 3.25, 4]

data.sort()
sum_num = sum(data)
len_num = len(data)

def median(set_number):
    if len_num % 2 == 0:
        median1 = data[len_num // 2]
        median2 = data[(len_num // 2) - 1]
        median_cal = (median1 + median2) / 2
    else:
        median_cal = data[len_num // 2]

    return median_cal

print(median(data))
