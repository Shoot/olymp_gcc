from os import system
from random import randint

# system("g++ sol.cpp -o CPP")
n = -1
def add_test():
    global n
    n = randint(1, 5)
    print(f"N = {n}")
    s = f"{n}\n"
    points_st = set()
    points = list()

    while len(points) < 2 * n:
        x = randint(1,10)
        y = randint(1,10)
        if (x,y) in points_st:
            continue
        points_st.add((x, y))
        points.append((x, y))
    for x,y in points:
        s += f"{x} {y}\n"

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
            if n == 1:
                print(f"my={f0.read()}, his={f.read()}")
            assert f0.read() == f.read()
for j in range(1, 100000):
    print('hi')
    add_test()
    stable()
    unstable()
    check()
    print(j)
