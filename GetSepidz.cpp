#define UNICODE
#include "GetSepidz.h"
#include "BstrToStdString.h"
#include <UIAutomation.h>
#include <iostream>
#include <string>
#include <sstream>


Invoice getInvoice(CComQIPtr<IUIAutomation> uia, CComPtr<IUIAutomationElement> mainForm) {
	Invoice invoice;


	CComPtr<IUIAutomationCondition> condition;

	//URL's id is 0xC354, or use UIA_EditControlTypeId for 1st edit box
	uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC354), &condition);

	CComPtr<IUIAutomationElementArray> edits;
	if (FAILED(mainForm->FindAll(TreeScope_Children, condition, &edits))
		|| !edits)
		return invoice; //maybe we don't have the right tab, continue...


	CComPtr<IUIAutomationElement> priceElement;
	edits->GetElement(20, &priceElement);
	CComVariant price;
	priceElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &price);


	CComPtr<IUIAutomationElement> costumerCodeElement;
	edits->GetElement(21, &costumerCodeElement);
	CComVariant costumerCode;
	costumerCodeElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &costumerCode);

	CComPtr<IUIAutomationElement> nameElement;
	edits->GetElement(22, &nameElement);
	CComVariant name;
	nameElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &name);

	CComPtr<IUIAutomationElement> phoneNumberElement;
	edits->GetElement(23, &phoneNumberElement);
	CComVariant phoneNumber;
	phoneNumberElement->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &phoneNumber);

	invoice.price = BstrToStdString(price.bstrVal);
	invoice.costumerCode = BstrToStdString(costumerCode.bstrVal);
	invoice.costumerName = BstrToStdString(name.bstrVal);
	invoice.phoneNumber = BstrToStdString(phoneNumber.bstrVal);

	return invoice;
}


std::string getOperator(CComQIPtr<IUIAutomation> uia, CComPtr<IUIAutomationElement> mainForm) {


	CComPtr<IUIAutomationCondition> condition;

	//URL's id is 0xC354, or use UIA_EditControlTypeId for 1st edit box
	uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC371), &condition);

	CComPtr<IUIAutomationElementArray> pane;
	if (FAILED(mainForm->FindAll(TreeScope_Children, condition, &pane))
		|| !pane)
		return ""; //maybe we don't have the right tab, continue...


	CComPtr<IUIAutomationElement> operatorElement;
	pane->GetElement(9, &operatorElement);
	BSTR opr;
	operatorElement->get_CurrentName(&opr);

	return BstrToStdString(opr);
}

Invoice GetSepidz()
{
	Invoice result;
	CoInitialize(NULL);

	while (true) {
		CComQIPtr<IUIAutomation> uia;
		if (FAILED(uia.CoCreateInstance(CLSID_CUIAutomation)) || !uia)
			break;


		CComPtr<IUIAutomationElement> root;
		if (FAILED(uia->GetRootElement(&root)) || !root)
			break;

		CComPtr<IUIAutomationCondition> trueCondition;

		//URL's id is 0xC354, or use UIA_EditControlTypeId for 1st edit box
		uia->CreateTrueCondition(&trueCondition);

		CComPtr<IUIAutomationElementArray> childrens;
		if (FAILED(root->FindAll(TreeScope_Children, trueCondition, &childrens))
			|| !childrens)
			break; //maybe we don't have the right tab, continue...

		int lenght;
		childrens->get_Length(&lenght);

		for (size_t i = 0; i < lenght; i++)
		{
			CComPtr<IUIAutomationElement> mainForm;

			childrens->GetElement(i, &mainForm);

			BSTR currentClassName;
			mainForm->get_CurrentClassName(&currentClassName);

			if (0 == wcscmp(currentClassName, L"TDocInfo14Form")) {

				Invoice invoice = getInvoice(uia, mainForm);

				result.operatorName = getOperator(uia, mainForm);
				invoice.price =invoice.price;
				invoice.costumerCode =	invoice.costumerCode;
				invoice.costumerName = invoice.costumerName;
				invoice.phoneNumber = invoice.phoneNumber;
				result.isElementFound = true;

				return result;
			}
		}
		break;

	}



	CoUninitialize();

	return result;

}
