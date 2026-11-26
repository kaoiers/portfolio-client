#pragma once
#include "AStar.h"
#include "../threading/ThreadPool.h"
#include <cstdint>
#include <future>
#include <utility>

struct AsyncPathResult
{
    std::uint64_t revision;
    PathResult path;
};

// No worker accesses a live map, game object or UI. Futures transfer values back to the caller.
class AsyncPathfinder
{
public:
    explicit AsyncPathfinder(std::size_t workers = 2) : m_pool(workers) {}

    std::future<AsyncPathResult> request(NavigationGrid snapshot, std::uint64_t revision,
        GridPoint start, GridPoint goal)
    {
        return m_pool.submit([grid = std::move(snapshot), revision, start, goal] {
            return AsyncPathResult{revision, AStar::find(grid, start, goal)};
        });
    }

private:
    ThreadPool m_pool;
};
