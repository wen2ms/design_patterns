#include <atomic>
#include <iostream>
#include <mutex>
using namespace std;

class TaskQueue {
  public:
    TaskQueue(const TaskQueue& other) = delete;
    TaskQueue& operator=(const TaskQueue& other) = delete;

    // Lazy Initialization is not thread-safe
    // Must use atmoic to ensure thread-safe
    static TaskQueue* get_instance() {
        TaskQueue* queue = task_queue_.load();

        if (queue == nullptr) {
            mutex_.lock();
            queue = task_queue_.load();
            if (queue == nullptr) {
                queue = new TaskQueue;
                task_queue_.store(queue);
            }

            mutex_.unlock();
        }

        return queue;
    }

    void foo() {
        cout << "This is a member function in TaskQueue" << endl;
    }

  private:
    TaskQueue() = default;

    static atomic<TaskQueue*> task_queue_;
    static mutex mutex_;
};

atomic<TaskQueue*> TaskQueue::task_queue_;
mutex TaskQueue::mutex_;

int main() {
    TaskQueue* task_queue = TaskQueue::get_instance();

    task_queue->foo();

    return 0;
}