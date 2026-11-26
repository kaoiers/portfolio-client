#pragma once
#include <cstdint>
#include <stdexcept>
#include <vector>

/// 타일 그리드의 정수 좌표를 표현하는 값 타입이다.
struct GridPoint
{
    int x = 0;
    int y = 0;
    bool operator==(const GridPoint& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const GridPoint& rhs) const { return !(*this == rhs); }
};

// A value-type snapshot; worker threads read their own immutable copy.
/// 타일의 유효 범위와 장애물 상태를 보관하는 복사 가능한 탐색 데이터이다.
class NavigationGrid
{
public:
    static constexpr std::size_t MAX_CELLS = 16 * 1024 * 1024;

    NavigationGrid() = default;
    NavigationGrid(int width, int height)
    {
        if (width <= 0 || height <= 0 ||
            static_cast<std::uint64_t>(width) * height > MAX_CELLS)
            throw std::invalid_argument("invalid navigation grid size");
        m_width = width;
        m_height = height;
        m_blocked.resize(static_cast<std::size_t>(width) * height, 0);
    }

    int width() const { return m_width; }
    int height() const { return m_height; }
    std::size_t size() const { return m_blocked.size(); }
    bool contains(GridPoint point) const
    {
        return point.x >= 0 && point.y >= 0 && point.x < m_width && point.y < m_height;
    }
    int index(GridPoint point) const { return point.y * m_width + point.x; }
    GridPoint point(int index) const { return {index % m_width, index / m_width}; }
    bool walkable(GridPoint point) const { return contains(point) && !m_blocked[index(point)]; }
    bool setBlocked(GridPoint point, bool blocked)
    {
        if (!contains(point)) return false;
        m_blocked[index(point)] = blocked ? 1 : 0;
        return true;
    }

private:
    int m_width = 0;
    int m_height = 0;
    std::vector<std::uint8_t> m_blocked;
};
