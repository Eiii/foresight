#include "foresight/arbiter.h"

using std::move;

namespace fore {

Arbiter::Arbiter(Domain&& domain) :
    domain_(move(domain)) {}

}
