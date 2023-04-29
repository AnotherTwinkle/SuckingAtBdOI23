#include <bits/stdc++.h>
#define ll long long
#define pair std::array<int, 2>

int main() {
	int n;
	std::cin >> n;

	std::vector<int> v(n); int ans = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> v[i];
	}

	for (int i = 0; i < n; i++) {
		if (v[i]) ans++, i++;
	}

	std::cout << ans << '\n';
	
}