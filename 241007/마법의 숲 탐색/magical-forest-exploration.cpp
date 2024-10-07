#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int map[75][75];
int start[1001];
int out[1001];
int Max[1001];
int r, k ,c;
int dx[3] = {0, -1, 1};
int dy[3] = {1, 0, 0};
int xd[5] = { 0, 1, 0, -1, 0 };
int yd[5] = { -1, 0, 1, 0, 0 };
void mem() {
    for (int i = 0; i <= r + 1; i++) {
        for (int j = 0; j <= c + 1; j++) {
            if (j == 0 || i == r + 1 || j == c + 1) {
                if (i == 0) map[j][i] = 0;
                else  map[j][i] = -1;
            }
            else map[j][i] = 0;
        }
    }
}
bool check(int x, int y, int u, int g) {
    if (u == 0) {
        if (map[x - 1 + dx[u]][y + dy[u]] == 0 && map[x + 1 + dx[u]][y + dy[u]] == 0 && map[x + dx[u]][y + dy[u] + 1] == 0) {
            for (int i = 0; i < 5; i++) {
                map[x + xd[i]][y + yd[i]] = 0;
            }
            for (int i = 0; i < 5; i++) {
                map[x + xd[i]][y + 1 + yd[i]] = g;
            }
            return true;
        }
        else return false;
    }
        else if(u == 1) {
        if (map[x - 2][y] == 0 && map[x - 1][y + 1] == 0 && map[x - 1][y - 1] == 0 &&  map[x - 2][y + 1] == 0 && map[x - 1][y + 2] == 0) {
                for (int i = 0; i < 5; i++) {
                    map[x + xd[i]][y + yd[i]] = 0;
                }
                for (int i = 0; i < 5; i++) {
                    map[x - 1 + xd[i]][y + 1 + yd[i]] = g;
                }
                return true;
            }
            else return false;
        }
        else if (u == 2) {
            if (map[x+1][y-1] == 0 && map[x+2][y] == 0 && map[x+1][y+1] == 0 && map[x + 2][y + 1] == 0 && map[x + 1][y + 2] == 0) {
                for (int i = 0; i < 5; i++) {
                    map[x + xd[i]][y + yd[i]] = 0;
                }
                for (int i = 0; i < 5; i++) {
                    map[x + 1 + xd[i]][y + 1 + yd[i]] = g;
                }
                return true;
            }
            else return false;
        }
}
int turn1(int num){
    if (num != 0) return num - 1;
    return 3;
}
int turn2(int num){
    if (num != 3) return num + 1;
    return 0;
}
int move(int num){
    int x = start[num]; int y = 1;
    while (1) {
        if (check(x, y, 0, num)) {
            y += 1;
        }
        else if (check(x, y, 1, num)) {
            x -= 1; y += 1;
            out[num] = turn1(out[num]);
        }
        else if (check(x, y, 2, num)) {
            x += 1; y += 1;
            out[num] = turn2(out[num]);
        }
        else {
            if (y < 2) {
                mem();
                return 0;
            }
                queue <int> q;
                int X = x + xd[out[num]]; int Y = y + yd[out[num]];
                for (int i = 0; i < 4; i++) {
                    if (map[X + xd[i]][Y + yd[i]] > 0) q.push(map[X + xd[i]][Y + yd[i]]);
                }
                Max[num] = y + 1;
                while(!q.empty()){
                    int qn = q.front();
                    q.pop();
                    Max[num] = max(Max[num], Max[qn]);
                }
            return Max[num];
        }
    }
}
int main() {
    int res = 0;
    cin >> r >> c >> k;
    for (int i = 1; i <= k; i++) {
        cin >> start[i] >> out[i];
    }
    mem();
    for (int i = 1; i <= k; i++) {
        res += move(i);
    }
    cout << res;
    return 0;
}