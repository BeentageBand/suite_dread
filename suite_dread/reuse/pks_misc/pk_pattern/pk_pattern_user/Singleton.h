/*
 * Singleton.h
 *
 *  Created on: 20/08/2015
 *      Author: ASUS
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

/*============================================================================*
 * Standard #include Headers
 *============================================================================*/
#include <memory>
#include <set>
#include <stdint.h>
/*============================================================================*
 * Exported #define Constants
 *============================================================================*/
#define SINGLETON_CLASS_MAX_NUM_OF_INSTANCES ((size_t) 32U)
/*============================================================================*
 * Class Declaration
 *============================================================================*/
template<typename T, typename I>
class Singleton
{
   /*==================================================*
    * Class Constructors, Destroyers & Operators
    *==================================================*/
protected:
   Singleton(void);
   virtual ~Singleton(void);
private:
   Singleton(Singleton const & cobj);
   Singleton & operator=(Singleton const & robj);
   /*==================================================*
    * Class Static Object Member Declarations
    *==================================================*/
private:
   static std::auto_ptr<T> instance;
   static std::set<I>      client;
   /*==================================================*
    * Class Method Member Declarations
    *==================================================*/
protected:
   virtual void initialize(void) {}
   /*==================================================*
    * Class Static Method Member Declarations
    *==================================================*/
public:
   static T * Create_Instance(const I client_id)
   {
      if(client.empty() )
      {
         instance.reset(new T());
      }
      add_client(client_id);

      return instance.get();
   }
   static void Destroy_Instance(const I client_id)
   {
      remove_client(client_id);
      if(client.empty() )
      {
         instance.reset();
      }
   }
private:
   static void add_client(const I client_id)
   {
      typename std::set<I>::iterator it = client.find(client_id);
      if(client.end() == it)
      {
         client.insert(client_id);
      }
   }

   static void remove_client(const I client_id)
   {
      typename std::set<I>::iterator it = client.find(client_id);
      if(client.end() != it)
      {
         client.erase(client_id);
      }
   }
};

/*============================================================================*
 * Class Static Member Definitions
 *============================================================================*/
template<typename T, typename I> typename std::auto_ptr<T> Singleton<T,I>::instance(nullptr);
template<typename T, typename I> typename std::set<I> Singleton<T,I>::client = std::set<I>();

/*============================================================================*
 * Class Constructors, Destroyers & Operators Definitions
 *============================================================================*/
template<typename T, typename I>
Singleton<T,I>::Singleton(void)
{
   initialize();
}

template<typename T, typename I>
Singleton<T,I>::Singleton(Singleton const & cobj)
{
   initialize();
}

template<typename T, typename I>
Singleton<T,I>::~Singleton(void)
{}

template<typename T, typename I>
Singleton<T,I> & Singleton<T,I>::operator=(Singleton<T,I> const & robj)
{
   return *this;
}

#endif /* SINGLETON_H_ */
