#ifndef DREAD_GTEST_EXT_H_
#define DREAD_GTEST_EXT_H_

#include "ccworker.h"

namespace fwk
{

class IPC_Worker : public cc::Worker
{
private:
	char ** argv;
	int argc;

public:

	IPC_Worker(char ** const argv, int const argc);
	virtual ~IPC_Worker(void);

private:
	void on_start(void);
	void on_mail(cc::Mail & mail);
	void on_loop(void);
	void on_stop(void);
	void main(void);
};
}

#endif /*DREAD_GTEST_EXT_H_*/
