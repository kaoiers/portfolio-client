#pragma once
#include "AStar.h"
#include "../threading/ThreadPool.h"
#include <cstdint>
#include <future>
#include <utility>

/// 탐색에 사용한 맵 revision과 결과를 함께 반환한다.
struct AsyncPathResult
{
    std::uint64_t revision;
    PathResult path;
};

// No worker accesses a live map, game object or UI. Futures transfer values back to the caller.
/// 스레드 풀에서 독립적인 맵 스냅샷을 탐색하고 future로 결과를 전달한다.
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
