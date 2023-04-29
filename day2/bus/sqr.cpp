#include <bits/stdc++.h>

using ll = long long;
using pair = std::array<int, 2>;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;
	std::vector<ll> w(n);
	for (ll i = 0; i < n; i++) {
		std::cin >> w[i];
	}

	std::vector<std::vector<int>> adj(n);
	for (int i = 0; i < n - 1; i++) {
		ll u, v; std::cin >> u >> v; u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int u = adj[0][0], prev = -1;
	while (adj[u].size() > 1) {
		int x = u;
		u = adj[u][0] == prev ? adj[u][1] : adj[u][0];
		prev = x;
	}

	std::cout << u << '\n';


}