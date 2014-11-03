#ifndef TEST_SCHEDULER_H
#define TEST_SCHEDULER_H

#include <string>
#include <mesos/scheduler.hpp>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using namespace mesos;

const int32_t CPUS_PER_TASK = 1;
const int32_t MEM_PER_TASK = 32;

class TestScheduler : public mesos::Scheduler {
public:
  TestScheduler(const ExecutorInfo &executor, string &role, string &script)
      : executor(executor),
        role(role),
        script(script),
        tasksLaunched(0) {
  }

  virtual ~TestScheduler() {
  }

  virtual void registered(SchedulerDriver *, const FrameworkID &, const MasterInfo &) override {
  }

  virtual void reregistered(SchedulerDriver *, const MasterInfo &masterInfo) {
  }

  virtual void disconnected(SchedulerDriver *driver) {
  }

  virtual void resourceOffers(SchedulerDriver *driver, const vector<Offer> &offers);

  virtual void offerRescinded(SchedulerDriver *driver,
      const OfferID &offerId) {
  }

  virtual void statusUpdate(SchedulerDriver *driver, const TaskStatus &status);

  virtual void frameworkMessage(SchedulerDriver *driver,
      const ExecutorID &executorId,
      const SlaveID &slaveId,
      const string &data) {
  }

  virtual void slaveLost(SchedulerDriver *driver, const SlaveID &sid) {
  }

  virtual void executorLost(SchedulerDriver *driver,
      const ExecutorID &executorID,
      const SlaveID &slaveID,
      int status) {
  }

  virtual void error(SchedulerDriver *driver, const string &message) {
    cout << message << endl;
  }


private:
  const ExecutorInfo executor;
  string role;
  string script;
  int tasksLaunched;
};

#endif