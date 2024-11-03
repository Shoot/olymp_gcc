import random
import sys, math
import os
from io import BytesIO, IOBase
from collections import defaultdict as ddic, Counter, deque
from itertools import groupby, combinations, product
from heapq import *
from math import ceil, gcd, log, log2, pi, isqrt, inf
from bisect import bisect, bisect_left
from functools import cache, reduce
from itertools import *
from collections import OrderedDict
red = lambda function, sequence, value=0: (lambda good, s, a: [(a := good(a, e)) for e in s][-1])(function, sequence, value) if sequence else value
ints, dbg, yes, bob = lambda: list(map(int, input().split())), lambda *args, **kwargs: print(*args, file=sys.stderr, **kwargs), lambda _: print('YES' if _ else 'NO'), lambda _: print('Bob' if _ else 'Alice')
tests, = (1,)
# tests, = ints()
for test in range(tests):
    input()
    print("Yes")