#include <bits/stdc++.h>

using ll = long long;
using pair = std::array<int, 2>;

int main() {
	// std::ios::sync_with_stdio(false);
	// std::cin.tie(nullptr);

	int n, k;
	std::cin >> n >> k;
	std::vector<std::vector<int>> v(n, std::vector<int>());
	
	for (int i = 0; i < n; i++) {
		int x; std::cin >> x;
		v[i] = std::vector<int>(x);
		for (int j = 0; j < x; j++) {
			std::cin >> v[i][j];
		}
	}

	int min = 1e9; std::vector<int> chosenmin;
	for (int i = 0; i < (1 << (n)); i++) {
		// std::cout << i << '\n';
		std::vector<int> chosen;
		for (int j = 0; (1 << j) <= i; j++) {
			if (i & (1 << j)) chosen.push_back(j);
		}

		std::set<int> S;
		for (int x : chosen) {
			for (int y : v[x]) {
				S.insert(y);
			}
		}

		bool flag = 1;
		for (int i = 1; i <= k; i++) {
			if (!S.count(i)) {
				flag = 0;
				break;
			}
		}

		if (flag && (int)chosen.size() < min) {
			min = (int)chosen.size();
			chosenmin = chosen;
		}
	}
	std::cout << min << '\n';
	for (int i = 0; i < chosenmin.size(); i++) {
		std::cout << chosenmin[i] + 1 << " \n"[i == chosenmin.size() - 1];
	}
}