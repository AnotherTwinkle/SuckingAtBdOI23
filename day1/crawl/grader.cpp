#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include "crawl.h"

namespace grader {
    const int QUERY_LIMIT = 120000, MAXN = 64, MAXM = 200;
    template<typename... Args>
    void waassert(bool b, std::string s="", Args... args) {
        if (b) return;
        fprintf(stderr, "Wrong Answer\n", args...);
        fprintf(stderr, s.c_str(), args...);
        fprintf(stderr, "\n", args...);
        exit(0);
    }

    template<typename... Args>
    void inputassert(bool b, std::string s="", Args... args) {
        if (b) return;
        fprintf(stderr, "Invalid Input\n", args...);
        fprintf(stderr, s.c_str(), args...);
        fprintf(stderr, "\n", args...);
        exit(0);
    }

    std::pair<int, int> other(Tunnel t, int u, int d) {
        if (u == t.room1 && d == t.door1) return {t.room2, t.door2};
        if (u == t.room2 && d == t.door2) return {t.room1, t.door1};
        return {-1, -1};
    }

    struct Graph {
        std::vector<std::vector<int>> adj;
        std::vector<Tunnel> edges;
        int s;
        Graph() {}

        Graph (int s, std::vector<int> doors, std::vector<Tunnel> tunnels) : adj(doors.size()), s(s) {
            int n = doors.size(), m = tunnels.size();
            if (!(0 <= s && s < n))     throw std::invalid_argument("Invalid starting room");

            int sum = 0;
            for (int i=0; i<n; i++) {
                if (!(0 <= doors[i] && doors[i] <= 2*m))    throw std::invalid_argument("Invalid number of doors");
                adj[i].assign(doors[i], -1);
                sum += doors[i];
            }

            if (sum != 2*m)    throw std::invalid_argument("Invalid number of doors");

            for (auto t: tunnels) {
                edges.push_back(t);
                int eid = edges.size()-1;

                int u = t.room1;
                int ud = t.door1;
                int v = t.room2;
                int vd = t.door2;

                if (!(0 <= u && u < n && 0 <= v && v < n && 0 <= ud && ud < adj[u].size() && 0 <= vd && vd < adj[v].size()))
                    throw std::invalid_argument("Invalid tunnel description");

                if (adj[u][ud] != -1 || adj[v][vd] != -1) {
                    throw std::invalid_argument("Door used for multiple tunnels");
                }

                adj[u][ud] = eid;
                adj[v][vd] = eid;
            }
        }
    };

    std::vector<bool> light;
    int cur;

    Graph input, output;
    void read_input() {

        std::vector<int> doors;
        std::vector<Tunnel> tunnels;
        int n, m, s;
        std::cin>>n>>m>>s;

        inputassert(1 <= n && n <= MAXN, "number of rooms out of bounds");
        inputassert(1 <= m && m <= MAXM, "number of tunnels out of bounds");

        doors.resize(n);
        light.resize(n);

        for (int i=0; i<n; i++)     std::cin>>doors[i];

        for (int i=0; i<n; i++) {
            int x;
            std::cin>>x;
            light[i] = x;
            inputassert(0 <= x && x <= 1, "Light must be 0 or 1");
        }

        for (int i=0; i<m; i++) {
            int u, ud, v, vd;
            std::cin>>u>>ud>>v>>vd;
            tunnels.push_back({u, ud, v, vd});
        }

        try {
            input = Graph(s, doors, tunnels);
        }
        catch(std::invalid_argument e) {
            inputassert(false, e.what());
        }

        cur = s;
    }

    int number_of_doors() {
        return input.adj[cur].size();
    }

    bool is_light_on() {
        return light[cur];
    }

    bool toggle_light() {
        return light[cur] = !light[cur];
    }

    int query_count = 0;
    int go_through_door(int door) {
        query_count++;
        waassert(query_count <= QUERY_LIMIT, "Exceeded query limit.");
        waassert(0 <= door && door < input.adj[cur].size(), "Invalid door number");
        Tunnel t = input.edges[input.adj[cur][door]];
        auto [v, d] = other(t, cur, door);
        cur = v;
        return d;
    }

    void finalize(Dungeon dungeon) {

        waassert(input.adj.size() == dungeon.doors.size(), "Incorrect number of rooms");
        waassert(input.edges.size() == dungeon.tunnels.size(), "Incorrect number of tunnels");

        try {
            output = Graph(dungeon.room, dungeon.doors, dungeon.tunnels);
        }
        catch(std::invalid_argument e) {
            waassert(false, e.what());
        }


        int n = input.adj.size();
        std::vector<int> mp(n, -1), rev(n, -1);

        auto equate = [&] (int u, int v) {
            if (mp[u] == -1 && rev[v] == -1) {
                mp[u] = v;
                rev[v] = u;
            }
            return mp[u] == v && rev[v] == u;
        };

        std::queue<int> q1, q2;
        waassert(equate(input.s, output.s), "Incorrect map");
        q1.push(input.s); q2.push(output.s);
        std::vector<bool> done(n);
        done[input.s] = 1;

        while (q1.size()) {
            int u1 = q1.front(); q1.pop();
            int u2 = q2.front(); q2.pop();

            waassert(input.adj[u1].size() == output.adj[u2].size());

            for (int i=0; i<(int)input.adj[u1].size(); i++) {
                int  e1 = input.adj[u1][i], e2 = output.adj[u2][i];
                auto [v1, d1] = other(input.edges[e1], u1, i);
                auto [v2, d2] = other(output.edges[e2], u2, i);

                waassert(equate(v1, v2), "Incorrect map");
                if (!done[v1]) {
                    q1.push(v1);
                    q2.push(v2);
                    done[v1] = true;
                }
            }
        }

        for (int i=0; i<n; i++) {
            waassert(mp[i] != -1 && rev[i] != -1, "Incorrect map");
        }
        fprintf(stderr, "Correct answer. q = %d\n", query_count);
    }
}




int number_of_doors() {
    return grader::number_of_doors();
}

bool is_light_on() {
    return grader::is_light_on();
}

bool toggle_light() {
    return grader::toggle_light();
}

int go_through_door(int door) {
    return grader::go_through_door(door);
}

int main(int argc, char **argv) {
  grader::read_input();
  grader::finalize(guess());
  return 0;
}
