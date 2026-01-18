#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

#define V_SZ 20'0010

struct Cmp {
	// second가 가장 작은 정점을 먼저 꺼내야 함
	// a가 크면 a를 뒤로 보냄 (작은 값이 앞으로 오게 되는 구조)
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
		return a.second > b.second;
	}
};

int v, e;
int st;
vector<vector<pair<int, int>>> graph;
priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> pq;
int dist[V_SZ];

// priority_queue< T, Container, Compare >
// T: 우리가 넣을 원소의 타입
// Container: 실제로 저장하는 자료구조 (vector<T> 꼴이 일반적)

void Dijkstra() {
	while (!pq.empty()) {		
		pair<int, int> tmp = pq.top(); pq.pop();

		// st -> now
		int now_node = tmp.first;
		int now_dist = tmp.second;
		
		// now가 예전 정보면 버려
		// dist에 이미 더 짧은 거리를 구해서 넣어뒀음
		if (now_dist > dist[now_node])
			continue;

		// now의 이웃들 거리 갱신
		// st -> nxt 와 st -> now -> nxt 거리 비교
		for (pair<int, int> nxt : graph[now_node]) {
			int nxt_node = nxt.first;
			int nxt_dist = nxt.second;

			if (dist[nxt_node] > dist[now_node] + nxt_dist) {
				dist[nxt_node] = dist[now_node] + nxt_dist;
				pq.push({ nxt_node, dist[nxt_dist] });
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> v >> e >> st;
	graph.resize(v + 1);

	for (int i = 0; i < e; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		// a -> b 비용 c
		// 양방향일 경우, b -> a 비용 c도 넣어주기
		graph[a].push_back({ b, c });
	}

	for (int i = 1; i <= v; i++)
		dist[i] = 1e9;

	dist[st] = 0;
	pq.push({ st, 0 });

	Dijkstra();

	for (int i = 1; i <= v; i++) {
		if (dist[i] == 1e9)
			cout << "INF";
		else
			cout << dist[i];
		cout << endl;
	}
}
