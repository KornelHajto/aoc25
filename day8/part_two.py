
#!/usr/bin/env python3
import sys
import heapq
from collections import Counter

# Reads X,Y,Z points from a file named "input"
def read_points(filename):
    pts = []
    with open(filename) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            x, y, z = map(int, line.split(','))
            pts.append((x, y, z))
    return pts

class DSU:
    def __init__(self, n):
        self.p = list(range(n))
        self.sz = [1] * n
    def find(self, a):
        while self.p[a] != a:
            self.p[a] = self.p[self.p[a]]
            a = self.p[a]
        return a
    def union(self, a, b):
        ra = self.find(a)
        rb = self.find(b)
        if ra == rb:
            return False
        if self.sz[ra] < self.sz[rb]:
            ra, rb = rb, ra
        self.p[rb] = ra
        self.sz[ra] += self.sz[rb]
        return True
    def count_components(self):
        roots = set(self.find(i) for i in range(len(self.p)))
        return len(roots)

def squared_dist(a, b):
    return (a[0]-b[0])**2 + (a[1]-b[1])**2 + (a[2]-b[2])**2

# This file finds the FIRST connection that causes the entire set
# of points to become a single connected component.

def main():
    filename = "input"
    if len(sys.argv) >= 2:
        filename = sys.argv[1]

    pts = read_points(filename)
    n = len(pts)
    if n == 0:
        print(0)
        return

    dsu = DSU(n)
    target = 1  # number of components desired

    # Produce all edges lazily through a generator
    # Use a min-heap to pull edges in increasing distance
    # (Memory usage scales with number of points, not squared pairs)

    heap = []
    for i in range(n):
        for j in range(i+1, n):
            dist = squared_dist(pts[i], pts[j])
            heap.append((dist, i, j))

    heapq.heapify(heap)

    last_pair = None

    while dsu.count_components() > target and heap:
        dist, i, j = heapq.heappop(heap)
        if dsu.union(i, j):
            last_pair = (i, j)

    if last_pair is None:
        print(0)
        return

    i, j = last_pair
    # multiply X-coordinates of last required connection
    result = pts[i][0] * pts[j][0]
    print(result)

if __name__ == "__main__":
    main()
