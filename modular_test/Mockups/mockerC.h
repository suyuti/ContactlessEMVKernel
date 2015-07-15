/*
 * mockerC.h
 *
 *  Created on: Oct 22, 2014
 *      Author: suyuti
 */

#ifndef MOCKERC_H_
#define MOCKERC_H_

#include <gmock/gmock.h>

namespace testing {
   template < typename T >
   class MockerC {
   public:
      static const T& instance() {
         const T* i = pointer();
         if (!i) {
            return *defaultInstance();
         }
         return *i;
      }

   protected:
      MockerC() {
         if (counter()++ == 0) {
            defaultInstance();
         }
         if (counter() > 2) {
            testing::internal::posix::Abort();
         }

         pointer() = static_cast<T*>(this);
      }

      ~MockerC() {
         reset();
      }

   private:
      static T* defaultInstance() {
         static testing::StrictMock<T> strict;
         return &strict;
      }

      static size_t& counter() {
         static size_t counter = 0;
         return counter;
      }

      void reset() {
         pointer() = NULL;
         counter()--;
      }

      static T*& pointer() {
         static T* i = NULL;
         return i;
      }

   private:
      MockerC(const MockerC& that);
      MockerC& operator=(const MockerC& that);
   };

}


#endif /* MOCKERC_H_ */
