#pragma once
#include <memory>
#include <queue>
#include <tuple>
#include <cstdio>

class IPending {
public:
    virtual void run() = 0;
    virtual ~IPending() = default;
};

template<typename Callable, typename... Args>
class Pending : public IPending {
private:
    Callable _callable;
    std::tuple<Args...> _args;

public:
    Pending(Callable callable, Args... args)
        : _callable(callable)
        , _args(std::make_tuple(args...)) {}

    void run() override {
        std::apply(_callable, _args);
    }
};

// Очередь отложенных вызовов
class PendingQueue : public std::queue<std::unique_ptr<IPending>> {
public:
    ~PendingQueue() {
        printf("%zu pending items dropped\n", this->size());
    }

    template<typename Callable, typename... ArgTypes>
    void enqueue(Callable callable, ArgTypes... args) {
        using PendingType = Pending<Callable, ArgTypes...>;
        this->emplace(std::make_unique<PendingType>(callable, args...));
    }

    void run_one() {
        if (this->empty())
            return;
        this->front()->run();
        this->pop();
    }

    void run_all() {
        while (!this->empty())
            run_one();
    }
};
