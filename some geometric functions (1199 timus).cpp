#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef long double LF;
typedef pair<LF, LF> pLFLF;
typedef vector<pLFLF> vpLFLF;
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

const LF INF = 1e14;
const LF eps = 0.00000000000001;
LF scalar_product(LF middleX, LF middleY, LF x1, LF y1, LF x2, LF y2)
{
    return (x1 - middleX) * (x2 - middleX) + (y1 - middleY) * (y2 - middleY);
}

LF pointToPoint_distance(LF x1, LF y1, LF x2, LF y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

LF cosinus(LF middleX, LF middleY, LF x1, LF y1, LF x2, LF y2)
{
    return (scalar_product(middleX, middleY, x1, y1, x2, y2) / (pointToPoint_distance(middleX, middleY, x1, y1) * pointToPoint_distance(middleX, middleY, x2, y2)));
}

LF sinus_byCosinus(LF cosine)
{
    return sqrt(1 - cosine * cosine);
}

LF triangle_area(LF x, LF y, LF x1, LF y1, LF x2, LF y2)
{
    return pointToPoint_distance(x, y, x1, y1) * pointToPoint_distance(x, y, x2, y2) * sinus_byCosinus(cosinus(x, y, x1, y1, x2, y2)) / 2;
}

LF pointToSegment_distance(LF x, LF y, LF x1, LF y1, LF x2, LF y2)
{
    if (scalar_product(x1, y1, x, y, x2, y2) < eps || scalar_product(x2, y2, x, y, x1, y1) < eps)
    {
        return min(pointToPoint_distance(x, y, x1, y1), pointToPoint_distance(x, y, x2, y2));
    }
    else
    {
        return 2*triangle_area(x, y, x2, y2, x1, y1) / pointToPoint_distance(x2, y2, x1, y1);
    }
}

void get_coords_of_perpendicular_base(LF &x1, LF &y1, LF &x2, LF &y2, LF &xa, LF &ya, LF &xb, LF &yb,
                LF &xc, LF &yc, LF &min_dist)
{
    /*
    this function takes x1,y1 - coords of starting point, x2,y2 - coords of end point, xa, ya - coords of point from witch perpendicular is ommited on segment (xb,yb)<->(xc,yc)
    and *changes* coords of base (x2, y2) of perpendicular on the segment OR (x2, y2) may be (xb,yb) or (xc,yc) if perpendicular *misses* the segment
    */
    LF cur_dist = pointToSegment_distance(xa, ya, xb, yb, xc, yc);
    if (cur_dist - min_dist < eps)
    {
        min_dist = cur_dist;
        x1 = xa;
        y1 = ya;

        if (scalar_product(xb, yb, x1, y1, xc, yc) >= eps && scalar_product(xc, yc, x1, y1, xb, yb) >= eps)
        {
            //if perp exists
            LF B = yc - yb, A = xc - xb, C = xa - xb;
            if (A != 0 && B != 0)
            {
                //in general, here are coords of base of perp
                y2 = (B * B * ya + A * B * C + A * A * yb) / (A * A + B * B);
                x2 = (-B * (y2 - ya)) / A + xa;
            }
            else if (A == 0 && B != 0)
            {
                //if segment is vertical
                y2 = ya;
                x2 = A*(y2-yb)/B + xb;
            }
            else if (A != 0 && B == 0)
            {
                //if segment is horizontal
                x2 = xa;
                y2 = B * (x2 - xb) / A + yb;
            }
            else
            {
                //degenerate segment
                x2 = xb;
                y2 = yb;
            }
        }
        else
        {
            //if exists only extreme points (perp doesnt fall within the line, so the min distance is (xa,ya)<->(xb/c, yb/c))
            if (pointToPoint_distance(xb, yb, xa, ya) - pointToPoint_distance(xc, yc, xa, ya) > eps)
            {
                x2 = xc;
                y2 = yc;
            }
            else
            {
                x2 = xb;
                y2 = yb;
            }
        }
    }
}
vi path_by_dijkstra(vector<vector<vector<LF>>> neighbour, int start, int end)
{
    int n = neighbour.size();
    vi link(n);
    vector<LF> d(n, INF);
    link[start] = -1;
    d[start] = 0;
    vector<bool> used(n, 0);
    for (int i = 0; i < n; i++)
    {
        int v = -1;
        for (int j = 0; j < n; j++)
        {
            if (!used[j] && (v == -1 || d[j] < d[v]))
            {
                v = j;
            }
        }
        if (d[v] == INF)
            break;
        used[v] = 1;
        for (size_t j = 0; j < neighbour[v].size(); j++)
        {
            int to = j;
            LF len = neighbour[v][j][4];
            if (d[v] + len < d[to])
            {
                d[to] = d[v] + len;
                link[to] = v;
            }
        }
    }
    vi path;
    for (int v = end; v != -1; v = link[v])
        path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
}

void solve()
{
    LF mouseX, mouseY, cheeseX, cheeseY;
    cin >> mouseX >> mouseY >> cheeseX >> cheeseY;
    int n;
    cin >> n;
    vector<vpLFLF> figure(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            LF x, y;
            cin >> x >> y;
            figure[i].push_back(make_pair(x, y));
        }
    }
    figure.push_back({make_pair(mouseX, mouseY)});
    figure.push_back({make_pair(cheeseX, cheeseY)});
    n += 2;
    vector<vector<vector<LF>>> neighbour(n, vector<vector<LF>>(n, vector<LF>(5)));
    for (int i = 0; i < n; i++)
    { // O(n*n*k*k) ~ 1e6
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                continue;
            if (figure[j].size() != 1)
            {
                LF min_dist = INF;
                LF x1, x2, y1, y2;
                for (int v = 0; v < figure[i].size(); v++)
                {
                    for (int e = 0; e < figure[j].size(); e++)
                    {
                        LF xa = figure[i][v].first, ya = figure[i][v].second, xb = figure[j][e].first, yb = figure[j][e].second;
                        LF xc = figure[j][(e + 1) % figure[j].size()].first, yc = figure[j][(e + 1) % figure[j].size()].second;
                        get_coords_of_perpendicular_base(x1, y1, x2, y2, xa, ya, xb, yb, xc, yc, min_dist);
                    }
                }
                for (int v = 0; v < figure[j].size(); v++)
                {
                    for (int e = 0; e < figure[i].size(); e++)
                    {
                        LF xa = figure[j][v].first, ya = figure[j][v].second, xb = figure[i][e].first, yb = figure[i][e].second;
                        LF xc = figure[i][(e + 1) % figure[i].size()].first, yc = figure[i][(e + 1) % figure[i].size()].second;
                        get_coords_of_perpendicular_base(x1, y1, x2, y2, xa, ya, xb, yb, xc, yc, min_dist);
                    }
                }
                pLFLF trace_vector = {x2 - x1, y2 - y1};
                LF dt = pointToPoint_distance(trace_vector.first, trace_vector.second, 0, 0);
                x1 += trace_vector.first/10/dt;
                y1 += trace_vector.second/10/dt;
                x2 -= trace_vector.first/10/dt;
                y2 -= trace_vector.second/10/dt;
                vector<LF> temp = {x1, y1, x2, y2, min_dist - 0.2};
                neighbour[i][j] = temp;
            }
            else
            {
                LF min_dist = INF;
                LF x1, x2, y1, y2;

                for (int e = 0; e < figure[i].size(); e++)
                {
                    LF xa = figure[j][0].first, ya = figure[j][0].second, xb = figure[i][e].first, yb = figure[i][e].second;
                    LF xc = figure[i][(e + 1) % figure[i].size()].first, yc = figure[i][(e + 1) % figure[i].size()].second;
                    get_coords_of_perpendicular_base(x2, y2, x1, y1, xa, ya, xb, yb, xc, yc, min_dist);
                }
                for (int e = 0; e < figure[i].size(); e++)
                {
                    LF cur_dist = pointToPoint_distance(figure[i][e].first, figure[i][e].second, figure[j][0].first, figure[j][0].second);
                    if (min_dist - cur_dist > eps)
                    {
                        min_dist = cur_dist;
                        x1 = figure[i][e].first, x2 = figure[j][0].first, y1 = figure[i][e].second, y2 = figure[j][0].second;
                    }
                }

                pLFLF trace_vector = {x2 - x1, y2 - y1};
                LF dt = pointToPoint_distance(trace_vector.first, trace_vector.second, 0, 0);
                x1 += trace_vector.first/10/dt;
                y1 += trace_vector.second/10/dt;
                x2 -= trace_vector.first/10/dt;
                y2 -= trace_vector.second/10/dt;
                vector<LF> temp = {x1, y1, x2, y2, min_dist - 0.2};
                neighbour[i][j] = temp;
            }
        }
    }
    int mouse_index = n-2, cheese_index = n-1;
    for (int i = 0; i < n-1; i++){
        if (i != n-2 && neighbour[mouse_index][i][4] <= 0){
            mouse_index = i;
        }
        if (neighbour[cheese_index][i][4] <= 0){
            cheese_index = i;
        }
    }
    vi dijkstra = path_by_dijkstra(neighbour, mouse_index, cheese_index);
    vpLFLF cur_path;
    for (int m = 0; m < dijkstra.size() - 1; m++)
    {
        if (dijkstra[m] != mouse_index) cur_path.push_back(make_pair(neighbour[dijkstra[m]][dijkstra[m + 1]][0], neighbour[dijkstra[m]][dijkstra[m + 1]][1]));
        if (dijkstra[m+1] != cheese_index) cur_path.push_back(make_pair(neighbour[dijkstra[m]][dijkstra[m + 1]][2], neighbour[dijkstra[m]][dijkstra[m + 1]][3]));
    }
    std::cout << 2 * dijkstra.size() - 2 << "\n";
    std::cout << mouseX << " " << mouseY << "\n";
    for (int i = 0; i < cur_path.size(); i++)
    {
        std::cout << cur_path[i].first << " " << cur_path[i].second << "\n";
    }
    std::cout << cheeseX << " " << cheeseY << "\n";
}
int main()
{
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(12);
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
}
