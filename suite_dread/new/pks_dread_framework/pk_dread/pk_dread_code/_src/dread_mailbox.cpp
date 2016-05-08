/*=====================================================================================*/
/**
 * api.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_events.h"
#include "dread_mailbox.h"
#include "dread_threads.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <algorithm>
/*=====================================================================================*
 * Namespace Definition
 *=====================================================================================*/
using namespace dread;
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static std::map<uint32_t, MailBoxDispatcher*> Create_Dispatcher_Maps(void);
static std::map<int, MailBoxListener*> Create_Listener_Maps(void);
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
MailBoxFactory<uint32_t,MailBoxDispatcher> dread::Dispatcher_Factory(Create_Dispatcher_Maps());
MailBoxFactory<int,MailBoxListener> dread::Listener_Factory(Create_Listener_Maps());
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

#undef DREAD_EVENT
#define DREAD_EVENT(ev, desc) map[ev] = new MailBoxDispatcher(ev);

std::map<uint32_t, MailBoxDispatcher*> Create_Dispatcher_Maps(void)
{
   std::map<uint32_t, MailBoxDispatcher*> map;
   map[DREAD_NULL_EV] = new MailBoxDispatcher(DREAD_NULL_EV);
   DREAD_PUBLIC_EVENTS
   DREAD_PRIVATE_EVENTS
   return map;
}

#undef DREAD_THREAD_ID
#define DREAD_THREAD_ID(thread, desc) map[thread] = new MailBoxListener(thread);

std::map<int, MailBoxListener*> Create_Listener_Maps(void)
{
   std::map<int, MailBoxListener*> map;
   map[DREAD_NULL_THREAD] = new MailBoxListener(DREAD_NULL_THREAD);
   DREAD_REGISTERED_THREADS
   return map;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
MailBoxListener::MailBoxListener(const int thread)
: thread(thread), pk_queue()
{}
void MailBoxListener::register_packet(const Packet & packet)
{
   this->pk_queue.push_back(packet);
}

Packet const * MailBoxListener::receive_packet(void)
{
   const Packet * pk = nullptr;

   if(!this->pk_queue.empty())
   {
      pk = &this->pk_queue.front();
   }

   return pk;
}
Packet const * MailBoxListener::receive_packet_timeout(const uint32_t tout)
{
   const Packet * pk = nullptr;
   uint32_t timeout_calc = 0;
   do
   {
      pk = this->receive_packet();
   }while(nullptr == pk && timeout_calc < tout);

   return pk;
}

Packet const * MailBoxListener::receive_packet_only(std::vector<uint32_t> const & event_list)
{
   const Packet * pk = nullptr;

   if(!this->pk_queue.empty() && !event_list.empty())
   {
      for(std::vector<uint32_t>::const_iterator it = event_list.begin(); it != event_list.end();
            ++it)
      {
         for(std::deque<Packet>::iterator found = this->pk_queue.begin();
               found != this->pk_queue.end(); ++found)
         {
            if(*it == found->event)
            {
               pk = found._M_cur;
            }
         }
      }
   }

   return pk;
}

Packet const * MailBoxListener::receive_packet_only_timeout(std::vector<uint32_t> const & event_list,
      const uint32_t tout)
{
   const Packet * pk = nullptr;
   uint32_t timeout_calc = 0;
   do
   {
      pk = this->receive_packet_only(event_list);
   }while(nullptr == pk && timeout_calc < tout);

   return pk;
}

bool MailBoxListener::register_events(std::vector<uint32_t> const & event_list)
{
   bool success = true;
   for(std::vector<uint32_t>::const_iterator event = event_list.begin();
         event != event_list.end() && success; ++event)
   {
      success = dread::Dispatcher_Factory.get_instance(*event).register_listener(*this);
   }
   return success;
}

bool MailBoxListener::unregister_events(std::vector<uint32_t> const & event_list)
{
   bool success = true;
   for(std::vector<uint32_t>::const_iterator event = event_list.begin();
         event != event_list.end() && success; ++event)
   {
      success = dread::Dispatcher_Factory.get_instance(*event).unregister_listener(*this);
   }
   return success;
}

MailBoxDispatcher::MailBoxDispatcher(const uint32_t event)
: event(event), listener_map()
{}

void MailBoxDispatcher::notify_listener(const int app_id, Packet const & packet)
{
   std::map<int, MailBoxListener*>::iterator found = this->listener_map.find(packet.thread);
   if(this->listener_map.end() != found)
   {
      found->second->register_packet(packet);
   }
}
void MailBoxDispatcher::notify_all_listener(Packet const & packet)
{
   for(std::map<int, MailBoxListener*>::iterator it = this->listener_map.begin();
         it != this->listener_map.end(); ++it)
   {
      it->second->register_packet(packet);
   }
}

bool MailBoxDispatcher::register_listener(MailBoxListener & listener)
{
   bool success = false;
   std::map<int, MailBoxListener*>::iterator found = this->listener_map.find(listener.thread);
   if(this->listener_map.end() == found)
   {
      this->listener_map.insert(std::make_pair(listener.thread, &listener));
      success = true;
   }
   return success;
}

bool MailBoxDispatcher::unregister_listener(MailBoxListener & listener)
{
   bool success = false;
   std::map<int, MailBoxListener*>::iterator found = this->listener_map.find(listener.thread);
   if(this->listener_map.end() != found)
   {
      this->listener_map.erase(found);
      success = true;
   }
   return success;
}
/*=====================================================================================* 
 * api.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/




