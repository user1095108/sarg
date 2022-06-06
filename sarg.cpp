#include <iostream>

#include "sarg.hpp"

//////////////////////////////////////////////////////////////////////////////
int main(int, char* argv[]) noexcept
{
  sarg::sarg(
    argv,
    [](std::string_view const& a, std::string_view const& b) noexcept
    {
      if (("help" == a) || ("version" == a))
      {
        std::cout << "no " << a << " for you!" << '\n';
      }

      std::cout << a << " = " << b << '\n';
    }
  );

  return 0;
}
