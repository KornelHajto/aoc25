
#!/usr/bin/env python3

import sys
import math
import itertools
import heapq
from collections import Counter

def read_points(filename):
    pts = []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            x,y,z = map(int, line.split(','))
            pts.append((x,y,z))
    return pts

class DSU:
    def __init__(self, n):
        self.p = list(range(n))
        self.sz = [1]*n
    def find(self, a):
        while self.p[a] != a:
            self.p[a] = self.p[self.p[a]]
            a = self.p[a]
        return a
    def union(self, a, b):
        ra = self.find(a); rb = self.find(b)
        if ra == rb:
            return False
        if self.sz[ra] < self.sz[rb]:
            ra, rb = rb, ra
        self.p[rb] = ra
        self.sz[ra] += self.sz[rb]
        return True
    def sizes(self):
        root_count = Counter()
        for i in range(len(self.p)):
            root_count[self.find(i)] += 1
        return list(root_count.values())

def squared_dist(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2 + (a[2]-b[2])**2

def main():
    filename = "input"
    k = 1000
    if len(sys.argv) >= 2:
        filename = sys.argv[1]
    if len(sys.argv) >= 3:
        k = int(sys.argv[2])

    points = read_points(filename)
    n = len(points)
    if n == 0:
        print(0)
        return

    # If total pairs <= k, take them all
    total_pairs = n * (n-1) // 2
    k = min(k, total_pairs)

    # Use heapq.nsmallest to find k smallest (dist, i, j) without storing all pairs
    # We iterate over combinations (i<j), produce (dist, i, j)
    def pairs():
        for i in range(n):
            pi = points[i]
            for j in range(i+1, n):
                yield (squared_dist(pi, points[j]), i, j)

    smallest_k = heapq.nsmallest(k, pairs(), key=lambda x: x[0])

    dsu = DSU(n)
    # Connect each of the k pairs in the order of increasing distance
    for dist, i, j in smallest_k:
        dsu.union(i, j)

    sizes = dsu.sizes()
    sizes.sort(reverse=True)

    # multiply top three sizes (pad with 1s if fewer than 3 components)
    top3 = sizes[:3] + [1]*max(0, 3 - len(sizes))
    prod = 1
    for s in top3:
        prod *= s

    print(prod)

if __name__ == "__main__":
    main()
