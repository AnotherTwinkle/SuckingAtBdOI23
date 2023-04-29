#include <bits/stdc++.h>

using ll = long long;
using pair = std::array<int, 2>;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, k, m;
	std::cin >> n >> k >> m;

	std::vector<int> v(n, -1);
	while (m--) {
		int x; std::cin >> x;
		if (x == 1) {
			int a, b;
			std::cin >> a >> b; a--, b--;
			if (v[a] >= 0 && v[a] == v[b]) {
				std::cout << "0\n";
				return 0;
			} 
			else if (v[a]) v[b] = 0;
			else if (v[b]) v[a] = 0;
		} else {
			int a, b,c ; 
			std::cin >> a >> b >> c; a--, b--, c--;
			if (v[a] != -1 && v[b] != -1 && v[a] != v[b]) {
				std::cout << "0\n";
				return 0;
			} else if (v[a] == -1 && v[b] == -1) v[a] = v[b] = c;
			else if (v[a] == -1) v[a] = v[b];
			else if (v[b] == -1) v[b] = v[a];
		}
	}

	ll ans = 2;
	for (int i = 0; i < n; i++) {
		if (v[i] < 0) ans *= 2;
	}
	std::cout << ans << '\n';

}