#pragma once

namespace fore {
  
class Duration {
  //Constructors
  public:
    Duration(int mean);
    virtual ~Duration() = default;
    Duration(const Duration& rhs) = default;
    Duration& operator=(const Duration& rhs) = default;
    Duration(Duration&& rhs) = default;
    Duration& operator=(Duration&& rhs) = default;

  //Member variables
  private:
    int mean_;
};

}
