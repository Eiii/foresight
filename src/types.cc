#include "foresight/types.h"

namespace fore {

std::ostream& operator<<(std::ostream& s, const Point& p) 
{
  s << "{";
  for (unsigned int i = 0; i < p.size(); i++) {
    s << p[i];
    if (i < p.size()-1) s << ", ";
  }
  s << "}";
  return s;
}

}
