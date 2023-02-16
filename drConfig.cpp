#include <fstream>
#include "drConfig.h"

/* Sleep time between events value, per ms */
const char* _CFG_VALUE_STIME = "10000";

/* Count of trying value */
const char* _CFG_VALUE_COUNT = "3";

/* Count of trying value */
const char* _CFG_VALUE_NET = "1";

void drConfig::read_file(const char* aFile) {
    std::ifstream __File(aFile);

    if (__File.is_open()) {
        size_t __cut_at;
        std::string __buf;
        __str_ci __itkb, __itke, __itvb, __itve;

        while (!__File.eof()) {
            std::getline(__File, __buf);
            __cut_at = __buf.find_first_of("=");
            if (__cut_at != std::string::npos && __cut_at > 0 && __cut_at < __buf.size() - 1) {
                __itkb = __buf.begin(); __itke = __itkb + __cut_at - 1; // Catch key
                __itvb = __itke + 2; __itve = __buf.end() - 1;          // Catch value
                _values[std::string(_ltrim(__itkb, __itke), _rtrim(__itke, __itkb))] = std::string(_ltrim(__itvb, __itve), _rtrim(__itve, __itvb));
            }
        }
        __File.close();
    }
}

void drConfig::defaults(void) {
    // Common defaults
    set_default(_CFG_NAME_STIME, _CFG_VALUE_STIME);
    set_default(_CFG_NAME_COUNT, _CFG_VALUE_COUNT);
    set_default(_CFG_NAME_NET,   _CFG_VALUE_NET);
}
