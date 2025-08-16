#include <iostream>
#include <vector>
using namespace std;

#define SZ 1001

int n;
vector<pair<int, int>> lines;
vector<int> selected;
int ans;

bool Possible() {
	bool check[SZ] = { false };

	for (int i = 0; i < selected.size(); i++) {
		pair<int, int> now = lines[selected[i]];

		int st = now.first;
		int en = now.second;

		for (int i = st; i <= en; i++) {
			if (check[i])
				return false;
			check[i] = true;
		}
	}

	return true;
}

void func(int index) {
	if (index == n) {
		if (Possible())
			ans = max(ans, int(selected.size()));
		return;
	}

	// 현재 index를 선택할지 말지 이지선다
	// 반복문을 쓰지 않고, 재귀를 두 번

	// 선택함
	selected.push_back(index);
	func(index + 1);
	selected.pop_back();

	// 선택 안 함
	func(index + 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;

		lines.push_back({ a, b });
	}

	func(0);

	cout << ans;
}
