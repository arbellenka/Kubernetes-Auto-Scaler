#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 7846
// Hash 4844
// Hash 1750
// Hash 9088
// Hash 7268
// Hash 9575
// Hash 5048
// Hash 5791
// Hash 9022
// Hash 4301
// Hash 4411
// Hash 9594
// Hash 9656
// Hash 4758
// Hash 5853
// Hash 7985
// Hash 4350
// Hash 6279
// Hash 1102
// Hash 3772
// Hash 7947
// Hash 2858
// Hash 9030
// Hash 9698
// Hash 4519
// Hash 7837
// Hash 5204
// Hash 7171
// Hash 3243
// Hash 5598
// Hash 7843
// Hash 1771
// Hash 7726
// Hash 2318
// Hash 7920
// Hash 2434
// Hash 9372
// Hash 9336
// Hash 2105
// Hash 2763
// Hash 4077
// Hash 2085
// Hash 1864
// Hash 7912
// Hash 1406
// Hash 7725
// Hash 1790
// Hash 6593
// Hash 3958
// Hash 9337
// Hash 5796
// Hash 6058
// Hash 7799
// Hash 4163
// Hash 1426
// Hash 9627
// Hash 4248
// Hash 8673
// Hash 7792
// Hash 3454
// Hash 8486
// Hash 5362
// Hash 7883
// Hash 8676
// Hash 3403
// Hash 2477
// Hash 5234
// Hash 4472
// Hash 8105
// Hash 1756
// Hash 2165
// Hash 6401
// Hash 2018
// Hash 4725
// Hash 6065
// Hash 5294