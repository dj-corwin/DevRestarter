#include "drServer.h"

const wchar_t* _SRV_VER_NO = L"0.1.0";               /* Server version number */
const wchar_t* _SRV_FULL_NAME = L"Device Restarter"; /* Server full name */

drServer::drServer(mLog* aLog) : Thread(), Runnable(), _cfg(_SRV_CFG_FILE) {
	_running = false;

	log = aLog;
	std::wstring __lstr;
	log->Msg(3, __lstr.assign(L"Initializing ", 13).append(_SRV_FULL_NAME).append(L" ver.", 5).append(_SRV_VER_NO));
	_manager = std::make_shared<drChecker>(log);

	// Running server
	try { start(*this); _running = true; }
	catch (...) { log->Msg(1, L"Server couldn`t start"); }
}

drServer::~drServer(void) {
	if (_running) stop();
	log->Msg(3, L"Server has been stopped");
}

void drServer::stop(void) {
	_running = false;
	log->Msg(3, L"Shutting down server...");
}

void drServer::run(void) {
	log->Msg(6, L"Starting server...");
	Sleep(100);

	while (isRunning() && _running) {
		_manager->check();

		// Let's service sleep a bit
		Sleep(_cfg.get(_CFG_NAME_STIME));
	}
}
