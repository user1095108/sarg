#include <type_traits>

namespace sarg
{

namespace detail
{

inline void arg(char const* const arg, bool& oper, auto&& f)
{
  auto YYCURSOR(arg);

  decltype(YYCURSOR) a, b, c;

  using iter_t = std::remove_const_t<decltype(arg)>;

  /*!stags:re2c format = 'iter_t @@;'; */
  /*!re2c
    re2c:define:YYCTYPE = std::remove_cvref_t<decltype(*arg)>;
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    nul  = '\000';
    char = (. | '\n') \ nul;
    eq   = [=];

    * { return; }

    "--" @a (char \ eq)* @b eq? @c char* {
      force_match0:
      if (!oper)
      {
        goto oper_match;
      }
      else 
      {
        if (a == b) // --
        {
          oper = {};

          if (a != YYCURSOR) // --=blabla
          {
            goto oper_match;
          }
        }
        else
        {
          f({a, b}, {c, YYCURSOR});
        }
      }

      return;
    }

    "-" @a char @b char* {
      c = b;
      goto force_match0;
    }

    char+ {
      oper = {};

      oper_match:
      f({}, {arg, YYCURSOR});

      return;
    }
  */
}

}

inline void sarg(char* argv[], auto f)
{
  bool oper{true}; // operand?

  for (auto a(&argv[1]); *a; ++a)
  {
    detail::arg(*a, oper, f);
  }
}

}
