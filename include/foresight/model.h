#pragma once

namespace fore {

class Model {
  //Public enum
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
  
  private:
    Type type_;
};

}
