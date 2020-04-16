x = 0
while 1:
    if (42**(x) % 191) == 178 or x > 191:
        print(x)
        break
    x+=1
