#include <iostream>
#include <mutex>
using namespace std;

class TaskQueue {
  public:
    TaskQueue(const TaskQueue& other) = delete;
    TaskQueue& operator =(const TaskQueue& other) = delete;

    // Lazy Initialization is not thread-safe
    static TaskQueue* get_instance() {
        if (task_queue_ == nullptr) {
            mutex_.lock();

            if (task_queue_ == nullptr) {
                task_queue_ = new TaskQueue;
            }
            
            mutex_.unlock();
        }

        return task_queue_;
    }

    void foo() {
        cout << "This is a member function in TaskQueue" << endl;
    }

  private:
    TaskQueue() = default;

    static TaskQueue* task_queue_;
    static mutex mutex_;
};

TaskQueue* TaskQueue::task_queue_ = nullptr;
mutex TaskQueue::mutex_;

int main() {
    TaskQueue* task_queue = TaskQueue::get_instance();

    task_queue->foo();

    return 0;
}