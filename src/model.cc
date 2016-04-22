#include "foresight/model.h"

namespace fore {

Model::Model(Model::Id id, Model::Type type, int seed) :
    id_(id), type_(type), seed_(seed) {}

}
