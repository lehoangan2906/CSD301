#include <bits/stdc++.h>
using namespace std;

const int MAX = 10;     // giả sử bài toán có tối đa 10 đỉnh
const int MAX_MASK = 1 << MAX;      //max của mask = 1 * a^n = 1 * 2^MAX
const int INF = 1e9;

int f[MAX_MASK][MAX];   // khởi tạo bảng dp 2 chiều
int n, m;
vector<vector<pair<int, int>>> graph;   // khởi tạo đồ thị có dạng vector 2 chiều chứa các cặp đỉnh và trọng số biểu diễn cho các cạnh

int minimumHamilton(){
    int nMask = 1 << n;

    // khởi tạo giá trị của tất cả các ô trong bảng là INF
    for (int i = 0; i < nMask; i++){
        for (int j = 0; j < n; j++){
            f[i][j] = INF;
        }
    }

    // đánh dấu những đường đi chỉ có một đỉnh là 0
    for (int i = 0; i < n; i++){
        f[1 << i][i] = 0;
    }

    // duyệt qua tất cả các trạng thái có thể có
    for (int mask = 1; mask < nMask; mask++){
        // xem đỉnh u là đỉnh kết thúc của trạng thái hiện tại -- prev
        for (int u = 0; u < n; u++){

            // kiểm tra xem đường đi đang xét có đi qua đỉnh u và có kết thúc tại đỉnh u hay không
            if (((mask >> u) & 1) && f[mask][u] != INF){
                // duyệt qua tất cả các đỉnh v kề với đỉnh u
                for (int i = 0; i < graph[u].size(); i++){
                    int v = graph[u][i].first;
                    int w = graph[u][i].second;

                    // chỉ duyệt những đỉnh chưa được ghé thăm trước đó nên nếu mask tại vị trí v = 0 tức 
                    // là đỉnh v chưa nằm trong đường đi thì mới tiếp tục xét
                    if (((mask >> v) & 1) == 0){
                        // bật bit tương ứng tại vị trí v bằng toán tử | hay OR => mask mới có thêm đỉnh v và đỉnh kết thúc của đường đi sẽ là v
                        //=> giá trị của đường đi bằng min của cách đi đã khám phá trước đó (vì có thể có nhiều đường đi dẫn đến v) và đường đi kết thúc 
                        // tại u + chi phí để đến v là w
                        f[mask | (1 << v)][v] = min(f[mask | (1 << v)][v], f[mask][u] + w);
                    }
                }
            }
        }
    }

    int res = INF;

    // duyệt qua mọi đỉnh kết thúc có thể có
    for (int i = 0; i < n; i++){
        // kết quả sẽ là min của các trạng thái cuối cùng khi mask = 2^n - 1 và kết thúc tại đỉnh i
        res = min(res, f[nMask - 1][i]);
    }

    return res;
}

int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    graph.assign(n, vector<pair<int, int>>());  // assign n value mới vào vector graph

    for (int u, v, w, i = 0; i < m; i++){
        // input các cặp đỉnh và trọng số của đồ thị
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    cout << minimumHamilton();

    return 0;
}



