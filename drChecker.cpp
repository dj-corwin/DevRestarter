#include "drChecker.h"
#include <SetupAPI.h>
#include <devguid.h>
#include <cfgmgr32.h>

#pragma comment(lib, "SetupAPI.lib")

const unsigned short MAX_DESC_LEN = 128;

void drChecker::check(void) {
    HDEVINFO info;
    if (_cfg.get(_CFG_NAME_NET) == 1) {
        GUID netGuid = GUID_DEVCLASS_NET; //{ 0x4d36e972, 0xe325, 0x11ce, { 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };
        info = SetupDiGetClassDevs(&netGuid, 0, 0, DIGCF_PRESENT);
    } else {
        info = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    }

    PSP_DEVINFO_DATA data = new SP_DEVINFO_DATA();
    data->cbSize = sizeof(SP_DEVINFO_DATA);

    PBYTE output = new BYTE[MAX_DESC_LEN];
    PDWORD dataType = new DWORD;
    PDWORD requiredSize = new DWORD;
    DWORD i = 0;
    ULONG status, problemNo;
    std::wstring __log;
    wchar_t ts[max_int_len];
    size_t tn;

    while (SetupDiEnumDeviceInfo(info, i++, data)) {
        if (CM_Get_DevNode_Status(&status, &problemNo, data->DevInst, 0) != CR_NO_SUCH_DEVNODE) {
            if (status & DN_HAS_PROBLEM) {
                if (++counts[data->DevInst] > _cfg.get(_CFG_NAME_COUNT)) continue;

                if (SetupDiGetDeviceRegistryProperty(info, data, SPDRP_FRIENDLYNAME, dataType, output, MAX_DESC_LEN, requiredSize)) {
                    // Do nothing
                } else if (SetupDiGetDeviceRegistryProperty(info, data, SPDRP_DEVICEDESC, dataType, output, MAX_DESC_LEN, requiredSize)) {
                    // Do nothing
                }

                log->Msg(6, str2wcs((const char*)output, __log));
                log->Msg(9, __log.assign(L"Status: ", 8).append(int2wcs(status, ts, tn)));
                log->Msg(9, __log.assign(L"Problem: ", 9).append(int2wcs(problemNo, ts, tn)));

                log->Msg(6, __log.assign(L"Trying to disable device... (", 29).append(int2wcs((int)counts[data->DevInst], ts, tn)).append(L")"));
                if (CM_Disable_DevNode(data->DevInst, 0) == CR_SUCCESS) {
                    log->Msg(8, L"Device disabled");
                    Sleep(1000);
                    log->Msg(6, L"Trying to ensable device...");
                    if (CM_Enable_DevNode(data->DevInst, 0) == CR_SUCCESS) {
                        log->Msg(8, L"Device enabled");
                        if (CM_Get_DevNode_Status(&status, &problemNo, data->DevInst, 0) != CR_NO_SUCH_DEVNODE) {
                            if (!(status & DN_HAS_PROBLEM)) {
                                counts[data->DevInst] = 0; // Clear counter if problem solved
                            }
                        }
                    } else {
                        log->Msg(8, L"Device cannot be enabled");
                    }
                } else {
                    log->Msg(8, L"Device cannot be disabled");
                }
            }
        }
    }

    SetupDiDestroyDeviceInfoList(info);

    delete dataType;
    delete requiredSize;
    delete data;
    delete[] output;
}
