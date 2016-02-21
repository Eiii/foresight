#pragma once

#include <map>
#include <string>

namespace fore {

class ResourceType {
  public:
    using Id = int;
    using Map = std::map<Id, ResourceType>;

  public:
    ResourceType(Id id, std::string name);
    virtual ~ResourceType() = default;
    //Forbid copying
    ResourceType(const ResourceType& rhs) = delete;
    ResourceType& operator=(const ResourceType& rhs) = delete;
    //Allow moving
    ResourceType(ResourceType&& rhs) = default;
    ResourceType& operator=(ResourceType&& rhs) = default;

  //Getters
  public:
    Id id() const { return id_; }
    const std::string& name() const { return name_; }

  private:
    Id id_;
    std::string name_;
};

}
