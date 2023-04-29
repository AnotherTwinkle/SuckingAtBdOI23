#include <bits/stdc++.h>
#define ll long long
#define pair std::array<int, 2>

constexpr long long MOD = 998244233;


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

	ll n, q;
	std::cin >> n >> q;

	std::vector<ll> v(n);
	for (ll& i : v) std::cin >> i;

	std::vector<ll> psum(n);
	psum[0] = v[0];
	for (int i = 1; i < n; i++) {
		psum[i] = psum[i - 1] + v[i];
	}

	while (q--) {
		int x;
		std::cin >> x;

		ll l, r;
		std::cin >> l >> r; l--, r--;
		// std::cout << (psum[r] - (l ? psum[l - 1] : 0)) << '\n';
		// std::cout << (((psum[r] % MOD) - ((l ? psum[l - 1] : 0) % MOD) % MOD) * (v[r] % MOD)) % MOD << '\n';	
		ll w = mod(mod(psum[r] - (l ? psum[l - 1] : 0)));
		// w = (w < 0 ? MOD - w : w);

		ll y = mod(v[r]);
		//y = (y < 0 ? MOD - y : y);
		// std::cout << w << ' ' << y << '\n';

		std::cout << mod((w * y)) << '\n';		
		// std::cout << ((psum[r] - (l ? psum[l - 1] : 0)) % MOD) * (v[r] % MOD) % MOD << '\n';
	}
}