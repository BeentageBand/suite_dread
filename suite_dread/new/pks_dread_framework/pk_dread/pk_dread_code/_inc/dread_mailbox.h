/*=====================================================================================*/
/**
 * api_ext.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_MAILBOX_H_
#define DREAD_MAILBOX_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_pk.h"

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <deque>
#include <map>
#include <stdint.h>
#include <vector>
/*=====================================================================================*
 * Namespace Definition
 *=====================================================================================*/
namespace dread{
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
template<typename Key, typename MailBox>
class MailBoxFactory
{
private:
   std::map<Key, MailBox*> mailbox_map;
public:
   MailBoxFactory(std::map<Key, MailBox*> map);
   virtual ~MailBoxFactory(void);
private:
   MailBoxFactory(MailBoxFactory const & obj){}
   MailBoxFactory & operator=(MailBoxFactory const & obj){return *this;}
public:
   MailBox & get_instance(const Key type);
};

class MailBoxListener
{
public:
   const int thread;
private:
   std::deque<Packet> pk_queue;
public:
   MailBoxListener(const int thread);
   void register_packet(const Packet & packet);
   Packet const * receive_packet(void);
   Packet const * receive_packet_timeout(const uint32_t tout);
   Packet const * receive_packet_only(std::vector<uint32_t> const & event_list);/*TODO change type to event*/
   Packet const * receive_packet_only_timeout(std::vector<uint32_t> const & event_list,/*TODO change type to event*/
         const uint32_t tout);
   bool register_events(std::vector<uint32_t> const & event_list);/*TODO change type to event*/
   bool unregister_events(std::vector<uint32_t> const & event_list);/*TODO change type to event*/
};

class MailBoxDispatcher
{
private:
   const uint32_t event;
   std::map<int, MailBoxListener*> listener_map;
public:
   MailBoxDispatcher(const uint32_t event);
   void notify_listener(const int app_id, Packet const & packet);
   void notify_all_listener(Packet const & packet);
   bool register_listener(MailBoxListener & listener);
   bool unregister_listener(MailBoxListener & listener);
};
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
extern MailBoxFactory<uint32_t,MailBoxDispatcher> Dispatcher_Factory;
extern MailBoxFactory<int,MailBoxListener> Listener_Factory;
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
template<typename Key, typename MailBox>
MailBoxFactory<Key,MailBox>::MailBoxFactory(std::map<Key, MailBox*> map)
: mailbox_map(map)
{}

template<typename Key, typename MailBox>
MailBoxFactory<Key,MailBox>::~MailBoxFactory(void)
{
   typename std::map<Key,MailBox*>::iterator it;
   for(it = this->mailbox_map.begin(); it != this->mailbox_map.end(); ++it)
   {
      delete it->second;
   }
}

template<typename Key, typename MailBox>
MailBox & MailBoxFactory<Key,MailBox>::get_instance(const Key type)
{
   MailBox * mailbox = this->mailbox_map[0U]; //TODO NullObject Method

   typename std::map<Key,MailBox*>::iterator it = this->mailbox_map.find(type);
   if(this->mailbox_map.end() != it)
   {
      mailbox = it->second;
   }
   return *mailbox;
}
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * api_ext.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
}/* dread namespace */

#endif /* DREAD_MAILBOX_H_ */


