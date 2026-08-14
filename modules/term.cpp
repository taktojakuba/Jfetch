#include "term.h"
#include <cstdlib>
#include <string>

using namespace std;

string get_term()
{
  string term;
  const char* term_env = getenv("TERM_PROGRAM");
  if (term_env)
    term = term_env;
  else
  {
    const char* term_fallback = getenv("TERM");
    term = term_fallback ? term_fallback : "Unknown";
  }
  return term;
}