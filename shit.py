from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    TESTS = 1000
    s = f"{TESTS}\n"
    for i in range(TESTS):
        val = str(randint(1, 1000000000000000000))
        s += f"{val}\n"
    with open('001.dat', 'w') as f:
        f.write(s)
def stable ():
    system("python3 stable.py < 001.dat > 001.ans")
    print('ok')
def unstable ():
    system("./A < 001.dat > his.ans")
    print('ok2')
def check ():
    with open('his.ans') as f:
        with open('001.ans') as f0:
            assert f0.read() == f.read()
while True:
    print('hi')
    add_test()
    stable()
    unstable()
    check()
