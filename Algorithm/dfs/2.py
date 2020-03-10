inf = 9999
# m = [[0, inf, inf, inf, 6],
#      [9, 0, 3, inf, inf],
#      [2, inf, 0, 5, inf, inf],
#      [inf, inf, inf, 0, 1],
#      [inf, inf, 0, inf, inf]]

m = [[0, 1, 12, inf, inf, inf],
     [inf, 0, 9, 3, inf, inf],
     [inf, inf, 0, inf, 5, inf],
     [inf, inf, 4, 0, 13, 15],
     [inf, inf, inf, inf, 0, 4],
     [inf, inf, inf, inf, inf, 0]
     ]

# m = [[0, 2, 6, 4],
#      [inf, 0, 3, inf],
#      [7, inf, 0, 1],
#      [5, inf, 12, 0]]

# m = [[0, 1, 3],
#      [inf, 0, 1],
#      [inf, inf, 0]]

size = len(m[0])

route = []
routes = []


def dfs(m, start, end):
    route.append(start)
    temp = [i for i in range(size) if m[start][i] != inf and m[start][i] != 0]
    if start == end:
        routes.append(route.copy())
        route.pop()
    else:
        if len(temp) == 0:
            route.pop()
        else:
            for i in temp:
                if not i in route:
                    dfs(m, i, end)
                if i == temp[-1]:
                    route.pop()
    return routes

def distances(m, start, end):
    routes = dfs(m, start, end)
    routes_ = []
    for route in routes:
        temp = 0
        for i in range(len(route)-1):
            temp += m[route[i]][route[i+1]]
        routes_.append((route, temp))
    return sorted(routes_, key=lambda x: x[1])


print(distances(m, 0, 5))
