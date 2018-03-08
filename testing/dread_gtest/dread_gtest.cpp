#include "gtest/gtest.h"
#include "dread_gtest_ext.h"
#include "ccipc.h"

using namespace fwk;

IPC_Worker::IPC_Worker(char **  const argv, int * const argc, ipc::Thread::Attributes & attr)
: ipc::Worker(ipc::IPC_CCGTEST_TID, attr),
  argv(argv),
  argc(argc)
{}

IPC_Worker::~IPC_Worker(void){}

void IPC_Worker::on_start(void){}
void IPC_Worker::on_message(ipc::Mail & mail){}
void IPC_Worker::on_periodic(void)
{
	this->main();

}
void IPC_Worker::on_stop(void)
{

}

void IPC_Worker::main(void)
{
	testing::InitGoogleTest(this->argc, this->argv);
	RUN_ALL_TESTS();

	ipc::Mail shutdown_mail(ipc::WORKER_BCT_SHUTDOWN_MID);
	ipc::IPC::Get().publish(shutdown_mail);
}

int main(char ** argv, int argc)
{
	static std::vector<ipc::TID_T> deps;
	static ipc::Thread::Attributes attr(0, 64UL, deps);
	static IPC_Worker gtest_wrkr(argv, &argc, attr);
	ipc::IPC::Get().run(ipc::IPC_CCGTEST_TID);
	ipc::IPC::Get().wait(ipc::IPC_CCGTEST_TID, 10000);
}
