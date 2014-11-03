#include <cstdio>
#include <string>
#include <iostream>
#include <csignal>

#include <mesos/resources.hpp>

#include <stout/flags.hpp>
#include "flags.h"
#include "test_scheduler.h"

using std::string;
using std::cerr;
using std::endl;

using namespace mesos;
using mesos::Resources;

void usage(const char *argv0, const flags::FlagsBase &flags) {
  cerr << "Usage: " << os::basename(argv0).get() << " [...]" << endl
      << endl
      << "Supported options:" << endl
      << flags.usage();
}

int main(int argc, char *argv[]) {

  // Find this executable's directory to locate executor.
  string path = os::realpath(dirname(argv[0])).get();
  string uri = path + "/mesolua-executor";

  Flags f;

  Try<Nothing> load = f.load(None(), argc, argv);
  if (load.isError()) {
    cerr << load.error() << endl;
    usage(argv[0], f);
    return 1;
  }

  if (f.master.isNone()) {
    cerr << "missing --master" << endl;
    usage(argv[0], f);
    return 1;
  }

  if (f.script.isNone() && f.scriptFile.isNone()) {
    cerr << "either --script or -e is required";
    usage(argv[0], f);
    return 1;
  }

  string script;
  if (f.script.isSome()) {
    script = f.script.get();
  } else if (f.scriptFile.isSome()) {
    auto data = os::read(f.scriptFile.get());
    if (data.isError()) {
      cerr << "error reading script file '" << f.scriptFile.get() << "'; "
          << data.get()
          << endl;

      return 1;
    }

    script = data.get();
  }

  ExecutorInfo e;
  e.mutable_executor_id()->set_value("default");
  e.mutable_command()->set_value(uri);
  e.set_name("Test Executor (Lua)");
  e.set_source("lua_test");

  FrameworkInfo fi;
  fi.set_user("");
  fi.set_name("Test Framework (Lua)");
  fi.set_role(f.role);
  fi.set_principal("test-framework-lua");

  TestScheduler scheduler(e, f.role, script);
  MesosSchedulerDriver *driver = new MesosSchedulerDriver(&scheduler, fi, f.master.get());
  int status = driver->run() == DRIVER_STOPPED ? 0 : 1;
  delete driver;

  return status;
}
