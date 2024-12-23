from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    N = randint(1, 50)
    s = ""
    s += f"{N}\n"
    while 1:
        o = []
        for j in range(N):
            o.append(randint(0, 1000))
        if sum(o) <= 10000:
            break
        print("tried")
    for j in o:
        s += f"{j} "
    s += "\n"
    with open('001.dat', 'w') as f:
        f.write(s)
def stable ():
    system("./his < 001.dat > his.ans")
    print('ok')
def unstable ():
    system("./my < 001.dat > my.ans")
    print('ok2')
def check ():
    with open('his.ans') as f:
        with open('my.ans') as f0:
            print(f"my={f0.read()}, his={f.read()}")
            assert f0.read() == f.read()
for j in range(1, 100000):
    print('hi')
    add_test()
    stable()
    unstable()
    check()
    print(j)
