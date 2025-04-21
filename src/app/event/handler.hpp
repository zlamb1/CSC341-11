#pragma once

#include <functional>
#include <memory>

template <typename T> class EventHandler {
    public:
        EventHandler<T>(std::function<void(T &)> handler)
            : m_Handler(handler) {}

        void onEvent(T &event) {
            m_Handler(event);
        }

    protected:
        std::function<void(T &)> m_Handler;

    private:
};

template <typename T> using HandlerRef = std::shared_ptr<EventHandler<T>>;

template <typename T, typename... Args>
constexpr HandlerRef<T> CreateHandler(Args &&...args) {
    return std::make_shared<EventHandler<T>>(std::forward<Args>(args)...);
}

template <typename T> using WeakHandlerRef = std::weak_ptr<EventHandler<T>>;

template <typename T> using HandlerList = std::vector<WeakHandlerRef<T>>;