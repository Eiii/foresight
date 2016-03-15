#pragma once

#include "foresight/domain.h"
#include "foresight/model.h"

namespace fore {

class GP {
  //Constructor
  GP(const Model& model);
  virtual ~GP() = default;
  //Forbid copying
  GP(const GP& rhs) = delete;
  GP& operator=(const GP& rhs) = delete;
  //Allow moving
  GP(GP&& rhs) = default;
  GP& operator=(GP&& rhs) = default;

};

}
