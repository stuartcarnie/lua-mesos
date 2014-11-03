#ifndef TASK_EXECUTOR_H
#define TASK_EXECUTOR_H

#include <string>

#include <mesos/executor.hpp>

using namespace mesos;
using std::string;

class TaskExecutor : public Executor {
public:
  virtual ~TaskExecutor() {
  }

  virtual void registered(ExecutorDriver *driver,
      const ExecutorInfo &executorInfo,
      const FrameworkInfo &frameworkInfo,
      const SlaveInfo &slaveInfo) {
  }

  virtual void reregistered(ExecutorDriver *driver,
      const SlaveInfo &slaveInfo) {

  }

  virtual void disconnected(ExecutorDriver *driver) {
  }

  virtual void launchTask(ExecutorDriver *driver, const TaskInfo &task);

  virtual void killTask(ExecutorDriver *driver, const TaskID &taskId) {
  }

  virtual void frameworkMessage(ExecutorDriver *driver, const string &data) {
  }

  virtual void shutdown(ExecutorDriver *driver) {
  }

  virtual void error(ExecutorDriver *driver, const string &message) {
  }
};

#endif