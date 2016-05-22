#pragma once

#include <map>
#include <string>

namespace fore {

class Resource {
  public:
    using Id = int;
    using Map = std::map<Id, Resource>;
    using Amount = std::map<Id, int>;

  public:
    Resource(Id id, std::string name);
    virtual ~Resource() = default;
    //Forbid copying
    Resource(const Resource& rhs) = delete;
    Resource& operator=(const Resource& rhs) = delete;
    //Allow moving
    Resource(Resource&& rhs) = default;
    Resource& operator=(Resource&& rhs) = default;

  //Getters
  public:
    Id id() const { return id_; }
    const std::string& name() const { return name_; }

  private:
    Id id_;
    std::string name_;
};

//Utility functions
bool has_enough(const Resource::Amount& source, 
                const Resource::Amount& required);
Resource::Amount operator-(const Resource::Amount& lhs, 
                           const Resource::Amount& rhs);
Resource::Amount operator+(const Resource::Amount& lhs, 
                           const Resource::Amount& rhs);
Resource::Amount operator*(const Resource::Amount& lhs, int rhs);
int operator/(const Resource::Amount& lhs, const Resource::Amount& rhs);

}
