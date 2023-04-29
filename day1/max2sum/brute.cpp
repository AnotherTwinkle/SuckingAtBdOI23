#include <bits/stdc++.h>
#define ll long long
#define pair std::array<int, 2>

constexpr long long MOD = 998244353 ;

ll mod(ll a) {
	if (a >= 0 && a < MOD) return a;
	else if (a >= MOD) {
		return a % MOD;
	} else {
		return  MOD + (a % MOD);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// std::cout << mod(-2) << ' ' << mod(3) << ' ' << mod(4) << '\n';
	int n, q;
	std::cin >> n >> q;

	if (n > 5000) {
		std::cout << "NOPE\n";
		return;
	}


	std::vector<ll> v(n);
	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
		// v[i] %= MOD;
		// v[i] = v[i] < 0 ? MOD - v[i] : v[i];
	}

	while (q--) {
		int t; std::cin >> t;
		if (t == 0) {
			int l, r; std::cin >> l >> r; l--, r--;

			std::vector<ll> pmax; pmax.push_back(v[l]);
			for (int i = l + 1; i <= r; i++) {
				pmax.push_back(std::max(pmax.back(), v[i]));
			}

			std::vector<ll> smax; smax.push_back(v[r]);
			for (int i = r - 1; i >= l; i--) {
				smax.push_back(std::max(smax.back(), v[i]));
			}

			std::reverse(smax.begin(), smax.end());

			ll ans = 0;
			for (int i = 0; i < pmax.size(); i++) {
				ans += mod(mod(pmax[i]) * mod(smax[i]));
			}
			std::cout << mod(ans) << '\n';
		} else {
			int l, r, k;
			std::cin >> l >> r >> k; l--, r--;
			for (int i = l; i <= r; i++) {
				v[i] += k;
			}
		}
	}
}