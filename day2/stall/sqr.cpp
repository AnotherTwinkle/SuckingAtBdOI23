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

	std::vector<int> v;
	v.push_back(u);
	if (adj[u].size()) {
		int prev = u;
		u = adj[u][0];
		v.push_back(u);
		while (adj[u].size() > 1) {
			int x = u;
			u = adj[u][0] == prev ? adj[u][1] : adj[u][0];
			prev = x;
			v.push_back(u);
		}
	}

	std::vector<ll> psum(n); psum[0] = v[0];
	for (int i = 1; i < n; i++) {
		psum[i] = psum[i - 1] + v[i];
	}

	for (int i = 0; i < n; i++) {
		ll min = 1e18;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;

			ll l = ((i ? psum[i - 1] : 0) * i);
			ll r = (psum.back() - psum[j]) * j;
			ll ml = psum(r - l - 1) / 2
		}
	}


}