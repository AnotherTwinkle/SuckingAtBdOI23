#include <bits/stdc++.h>

using ll = long long;
using pair = std::array<int, 2>;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;
	std::vector<ll> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}

	std::vector<std::vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; std::cin >> u >> v; u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	std::vector<std::vector<int>> distance(n, std::vector<int>(n));
	std::function<void(int, int, int, int)> dfs = [&](int u, int v, int f, int d) {
		d++;
		for (int i : adj[v]) {
			if (i == v || i == f) continue;
			distance[u][i] = d;
			dfs(u, i, v, d);
		}
	};



	for (int i = 0; i < n; i++) {
		dfs(i, i, -1, 0);
	}

	for (int i = 0; i < n; i++) {
		ll min = 1e18;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			ll dist = 0;
			for (int l = 0; l < n; l++) {
				dist += std::min(distance[l][j] * w[l], distance[l][i] * w[l]);
			}
			min = std::min(dist, min);
		}
		std::cout << min << '\n';
	}

}