/*  BEGIN_FILE_HDR
************************************************************************************************
*   File Name       : rte_img_pool.h
************************************************************************************************
*   END_FILE_HDR*/
#ifndef __RTE_IMG_POOL_H__
#define __RTE_IMG_POOL_H__

#include <condition_variable>
#include <mutex>
#include <queue>
#include <list>
#include <memory>
#include <utility>

template <typename T>
class RtePool
{
public:
    template <typename... Args>
    static std::shared_ptr<RtePool<T>> create(int max_alloc_cnt, Args&&... args)
    {
        auto *pool = new RtePool<T>();
        pool->init(max_alloc_cnt, std::forward<Args>(args)...);
        return std::shared_ptr<RtePool<T>>(pool);
    }

    ~RtePool()
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        for (auto *item : m_items)
        {
            delete item;
            item = nullptr;
        }
        m_items.clear();

        while (!m_free_list.empty())
        {
            m_free_list.pop();
        }
    }

    T* get()
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        if (m_free_list.empty())
        {
            return nullptr;
        }

        T *item = m_free_list.front();
        m_free_list.pop();

        return item;
    }

    T* get(int timeout)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        if (timeout > 0)
        {
            m_cv.wait_for(lck, std::chrono::milliseconds(timeout), [this]
            {
                return !this->m_free_list.empty();
            });
        }
        else
        {
            m_cv.wait(lck, [this] { return !this->m_free_list.empty(); });
        }

        if (m_free_list.empty())
        {
            return nullptr;
        }

        T *item = m_free_list.front();
        m_free_list.pop();

        return item;
    }

    std::shared_ptr<T> get_shared_ptr(bool auto_release)
    {
        return wrap_item(get(), auto_release);
    }

    std::shared_ptr<T> get_shared_ptr(int timeout, bool auto_release)
    {
        return wrap_item(get(timeout), auto_release);
    }

    void release(T *item)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_free_list.emplace(item);
        lck.unlock();
        m_cv.notify_all();
    }

private:
    template <typename... Args>
    void init(int max_alloc_cnt, Args&&... args)
    {
        m_max_alloc_cnt = max_alloc_cnt <= 0 ? INT32_MAX : max_alloc_cnt;
        for (int i = 0; i < m_max_alloc_cnt; i++)
        {
            alloc_item(std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    void alloc_item(Args&&... args)
    {
        T *item = new T(std::forward<Args>(args)...);
        m_items.emplace_back(item);
        m_free_list.emplace(item);
    }

    std::shared_ptr<T> wrap_item(T *item, bool auto_release)
    {
        if (!item)
        {
            return nullptr;
        }

        if (auto_release)
        {
            return std::shared_ptr<T>(item, [this](T *item) { this->release(item); });
        }
        else
        {
            return std::shared_ptr<T>(item, [](T *item) {});
        }
    }

private:
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    std::list<T*>           m_items;
    std::queue<T*>          m_free_list;
    int                     m_max_alloc_cnt = 0;
};

#endif  // __RTE_IMG_POOL_H__
