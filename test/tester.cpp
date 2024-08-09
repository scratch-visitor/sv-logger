#include "sv/logger.hpp"
#include <cstdint>
#include <iostream>

extern "C"
{

void version() {}
}

void foo(int a, int b, int c) {}

namespace sv
{
namespace detail
{

struct format_t
{
  std::string ip;
  std::uint16_t port;
};

} // namespace detail
} // namespace sv

void call(std::function<void()> f)
{
  if (f)
    f();
}

int main()
{
  trace;

  int* p = nullptr;

  {
    scope_trace(test);
  }

  foo(1, 2, 3);

  call([]() { std::cout << "hello world\n" << std::flush; });
  // sv::logger::release();

  return 0;
}