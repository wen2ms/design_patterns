#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class TaskQueue {
  public:
    TaskQueue(const TaskQueue& other) = delete;
    TaskQueue& operator=(const TaskQueue& other) = delete;

    static TaskQueue* get_instance() {
        return task_queue_;
    }

    void foo() {
        std::cout << "This is a member function in TaskQueue" << std::endl;
    }

    bool is_empty() {
        std::lock_guard<std::mutex> locker(mutex_);

        return data_.empty();
    }

    void add_task(int node) {
        std::lock_guard<std::mutex> locker(mutex_);

        data_.push(node);
    }

    bool pop_task() {
        std::lock_guard<std::mutex> locker(mutex_);

        if (data_.empty()) {
            return false;
        }

        data_.pop();
        return true;
    }

    int take_task() {
        std::lock_guard<std::mutex> locker(mutex_);

        if (data_.empty()) {
            return -1;
        }

        return data_.front();
    }

  private:
    TaskQueue() = default;

    static TaskQueue* task_queue_;
    std::queue<int> data_;
    std::mutex mutex_;
};

TaskQueue* TaskQueue::task_queue_ = new TaskQueue;

int main() {
    TaskQueue* task_queue = TaskQueue::get_instance();

    std::thread producer([=]() {
        for (int i = 0; i < 10; ++i) {
            task_queue->add_task(i + 100);
            std::cout << "+++ add task: " << i + 100 << ", thread id: " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    std::thread consumer([=]() {
        while (!task_queue->is_empty()) {
            int number = task_queue->take_task();
            std::cout << "--- take task: " << number << ", thread id: " << std::this_thread::get_id() << std::endl;
            task_queue->pop_task();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    producer.join();
    consumer.join();

    return 0;
}