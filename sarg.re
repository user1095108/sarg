// https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap12.html
#include <string_view>
#include <type_traits>

namespace sarg
{

template <typename T>
void sarg(T* argv[], auto f)
  noexcept(noexcept(f(std::basic_string_view<T>{},
    std::basic_string_view<T>{})))
{
  using SV = std::basic_string_view<T>;

  bool oper{}; // operand?

  for (auto ap(&argv[1]); *ap; ++ap)
  {
    if (oper)
      f(SV{}, SV{*ap});
    else
    {
      auto YYCURSOR(*ap);

      decltype(YYCURSOR) a, b, c;

      /*!stags:re2c format = 'decltype(a) @@;'; */
      /*!re2c
        re2c:define:YYCTYPE = std::remove_cvref_t<decltype(*a)>;
        re2c:flags:encoding-policy = substitute;
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
            f(SV{a, b}, SV{c, YYCURSOR});

          continue;
        }

        "-" @a char @b @c char* { goto force_match0; }

        char+ {
          oper_match:
          oper = true;

          f(SV{}, SV{*ap, YYCURSOR});

          continue;
        }
      */
    }
  }
}

}
