// https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap12.html
#include <type_traits>

namespace sarg
{

inline void sarg(char* argv[], auto f)
  noexcept(noexcept(f({}, {})))
{
  bool oper{}; // operand?

  for (auto ap(&argv[1]); *ap; ++ap)
  {
    if (oper)
    {
      f({}, *ap);
    }
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
          {
            oper = true;

            if (a != YYCURSOR) goto oper_match; // ignore "--"
          }
          else
          {
            f({a, b}, {c, YYCURSOR});
          }

          continue;
        }

        "-" @a char @b @c char* { goto force_match0; }

        char+ {
          oper = true;

          oper_match:
          f({}, {*ap, YYCURSOR});

          continue;
        }
      */
    }
  }
}

}
