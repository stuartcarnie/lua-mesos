#include <mesos/scheduler.hpp>
#include "task_executor.h"

using namespace mesos;

int main(int argc, char *argv[]) {
  TaskExecutor executor;
  MesosExecutorDriver driver(&executor);
  return driver.run() == DRIVER_STOPPED ? 0 : 1;
}
