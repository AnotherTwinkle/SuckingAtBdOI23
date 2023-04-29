#include <vector>
#include <string>

int number_of_doors();
bool is_light_on();
bool toggle_light();
int go_through_door(int door);


struct Tunnel {
    int room1, door1, room2, door2;
};

struct Dungeon {
    int room;
    std::vector<int> doors;
    std::vector<Tunnel> tunnels;
};

Dungeon guess();

