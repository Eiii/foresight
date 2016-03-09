#pragma once

namespace fore {

class Model;

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
