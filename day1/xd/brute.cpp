#include <bits/stdc++.h>
#define ll long long
#define pair std::array<int, 2>

int main() {
	int n;
	std::cin >> n;

	std::vector<ll> v(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
	}


	ll max = 0;
	for (ll i = 0; i < (1 << (n + 1)); i++) {
		ll tot = 0;
		std::vector<int> ind;
		// std::cout << "i " << i << '\n';
		for (int j = 0; (1 << j) <= i; j++) {
			// std::cout << "j " << j << '\n';
			if (i & (1 << j)) ind.push_back(j);
		}
		
		for (int k = 0; k < ind.size(); k++) {
			int l = k ? ind[k - 1] + 1 : 0;
			int r = ind[k] - 1;

			ll ans = 0;
			for (int m = l; m <= r; m++) ans ^= v[m];
			tot += ans;
		}

		max = std::max(tot, max);
	}

	std::cout << max << '\n';
	
}