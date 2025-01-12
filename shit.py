from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
def add_test():
    lines = randint(1, 10)
    drivers = randint(1, 10)
    stops = randint(1, 10)
    s = f"{lines} {drivers} {stops}\n"
    for i in range(lines):
        this_stops = randint(1, stops)
        for j in range(this_stops):
            s += f"{randint(1, stops)}"
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
