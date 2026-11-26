#include "../game/threading/ThreadPool.h"
#include <atomic>
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        std::atomic<int> count{0};
        std::future<int> final;
        {
            ThreadPool pool(2);
            std::vector<std::future<int>> results;
            for (int i = 0; i < 100; ++i)
                results.push_back(pool.submit([i, &count] { ++count; return i * i; }));
            for (int i = 0; i < 100; ++i)
                if (results[i].get() != i * i) throw std::runtime_error("wrong task result");
            auto failure = pool.submit([]() -> int { throw std::runtime_error("task failure"); });
            bool propagated = false;
            try { failure.get(); } catch (const std::runtime_error&) { propagated = true; }
            if (!propagated) throw std::runtime_error("exception not propagated");
            final = pool.submit([value = std::make_unique<int>(7), &count] { ++count; return *value; });
        }
        if (final.get() != 7 || count != 101) throw std::runtime_error("pool did not drain");
        bool rejected = false;
        try { ThreadPool invalid(0); } catch (const std::invalid_argument&) { rejected = true; }
        if (!rejected) throw std::runtime_error("zero workers accepted");
        std::cout << "Thread pool tests passed\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
