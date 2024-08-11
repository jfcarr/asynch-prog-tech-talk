# C

## Highlights

* C does not have built-in support for asynchronous operations.
  * We will leverage Linux POSIX libraries.
  * We could have used select() or poll() or fork() instead.
  * There are also asynchronous libraries like `libuv` and `libevent`.
* More challenging: Lots of pointer references being passed around.

![](../../images/here-be-dragons.jpg)
