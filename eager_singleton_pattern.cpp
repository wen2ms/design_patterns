#include <iostream>
using namespace std;

class TaskQueue {
  public:
    TaskQueue(const TaskQueue& other) = delete;
    TaskQueue& operator =(const TaskQueue& other) = delete;

    static TaskQueue* get_instance() {
        return task_queue_;
    }

    void foo() {
        cout << "This is a member function in TaskQueue" << endl;
    }

  private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& other) = default;
    // TaskQueue& operator =(const TaskQueue& other) = default;

    static TaskQueue* task_queue_;
};

TaskQueue* TaskQueue::task_queue_ = new TaskQueue;

int main() {
    TaskQueue* task_queue = TaskQueue::get_instance();

    task_queue->foo();

    return 0;
}