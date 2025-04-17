#include <iostream>

class TaskQueue {
  public:
    static TaskQueue* get_instance() {
        // Must be c++11 or later
        static TaskQueue task_queue;

        return &task_queue;
    }

  void foo() {
    std::cout << "This is a member function in TaskQueue" << std::endl;
  }

  private:
    TaskQueue() = default;
    TaskQueue(const TaskQueue& other) = default;
    TaskQueue& operator =(const TaskQueue& other) = default;
};

int main() {
    TaskQueue* task_queue = TaskQueue::get_instance();

    task_queue->foo();

    return 0;
}