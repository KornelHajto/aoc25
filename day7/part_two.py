
#!/usr/bin/env python3

import sys
sys.setrecursionlimit(10**7)

# Read the manifold from "input"
with open("input") as f:
    grid = [line.rstrip("\n") for line in f]

R = len(grid)
C = len(grid[0])

# Find S
start_row = start_col = None
for r in range(R):
    for c in range(C):
        if grid[r][c] == "S":
            start_row, start_col = r, c
            break
    if start_row is not None:
        break

if start_row is None:
    print("No S found", file=sys.stderr)
    sys.exit(1)

# Memoization table
memo = {}

def dfs(r, c):
    """Return number of timelines from position (r,c)."""
    # Exiting the manifold counts as one timeline
    if r >= R or c < 0 or c >= C:
        return 1

    key = (r, c)
    if key in memo:
        return memo[key]

    ch = grid[r][c]

    if ch == "^":
        # Split: left and right timelines
        res = dfs(r + 1, c - 1) + dfs(r + 1, c + 1)
    else:
        # Normal: continue downward
        res = dfs(r + 1, c)

    memo[key] = res
    return res


answer = dfs(start_row + 1, start_col)
print(answer)
