#pragma once

#include <map>

#include "foresight/types.h"

namespace fore {

class Model {
  //Public type aliases
  public:
    using Id = int;
    using Map = std::map<Id, Model>;
    using ObsMap = std::map<Id, ObsList>;

  //Public enums
  public:
    enum class Type { RASTRIGIN, ROSENBROCK, COSINE };

  //Constructors
  public:
    Model(Id id, Type type);
    virtual ~Model() = default;
    //Forbid copying
    Model(const Model& rhs) = delete;
    Model& operator=(const Model& rhs) = delete;
    //Allow moving
    Model(Model&& rhs) = default;
    Model& operator=(Model&& rhs) = default;

  //Getters
  public:
    Id id() const { return id_; }
    Type type() const { return type_; }
  
  private:
    Id id_;
    Type type_;
};

}
