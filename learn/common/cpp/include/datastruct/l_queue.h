/*  BEGIN_FILE_HDR
************************************************************************************************
*   File Name       : rte_img_queue.h
************************************************************************************************
*   END_FILE_HDR*/
#ifndef __RTE_IMG_QUEUE_H__
#define __RTE_IMG_QUEUE_H__

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class RteQueue
{
public:
    explicit RteQueue(int capacity = INT32_MAX) : m_capacity(capacity) {}

    template <typename... Args>
    void put(Args&&... args)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_cv.wait(lck, [this] { return m_queue.size() <= m_capacity; });
        m_queue.emplace(std::forward<Args>(args)...);
        lck.unlock();
        m_cv.notify_all();
    }

    bool get(T& t, int timeout = 0)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        if (timeout > 0)
        {
            m_cv.wait_for(lck, std::chrono::milliseconds(timeout), [this]
            {
                return !this->m_queue.empty();
            });
        }
        else
        {
            m_cv.wait(lck, [this]
            {
                return !m_queue.empty();
            });
        }

        if (m_queue.empty())
        {
            return false;
        }
        else
        {
            t = std::move(m_queue.front());
            m_queue.pop();
        }

        lck.unlock();
        m_cv.notify_all();
        return true;
    }

    void clear()
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        while (!m_queue.empty())
        {
            m_queue.pop();
        }
    }

private:
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    std::queue<T>           m_queue;
    int                     m_capacity;
};

#endif  // __RTE_IMG_QUEUE_H__
