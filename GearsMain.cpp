#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <memory>

enum class Rotation {	// same as last gear or opposite
    not_moving,
    same,
    opposite
};

struct Gear {

    int x, y;
    int r;
    Rotation rotation;
    int speed;

    Gear(int x, int y, int r) : x(x), y(y), r(r), rotation(Rotation::not_moving),
                                speed(0) {}

    bool operator==(Gear& other) {
        return this->x == other.x && this->y == other.y && this->r == other.r;
    }

    bool operator!=(Gear& other) {
        return !operator==(other);
    }

};

bool isTouching(Gear left, Gear right) {
    if (left == right)
        return false;

    return std::pow(left.r + right.r, 2) 
            == std::pow(left.x - right.x, 2) 
                + std::pow(left.y - right.y, 2);
}

int main()
{
    std::vector<Gear> gears;
    int N;
    std::cin >> N; std::cin.ignore();
    for (int i = 0; i < N; i++) {
        int x;
        int y;
        int r;
        std::cin >> x >> y >> r; std::cin.ignore();

        gears.emplace_back(x, y, r);
    }

    std::queue<std::shared_ptr<Gear>> queue;

    gears.back().rotation = Rotation::same;
    gears.back().speed = 36; // to change, may be...

    queue.push(std::make_shared<Gear>(gears.back()));

    while (!queue.empty()) {
        auto lastGear = queue.front();
        queue.pop();

        for (auto& g : gears) {
  
            if (isTouching(*lastGear, g)) {

              // exits from a loop in graph or/and
              // every connected gear has been checked...
                if (g.rotation != Rotation::not_moving) {
                    if (g.rotation == lastGear->rotation || g.speed != lastGear->speed) { // jammed...
                        std::cout << "NOT MOVING" << std::endl;
                        return 0;
                    }
                    else continue;
                }

                if (lastGear->rotation == Rotation::same)
                    g.rotation = Rotation::opposite;
                else
                    g.rotation = Rotation::same;

                g.speed = lastGear->speed * lastGear->r / g.r;

                queue.push(std::make_shared<Gear>(g));
            }
        }
    }

    if (gears.front().rotation == Rotation::not_moving)
        std::cout << "NOT MOVING" << std::endl;
    else if (gears.front().rotation == Rotation::same)
        std::cout << "CW" << std::endl;
    else
        std::cout << "CCW" << std::endl;

    return 0;
}
/*
9
0 0 1
0 12 3
0 6 1
0 16 1
0 8 1
3 16 2
0 4 1
0 2 1
2 0 1
*/