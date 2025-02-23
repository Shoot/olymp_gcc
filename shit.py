from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    n = randint(2, 20)
    one = ""
    another = ""
    for i in range(n):
        one += chr(ord('a')+randint(0, 1))
    x = randint(0, n-1)
    with open('001.dat', 'w') as f:
        f.write(f"{one}\n{one[x:]+one[:x]}")
def stable ():
    system("./his < 001.dat > his.ans")
    # print('ok')
def unstable ():
    system("./my < 001.dat > my.ans")
    # print('ok2')
def check ():
    with open('his.ans') as f:
        with open('my.ans') as f0:
            x = f0.read().strip()
            y = f.read().strip()
            print(f"{x} vs {y}")
            assert x == y
for j in range(1, 100000):
    print('hi')
    add_test()
    stable()
    unstable()
    check()
    print(j)
