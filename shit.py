from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    s = f"1\n{randint(1, 10)} {randint(1, 10)} {randint(1, 10)}"
    with open('001.dat', 'w') as f:
        f.write(s)
def stable ():
    system("./his < 001.dat > his.ans")
    # print('ok')
def unstable ():
    system("./my < 001.dat > my.ans")
    # print('ok2')
def check ():
    with open('his.ans') as f:
        with open('my.ans') as f0:
            assert f0.read() == f.read()
for j in range(1, 100000):
    print('hi')
    add_test()
    stable()
    unstable()
    check()
    print(j)
