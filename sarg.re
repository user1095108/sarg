#include <type_traits>

namespace sarg
{

namespace detail
{

inline void process(auto* const arg, bool& optarg, auto&& f) noexcept
{
  auto YYCURSOR(arg);

  decltype(YYCURSOR) a, b, c;

  using iter_t = std::remove_const_t<decltype(arg)>;

  /*!stags:re2c format = 'iter_t @@;'; */
  /*!re2c
    re2c:define:YYCTYPE = std::remove_reference_t<decltype(*arg)>;
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    nul   = '\000';
    eq    = [=];
    char  = (. | '\n') \ nul ;
    bchar = char \ eq;

    * { return; }

    "--" @a bchar* @b eq? @c char*? {
      force_match0:
      if (optarg)
      {
        if (a == b)
        {
          optarg = {};

          if (a != c)
          {
            goto force_match1;
          }
        }
        else
        {
          f({a, b}, {c, YYCURSOR}, {arg, YYCURSOR});
        }
      }
      else 
      {
        goto force_match1;
      }

      return;
    }

    "-" @a bchar @b char*? {
      c = b;
      goto force_match0;
    }

    char+ {
      optarg = {};

      force_match1:
      f({}, {arg, YYCURSOR}, {arg, YYCURSOR});

      return;
    }
  */
}

}

inline void sarg(auto* argv[], auto f) noexcept
{
  bool optarg{true}; // option-argument?

  for (auto a(&argv[1]); *a; ++a)
  {
    detail::process(*a, optarg, f);
  }
}

}
