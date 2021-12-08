#ifndef NETCLIENT_NET_TSQUEUE_H
#define NETCLIENT_NET_TSQUEUE_H

#include "net_common.h"

namespace olc {
    namespace net {

        template<typename T>
        class Tsqueue{
        public:
            Tsqueue() = default;
            Tsqueue(const Tsqueue<T>&) = delete;
            virtual ~Tsqueue(){ clear(); }

        public:
            // Returns and maintains item at front of Queue
            const T& front(){
                std::scoped_lock lock(muxQueue);
                return deqQueue.front();
            }

            // Returns and maintains item at back of Queue
            const T& back(){
                std::scoped_lock lock(muxQueue);
                return deqQueue.back();
            }

            // Adds an item to back of Queue
            void push_back(const T& item){
                std::scoped_lock lock(muxQueue);
                deqQueue.template emplace_back(std::move(item));
            }

            // Adds an item to front of Queue
            void push_front(const T& item){
                std::scoped_lock lock(muxQueue);
                deqQueue.template emplace_front(std::move(item));
            }

            // Returns number of items in Queue
            size_t count(){
                std::scoped_lock lock(muxQueue);
                return deqQueue.size();
            }

            // Clears Queue
            void clear(){
                std::scoped_lock lock(muxQueue);
                deqQueue.clear();
            }

            // Remove and returns item from front of Queue
            T pop_front(){
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deqQueue.front());
                deqQueue.pop_front();
                return t;
            }

            // Remove and returns item from back of Queue
            T pop_back(){
                std::scoped_lock lock(muxQueue);
                auto t = std::move(deqQueue.back());
                deqQueue.pop_back();
                return t;
            }

        protected:
            std::mutex muxQueue;
            std::deque<T> deqQueue;
        };

    }
}

#endif //NETCLIENT_NET_TSQUEUE_H
