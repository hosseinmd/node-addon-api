#include "BstrToStdString.h"

std::string& BstrToStdStringPtr(const BSTR bstr, std::string& dst)
{
    int cp = CP_UTF8;
    if (!bstr)
    {
        // define NULL functionality. I just clear the target.
        dst.clear();
        return dst;
    }

    // request content length in single-chars through a terminating
    //  nullchar in the BSTR. note: BSTR's support imbedded nullchars,
    //  so this will only convert through the first nullchar.
    int res = WideCharToMultiByte(cp, 0, bstr, -1, NULL, 0, NULL, NULL);
    if (res > 0)
    {
        dst.resize(res);
        WideCharToMultiByte(cp, 0, bstr, -1, &dst[0], res, NULL, NULL);
    }
    else
    {    // no content. clear target
        dst.clear();
    }
    return dst;
}

// conversion with temp.
std::string BstrToStdString(BSTR bstr)
{
    std::string str;
    BstrToStdStringPtr(bstr, str);
    return str;
}