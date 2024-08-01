#include <iostream>
#include "sv/logger.hpp"

int main()
{
  trace;

  {
    scope_trace(test);

  }

  // sv::logger::release();
  return 0;
}