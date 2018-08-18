#include "gtest/gtest.h"
#include "dread_gtest_ext.h"
#include "ccipc.h"

using namespace fwk;

IPC_Worker::IPC_Worker(char **  const argv, int const argc)
: cc::Worker(ipc::IPC_CCGTEST_TID),
  argv(argv),
  argc(argc)
{}

IPC_Worker::~IPC_Worker(void){}

void IPC_Worker::on_start(void){}
void IPC_Worker::on_mail(cc::Mail & mail){}
void IPC_Worker::on_loop(void)
{
	this->main();

}

void IPC_Worker::on_stop(void)
{

}

void IPC_Worker::main(void)
{
	testing::InitGoogleTest(&this->argc, this->argv);
	RUN_ALL_TESTS();
	cc::IPC::Get().publish(ipc::WORKER_PBC_SHUTDOWN_MID);
}

int main(char ** argv, int argc)
{
	static IPC_Worker gtest_wrkr(argv, argc);
	cc::IPC::Get().run(ipc::IPC_CCGTEST_TID);
	cc::IPC::Get().wait(ipc::IPC_CCGTEST_TID, 10000);
}
