#include "test_scheduler.h"
#include <mesos/resources.hpp>
#include <stout/check.hpp>

using boost::lexical_cast;
using std::ostringstream;

void TestScheduler::resourceOffers(SchedulerDriver *driver, const vector<Offer> &offers) {
  for (const Offer &offer : offers) {
    static const Resources TASK_RESOURCES = Resources::parse(
        "cpus:" + stringify(CPUS_PER_TASK) + ";mem:" + stringify(MEM_PER_TASK)).get();

    Resources remaining = offer.resources();

    vector<TaskInfo> tasks;
    if (TASK_RESOURCES <= remaining.flatten()) {
      int taskId = 1;
      TaskInfo task;
      task.set_name("Task " + lexical_cast<string>(taskId));
      task.mutable_task_id()->set_value(lexical_cast<string>(taskId));
      task.mutable_slave_id()->MergeFrom(offer.slave_id());
      task.mutable_executor()->MergeFrom(executor);
      task.set_data(script);

      Option<Resources> resources = remaining.find(TASK_RESOURCES, role);
      CHECK_SOME(resources);
      task.mutable_resources()->MergeFrom(resources.get());

      tasks.push_back(task);
      driver->launchTasks(offer.id(), tasks);
      tasksLaunched++;

      break;
    }
  }

  if (tasksLaunched == 0) {
    driver->abort();
  }
}

void TestScheduler::statusUpdate(SchedulerDriver *driver, const TaskStatus &status) {
  if (status.state() == TASK_FINISHED) {
    cout << endl << status.data() << endl;
    driver->stop();
    return;
  }

  if (status.state() == TASK_LOST ||
      status.state() == TASK_KILLED ||
      status.state() == TASK_FAILED) {
    cout << "Aborting because task "
        << " is in unexpected state " << status.state()
        << " with message '" << status.message() << "'"
        << endl;
    driver->abort();
  }
}