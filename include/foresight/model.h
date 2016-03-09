#pragma once

#include "foresight/types.h"

namespace fore {

class Model {
  //Public type aliases
  public:
    using Id = int;

  //Public enums
  public:
    enum class Type { COSINE };

  //Constructors
  public:
    Model(Type type);
    virtual ~Model() = default;
    //Forbid copying
    Model(const Model& rhs) = delete;
    Model& operator=(const Model& rhs) = delete;
    //Allow moving
    Model(Model&& rhs) = default;
    Model& operator=(Model&& rhs) = default;

  public:
    Point NextPoint();
    double MeanAt(Point p);
  
  private:
    Type type_;
};

}
