#pragma once
#include <string>

struct Invoice
{
	bool isElementFound = false;
	std::string	price;
	std::string	costumerCode;
	std::string	costumerName;
	std::string	phoneNumber;
	std::string	operatorName;

};

Invoice GetSepidz();
