//  Boost noncopyable.hpp header file  --------------------------------------//

//  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility for documentation.

#ifndef MINIBOOST_NONCOPYABLE_HPP
#define MINIBOOST_NONCOPYABLE_HPP

namespace boost {

namespace noncopyable_  // protection from unintended ADL
{
  class noncopyable
  {
  protected:
      noncopyable() {}
      ~noncopyable() {}
  private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      noncopyable& operator=( const noncopyable& );
  };
}

typedef noncopyable_::noncopyable noncopyable;

} // namespace boost

#endif  // MINIBOOST_NONCOPYABLE_HPP
