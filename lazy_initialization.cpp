#include <iostream>
using namespace std;

class TaskQueue {
  public:
    TaskQueue(const TaskQueue& other) = delete;
    TaskQueue& operator =(const TaskQueue& other) = delete;

    // Lazy Initialization is not thread-safe
    static TaskQueue* get_instance() {
        if (task_queue_ == nullptr) {
            task_queue_ = new TaskQueue;
        }

        return task_queue_;
    }

    void foo() {
        cout << "This is a member function in TaskQueue" << endl;
    }

  private:
    TaskQueue() = default;

    static TaskQueue* task_queue_;
};

TaskQueue* TaskQueue::task_queue_ = nullptr;

int main() {
    TaskQueue* task_queue = TaskQueue::get_instance();

    task_queue->foo();

    return 0;
}