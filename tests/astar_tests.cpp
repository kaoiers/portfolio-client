#include "../game/navigation/AStar.h"
#include <iostream>
#include <stdexcept>

namespace
{
void require(bool condition, const char* message)
{
    if (!condition) throw std::runtime_error(message);
}
}

int main()
{
    try
    {
        NavigationGrid grid(5, 5);
        for (int y = 0; y < 4; ++y)
            grid.setBlocked({2, y}, true);
        auto result = AStar::find(grid, {0, 0}, {4, 0});
        require(result.status == PathStatus::Found && result.points.size() == 13, "shortest detour");
        require(result.points.front() == GridPoint{0, 0} && result.points.back() == GridPoint{4, 0}, "path endpoints");
        for (std::size_t i = 1; i < result.points.size(); ++i)
        {
            const auto a = result.points[i - 1], b = result.points[i];
            require(grid.walkable(b) && std::abs(a.x - b.x) + std::abs(a.y - b.y) == 1, "valid adjacent step");
        }
        require(AStar::find(grid, {0, 0}, {0, 0}).points.size() == 1, "start equals goal");
        require(AStar::find(grid, {-1, 0}, {4, 0}).status == PathStatus::InvalidEndpoint, "invalid start");
        require(AStar::find(grid, {0, 0}, {2, 0}).status == PathStatus::InvalidEndpoint, "blocked goal");
        grid.setBlocked({2, 4}, true);
        require(AStar::find(grid, {0, 0}, {4, 0}).status == PathStatus::Unreachable, "disconnected grid");
        require(!grid.setBlocked({5, 5}, true), "invalid tile rejected");
        std::cout << "A* tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
