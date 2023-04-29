#include <bits/stdc++.h>
#define ll long long
#define pair std::array<int, 2>

constexpr long long MOD = 998244353 ;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// std::cout << mod(-2) << ' ' << mod(3) << ' ' << mod(4) << '\n';
	int n, q;
	std::cin >> n >> q;

	std::vector<int> two;
	std::vector<ll> v(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
		if (v[i] == 2) two.push_back(i);
	}

	while (q--) {
		int t; std::cin >> t;
		if (t == 0) {
			ll l, r; std::cin >> l >> r; l--, r--;

			// Find first 2 in range [l, r]
			auto first = std::lower_bound(two.begin(), two.end(), l);
			if (first == two.end() || *first > r || two.size() == 0) {
				// Everything in pmax and smax is one.
				std::cout << (r - l + 1) % MOD << '\n';
				continue;
			}
			// std::cout << *first << '\n';

			// Now there must also exist a last occurence of two
			auto last = std::upper_bound(two.begin(), two.end(), r); last--;

			// Now everything is 2 from [first, r]
			// Everything is  2 from [l, last]
			// std::cout << *first << ' ' << *last << '\n';
			// std::cout << *first - l + 1 << ' ' << *last - *first + 1 << ' ' << r - *last + 1 << '\n';
			std::cout << ((long long) 2 * (*first - l + 1) + 4 * (*last - *first + 1) + 2 * (r - *last - 1)) % MOD << '\n';
			


		} else {
			int l, r, k;
			std::cin >> l >> r >> k; l--, r--;
			for (int i = l; i <= r; i++) {
				v[i] += k;
			}
		}
	}
}