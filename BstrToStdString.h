#pragma once
#include <string>
#include <AtlBase.h>
#include <AtlCom.h>

std::string& BstrToStdStringPtr(const BSTR bstr, std::string& dst);
std::string BstrToStdString(BSTR bstr);
