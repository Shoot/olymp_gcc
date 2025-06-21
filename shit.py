from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    qs = int(2)
    txt = f"""10 {qs}
0 0 0 0 0
0 0 0 0 0
1 8
2 5
3 5
3 8
4 9
4 10
5 6
6 9
7 9\n"""
    maxi = int(1e9)
    for i in range(qs):
        tp = randint(1, 2)
        if tp == 1:
            txt += f"{1} {randint(1, 6)} {randint(1, maxi)}\n"
        else:
            txt += f"{2} {randint(1, 6)} {randint(1, 6)}\n"

    with open('001.dat', 'w') as f:
        f.write(f"{txt}")
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
