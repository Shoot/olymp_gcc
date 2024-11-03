from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    TESTS = randint(1, 100000)
    s = ""
    for j in range(TESTS):
        s += chr(ord('a')+randint(0, 25))
    with open('001.dat', 'w') as f:
        f.write(s)
def stable ():
    system("python3 stable.py < 001.dat > 001.ans")
    print('ok')
def unstable ():
    system("./C < 001.dat > his.ans")
    print('ok2')
def check ():
    with open('his.ans') as f:
        with open('001.ans') as f0:
            assert f0.read() == "Yes\n" and f.read() == "Yes\n"
for j in range(1, 100000):
    print('hi')
    add_test()
    # stable()
    unstable()
    check()
    print(j)
