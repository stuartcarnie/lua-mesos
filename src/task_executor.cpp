#include "task_executor.h"
#include "lua_runner.h"

void TaskExecutor::launchTask(ExecutorDriver *driver, const TaskInfo &task) {
  TaskStatus status;
  status.mutable_task_id()->MergeFrom(task.task_id());
  status.set_state(TASK_RUNNING);

  driver->sendStatusUpdate(status);

  auto res = run(task.data());
  status.mutable_task_id()->MergeFrom(task.task_id());
  switch (std::get<1>(res)) {
    case 0:
      status.set_data(std::get<0>(res));
      status.set_state(TASK_FINISHED);
      break;

    case 1:
      status.set_message(std::get<0>(res));
      status.set_state(TASK_FAILED);
      break;
  }

  driver->sendStatusUpdate(status);
}
