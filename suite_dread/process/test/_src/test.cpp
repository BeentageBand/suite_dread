/*=====================================================================================*/
/**
 * test.cpp
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
#include "gtest.h" // Always gtest header goes first
#include "test_stubs.h"
#include "dread.h"
#include "dread_assert.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <iostream>
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
class LocalThread : public dread::Thread
{
   const int id = 45;
public:
   LocalThread(void);
   virtual int on_thread(void);
};

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static bool Test_Local_Thread = false;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
LocalThread::LocalThread(void)
: dread::Thread(id)
{

}
int LocalThread::on_thread(void)
{
   Test_Local_Thread = this->is_alive;
   while(this->is_alive)
   {
   std::cout << "This is Local Thread Test" << std::endl;
   sleep(1);
   this->is_alive = Test_Local_Thread;
   }
   std::cout << "Exit this is Local Thread Test" << std::endl;
   return 0;
}

TestDispatch::TestDispatch(const int id)
: dread::Thread(id)
{

}
int TestDispatch::on_thread(void)
{
   std::vector<uint32_t> events(1,TEST_EVG_ALIVE);
   events.push_back(TEST_EVG_SHUTDOWN);
   dread::Subscribe(events);
   Tr_Notify(__FUNCTION__);
   while(this->is_alive)
   {
      const dread::Packet * pk = dread::Receive_Packet();
      if(nullptr != pk)
      {
         switch(pk->event)
         {
         case TEST_EVG_ALIVE:
         {
            break;
         }
         case TEST_EVG_SHUTDOWN:
         {
            break;
         }
         default: break;
         }
      }
   }
   dread::Unsubscribe(events);
   return 0;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/

TEST(TestDread, Init)
{
   Tr_Notify("Testing Init");
   ASSERT_FALSE(Test_Local_Thread);
   LocalThread lt;
   lt.run();
   while(!Test_Local_Thread){};
   ASSERT_TRUE(Test_Local_Thread);
   Test_Local_Thread = false;
}

TEST(DreadPacket, SendPacket)
{
   Tr_Notify("Testing Application");
   apm::Application_Manager().run_application();
}

/*=====================================================================================* 
 * test.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


