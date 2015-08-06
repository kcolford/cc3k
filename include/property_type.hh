#ifndef PROPERTY_TYPE_HH
#define PROPERTY_TYPE_HH

#include <string>
#include <boost/lexical_cast.hpp>

class property_type {
private:
  std::string val_;

  std::string val() const
  { return val_.empty() ? "0" : val_; }

public:
  property_type() {}

  template<typename T>
  property_type(T other)
  { val_ = boost::lexical_cast<std::string>(other); }

  operator bool() { return boost::lexical_cast<bool>(val()); }
  operator int() { return boost::lexical_cast<int>(val()); }
  operator unsigned() { return boost::lexical_cast<unsigned>(val()); }

  template<typename T>
  class updater
  {
  private:
    property_type &parent_;
    
    friend class property_type;
    updater(property_type &p): parent_(p) {}

  public:
    property_type &operator()(T val)
    { return parent_ = val; }

    property_type &operator()()
    { return parent_.as<T>(); }
  };

  template<typename T>
  T as() const 
  { return boost::lexical_cast<T>(val_); }

  template<typename T>
  updater<T> get()
  { return updater<T>(*this); }

};

#endif
