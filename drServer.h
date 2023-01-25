#pragma once

#include <Poco/Thread.h>
#include "drChecker.h"

class drServer : public Poco::Thread, public Poco::Runnable {
public:
	drServer(mLog* aLog);
	virtual ~drServer(void);

	void stop(void);

protected:
	virtual void run(void);

private:
	bool _running;
	mLog* log;
	drConfig _cfg;
	std::shared_ptr<drChecker> _manager;
};

