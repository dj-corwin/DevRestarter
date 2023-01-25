#include "drApplication.h"

using namespace Poco::Util;

void drApplication::initialize(Application& self) {
    _started = true;
    ServerApplication::initialize(self);
    log.NewLine();

    // Starting server in separate thread
    _srv = std::make_shared<drServer>(&log);
}

void drApplication::uninitialize(void) {
    if (_started) ServerApplication::uninitialize();
}

int drApplication::main(const std::vector<std::string>&) {
    if (_started) {
        if (isInteractive()) {
            std::cout << "Interactive mode detected. Press CRTL-C to exit\n";
            log.Msg(6, L"Started in interactive mode");
        }

        waitForTerminationRequest();

        _srv->stop();
        Sleep(100);

        log.Msg(6, L"Quitting...");
    }

    return Application::EXIT_OK;
}
