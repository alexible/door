def string_test(s):
    d={"UPPER_CASE":0, "LOWER_CASE":0}
    for c in s:
        if c.isupper():
           d["UPPER_CASE"]+=1
        elif c.islower():
           d["LOWER_CASE"]+=1
        else:
           pass
    print ("Your Original String : ", s)
    print ("The Upper case characters : ", d["UPPER_CASE"])
    print ("The Lower case Characters : ", d["LOWER_CASE"])

a = input("Enter your own text :  ")
string_test(a)
