#pragma once

#include <Poco/Util/ServerApplication.h>
#include "drServer.h"

static const char* _SRV_LOG_FILES = "logs\\dr_%Y.%m.%d.log";

class drApplication : public Poco::Util::ServerApplication {
public:
	drApplication(void) : log(_SRV_LOG_FILES) { _started = false; }
	~drApplication(void) { /* Do nothing */ }

protected:
	int main(const std::vector<std::string>&);

private:
	bool _started;
	mLog log;
	std::shared_ptr<drServer> _srv;

	void initialize(Application& self);
	void uninitialize(void);

	drApplication(const drApplication&)            = delete;
	drApplication& operator=(const drApplication&) = delete;
};

