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
#include "dread.h"
#include "dread_mailbox.h"
#include "dread_ext.h"
#include "dread_assert.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/
using namespace dread;
/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void dread::Send(const int app_id, const int thread_id, const uint32_t event, std::stringstream & data)
{
   const Packet pk(event, thread_id, app_id);
   *pk.data_buff << data.str();
   dread::Send(pk);

}

void dread::Send(Packet const & packet)
{
   dread::Dispatcher_Factory.get_instance(packet.thread).notify_listener(packet.app_id, packet);
}

void dread::Publish(const uint32_t event, std::stringstream & data )
{
   const Packet pk(event, DREAD_NULL_EV, 0);
   *pk.data_buff << data.str();
   dread::Publish(pk);
}

void dread::Publish(Packet const & packet)
{
   dread::Dispatcher_Factory.get_instance(packet.thread).notify_all_listener(packet);
}

const Packet * dread::Receive_Packet(void)
{
   const Packet * pk = nullptr;
   return pk;
}

const Packet * dread::Receive_Packet_Timeout(uint32_t tout)
{
   const Packet * pk = nullptr;
   return pk;
}

const Packet * dread::Receive_Packet_Only(std::vector<uint32_t> const & event_list)
{
   const Packet * pk = nullptr;
   return pk;
}

const Packet * dread::Receive_Packet_Only_Timeout(std::vector<uint32_t> const & event_list, uint32_t tout)
{
   const Packet * pk = nullptr;
   return pk;
}

bool dread::Subscribe(std::vector<uint32_t> const & event_list)
{
   bool success = false;
   int thread_id = Get_Current_Thread_Id();

   if(DREAD_NULL_THREAD < thread_id && thread_id < DREAD_NULL_THREAD)
   {
      dread::Listener_Factory.get_instance(thread_id).register_events(event_list);
   }
   return success;
}

bool dread::Unsubscribe(std::vector<uint32_t> const & event_list)
{
   bool success = false;
   int thread_id = Get_Current_Thread_Id();

   if(DREAD_NULL_THREAD < thread_id && thread_id < DREAD_NULL_THREAD)
   {
      dread::Listener_Factory.get_instance(thread_id).unregister_events(event_list);
   }
   return success;
}

Packet::Packet(const uint32_t event, const int thread, const int app_id)
: event(event), thread(thread), app_id(app_id), data_buff(new std::stringstream)
{}
/*=====================================================================================* 
 * api.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


