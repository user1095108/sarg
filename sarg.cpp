#include <iostream>

#include "sarg.hpp"

//////////////////////////////////////////////////////////////////////////////
int main(int, char* argv[]) noexcept
{
  sarg::sarg(
    argv,
    [](std::string_view const k, std::string_view const v) noexcept
    {
      if (("help" == k) || ("version" == k))
      {
        std::cout << "no " << k << " for you!" << '\n';
      }

      std::cout << k << " = " << v << '\n';
    }
  );

  return 0;
}
