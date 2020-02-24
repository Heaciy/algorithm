import copy
inf = 9999

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


size = len(m[0])


def init_route(e):
    route = copy.deepcopy(e)
    for i in range(size):
        for j in range(size):
            if e[i][j] != inf:
                route[i][j] = [i, j]
                if e[i][j] == 0:
                    route[i][j] = [i]
            else:
                route[i][j] = []
    return route


def print_route(e, route, start, end):
    if len(route[start][end]) > 1:
        route_ = [str(i) for i in route[start][end]]
        print('route: ' + '-->'.join(route_))
        print('distance: {}'.format(e[start][end]))
    elif len(route[start][end]) == 1:
        print('不动')
        print('distance: 0')

    else:
        print("Cant't Arrive!!!")


# dijkstra https://blog.csdn.net/lbperfect123/article/details/84281300
def dijkstra(e, route, rownum):
    dis = copy.deepcopy(e[rownum])
    vis = [0 for i in range(size)]
    for i in range(size):
        min = inf
        for i in range(size):
            if not vis[i] and dis[i] < min:
                min, temp = dis[i], i
        vis[temp] = 1
        for i in range(size):
            if dis[temp] + e[temp][i] < dis[i]:
                dis[i] = dis[temp] + e[temp][i]
                route[rownum][i] = route[rownum][temp][:-1] + route[temp][i]
    return dis


def dijkstra_pro(m, start, end):
    e = copy.deepcopy(m)
    route = init_route(e)
    for i in range(size):
        e[i] = dijkstra(e, route, i)

    print_route(e, route, start, end)


# floyd https://blog.csdn.net/Harington/article/details/81982299
def floyd_route(m, start, end):
    e = copy.deepcopy(m)
    route = init_route(e)
    for k in range(size):
        for i in range(size):
            for j in range(size):
                if e[i][k] != inf and e[k][j] != inf and e[i][j] > e[i][k]+e[k][j]:
                    e[i][j] = e[i][k] + e[k][j]
                    route[i][j] = route[i][k][:-1] + route[k][j]

    print_route(e, route, start, end)


if __name__ == '__main__':
    dijkstra_pro(m, 5, 4)
    floyd_route(m, 4, 5)
