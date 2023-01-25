#pragma once

#include "drConfig.h"

class drChecker {
public:
    drChecker(mLog* aLog) : _cfg(_SRV_CFG_FILE) { log = aLog; }
    ~drChecker(void) { counts.clear(); }

    void check(void);

private:
    mLog* log;
    drConfig _cfg;
    std::map<DWORD, int> counts;
};

