#ifndef FLAGS_H
#define FLAGS_H

#include <stout/flags.hpp>
#include <string>

using flags::FlagsBase;

class Flags : public virtual FlagsBase {
public:
  Flags() {
    add(&role, "role", "role to use", "*");
    add(&master, "master", "ip:port of master");
    add(&scriptFile, "file", "file to execute");
    add(&script, "e", "inline script to run");
  }

  std::string role;
  Option<std::string> master;
  Option<std::string> scriptFile;
  Option<std::string> script;
};
#endif