// https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap12.html
#include <type_traits>

namespace sarg
{

void sarg(char* argv[], auto f)
  noexcept(noexcept(f(std::string_view{}, std::string_view{})))
{
  bool oper{}; // operand?

  for (auto ap(&argv[1]); *ap; ++ap)
  {
    if (oper)
      f({}, *ap);
    else
    {
      auto YYCURSOR(*ap);

      decltype(YYCURSOR) a, b, c;

      /*!stags:re2c format = 'decltype(a) @@;'; */
      /*!re2c
        re2c:define:YYCTYPE = std::remove_cvref_t<decltype(*a)>;
        re2c:tags = 1;
        re2c:yyfill:enable = 0;

        nul  = '\000';
        char = (. | '\n') \ nul;
        eq   = [=];

        * { continue; }

        "--" @a (char \ eq)* @b eq? @c char* {
          force_match0:
          if (a == b) // --
            if (a == YYCURSOR) oper = true; else goto oper_match; // --=
          else
            f({a, b}, {c, YYCURSOR});

          continue;
        }

        "-" @a char @b @c char* { goto force_match0; }

        char+ {
          oper_match:
          oper = true;

          f({}, {*ap, YYCURSOR});

          continue;
        }
      */
    }
  }
}

}
