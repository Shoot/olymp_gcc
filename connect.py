import os,sys
r1, w1 = os.pipe()
r2, w2 = os.pipe()
a = os.fork()
if a == 0:
    os.dup2(r1, 0)
    os.dup2(w1, 1)

    os.system("./interact")
    sys.exit(0)
a = os.fork()
if a == 0:
    os.dup2(r2, 0)
    os.dup2(w2, 1)

    os.system("./interactor")
    sys.exit(0)
