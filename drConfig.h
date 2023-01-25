#pragma once

#include <map>
#include <iostream>
#include "drLog.h"

/* Config file name */
#define _SRV_CFG_FILE     "dr.cfg"           

/* Count of trying */
#define _CFG_NAME_COUNT   "count_of_trying"           

/* What should be checked - all devices or net devices only */
#define _CFG_NAME_NET     "net_only"           

/* Sleep time between events, per ms */
#define _CFG_NAME_STIME   "sleep_time"

class drConfig {
private:
    struct _config_t {
    public:
        _config_t(void) : _value("") { /* Do nothing */ }
        _config_t(const char* aC) : _value(aC) { /* Do nothing */ }
        _config_t(const std::string& aS) : _value(aS) { /* Do nothing */ }

        operator const std::string& () const { return _value; }
        operator const char* () const { return _value.c_str(); }
        operator const std::wstring& () const { std::wstring __tmp;  return str2wcs(_value, __tmp); }
        operator const wchar_t* () const { std::wstring __tmp;  return str2wcs(_value, __tmp).c_str(); }
        operator const int () const { return atoi(_value.c_str()); }

    private:
        std::string _value;
    };

public:
    typedef std::map<std::string, _config_t>  _config_m;
    typedef _config_m::const_iterator         _config_ci;

    drConfig(const char* aFile) { read_file(aFile); defaults(); }
    virtual ~drConfig(void) { _values.clear(); }

    inline const _config_t& get(const std::string& aStr) const { _config_ci _find(_values.find(aStr)); return (_find != _values.end() ? _find->second : _default); }

    drConfig(const drConfig& O) : _values(O._values) { /* Do nothing */ }

private:
    typedef std::string::const_iterator __str_ci;

    _config_t _default;
    _config_m _values;

    inline void set_default(const std::string& aStr, const _config_t& aValue) { if (_values.find(aStr) == _values.end()) _values[aStr] = aValue; }

    inline const __str_ci& _ltrim(__str_ci& aIt, const __str_ci& aEnd) { while (aIt != aEnd && (*aIt) == ' ') ++aIt; return aIt; }
    inline const __str_ci& _rtrim(__str_ci& aIt, const __str_ci& aBeg) { while (aIt != aBeg && (*aIt) == ' ') --aIt; ++aIt; return aIt; }

    void read_file(const char* aFile);

    void defaults(void);
};

