#pragma once
#include "NavigationGrid.h"
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <queue>
#include <vector>

enum class PathStatus { Found, Unreachable, InvalidEndpoint };

struct PathResult
{
    PathStatus status = PathStatus::InvalidEndpoint;
    std::vector<GridPoint> points; // Includes both start and goal when found.
};

class AStar
{
public:
    static PathResult find(const NavigationGrid& grid, GridPoint start, GridPoint goal)
    {
        if (!grid.walkable(start) || !grid.walkable(goal))
            return {PathStatus::InvalidEndpoint, {}};

        struct OpenEntry { int index, cost, heuristic; };
        struct Compare
        {
            bool operator()(const OpenEntry& lhs, const OpenEntry& rhs) const
            {
                const auto lhs_score = lhs.cost + lhs.heuristic;
                const auto rhs_score = rhs.cost + rhs.heuristic;
                if (lhs_score != rhs_score) return lhs_score > rhs_score;
                if (lhs.heuristic != rhs.heuristic) return lhs.heuristic > rhs.heuristic;
                return lhs.index > rhs.index;
            }
        };
        const auto heuristic = [goal](GridPoint point) {
            return std::abs(point.x - goal.x) + std::abs(point.y - goal.y);
        };

        std::vector<int> cost(grid.size(), (std::numeric_limits<int>::max)());
        std::vector<int> parent(grid.size(), -1);
        std::priority_queue<OpenEntry, std::vector<OpenEntry>, Compare> open;
        const int first = grid.index(start), last = grid.index(goal);
        cost[first] = 0;
        open.push({first, 0, heuristic(start)});
        constexpr GridPoint directions[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        while (!open.empty())
        {
            const auto current = open.top();
            open.pop();
            if (current.cost != cost[current.index]) continue;
            if (current.index == last)
            {
                std::vector<GridPoint> points;
                for (int index = last; index != -1; index = parent[index])
                    points.push_back(grid.point(index));
                std::reverse(points.begin(), points.end());
                return {PathStatus::Found, std::move(points)};
            }
            const auto point = grid.point(current.index);
            for (const auto direction : directions)
            {
                const GridPoint next{point.x + direction.x, point.y + direction.y};
                if (!grid.walkable(next)) continue;
                const int index = grid.index(next);
                const int next_cost = current.cost + 1;
                if (next_cost >= cost[index]) continue;
                cost[index] = next_cost;
                parent[index] = current.index;
                open.push({index, next_cost, heuristic(next)});
            }
        }
        return {PathStatus::Unreachable, {}};
    }
};
