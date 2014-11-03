lua-mesos
=========

Apache Mesos framework for Lua using LuaJIT 2.x

Description
-----------

This project serves as an initial experimentation with the Apache Mesos
framework and embedding Lua to serve as the distributed runtime / framework. The
interest in embedding Lua rather than running it via the shell would be
beneficial for a number of reasons, such as

* OOTB standard library for features such as
 * libuv for it's scalable networking architecture
 * http parser for high-performance web development
 * HDFS support
 * Mesos bindings for writing the scheduler and executor in Lua
* distributed events for cross-node communication
 * leveraging [nsq](http://nsq.io/) or some other [AMQP](http://www.amqp.org/)
* Security [sandboxing][lua-sandboxes] is relatively
  easy in Lua
* remote debugging via modified [MobDebug][]
 * would be conceivable to use WebSockets to support debugging in the browser

Why Lua?
--------

Lua and specifically LuaJIT is known to be one of the fastest dynamic languages
available. It is easy to embed in other runtimes, evidenced by its prominence
in projects like nginx, Redis, AAA games, [packet processing][snabb] and
game runtimes like [Corona][]

Status
------

**Experimental**: the project is not even close to the goals it aspires to
above, however it has embedded LuaJIT in the scheduler and executor and
allows arbitrary Lua code to be executed as a task and returns the result.


Prerequisites
-------------
lua-mesos has only been tested on OS X, however the is no reason it won't build
on *nix as long as the following dependencies are met:

* mesos
 * running master and slave
* boost
* glog
* protobuf 2.5

### OS X

Install mesos

    brew install mesos

Install boost

    brew install boost

Install glog

    brew install glog

Install protobuf compiler v2.5

    brew install https://raw.githubusercontent.com/Homebrew/homebrew/6de7a2318fd31ffdba3d9b0a02940ee54ab7796c/Library/Formula/protobuf.rb

Building
--------

    $ git clone http://github.com/stuartcarnie/lua-mesos
    $ cd lua-mesos
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

Running
-------

    > ./mesolua --master=localhost:5050 --e="return 'hello world'"
    I1103 10:50:57.872282 1999229696 sched.cpp:139] Version: 0.20.1
    I1103 10:50:57.873710 216440832 sched.cpp:235] New master detected at master@127.0.0.1:5050
    I1103 10:50:57.873818 216440832 sched.cpp:243] No credentials provided. Attempting to register without authentication
    I1103 10:50:57.874292 216440832 sched.cpp:409] Framework registered with 20141101-171912-16777343-5050-99670-0011

    hello world
    I1103 10:50:58.046589 214294528 sched.cpp:747] Stopping framework '20141101-171912-16777343-5050-99670-0011'

[snabb]: http://highscalability.com/blog/2014/2/13/snabb-switch-skip-the-os-and-get-40-million-requests-per-sec.html
[MobDebug]: https://github.com/pkulchenko/MobDebug
[lua-sandboxes]: http://lua-users.org/wiki/SandBoxes
[Corona]: http://coronalabs.com/products/corona-sdk/
