#ifndef SHARED_PTR_HH
#define SHARED_PTR_HH

#include <boost/smart_ptr.hpp>
using boost::shared_ptr;
using boost::enable_shared_from_this;
using boost::make_shared;

namespace boost {
  template<typename T>
  bool operator<(const shared_ptr<T> &l, const shared_ptr<T> &r)
  {
    return (size_t) l.get() < (size_t) r.get();
  }
}

#endif
