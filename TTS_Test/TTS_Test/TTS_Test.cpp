// TTS_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sapi.h>


int speak(const std::wstring & text)
{
	ISpVoice * pVoice = NULL;	//not mandatory - just initializing 
	
	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	//setup
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (SUCCEEDED(hr))
	{
		hr = pVoice->Speak(text.c_str(), 0, NULL);		//need to figure out a way to convert std::string to wchar_t(LPCWSTR)
		hr = pVoice->Speak(L"<pitch middle = '-10'/>Unicestwienie ludzkości za: 5, 4, 3, 2, 1, ... <pitch middle = '+10'/>żarcik - dam wam jeszcze z 20minut.", 0, NULL);		//actual speech - needs text in wchar_t in order to work
		
		pVoice->Release();
		pVoice = NULL;
	}
	::CoUninitialize();
	return TRUE;
}

int main()
{
	std::wstring sentence;
	char end ='y';
	do
	{
		std::cout << "\nInput text you want to hear me speak:\n";
		std::getline(std::wcin, sentence);
		//TODO: somehow polish diacretic characters are changed for different characters, this needs further investigation
		speak(sentence);
		std::cout << "\nContinue? Y/N: ";
		end=_getch();
	} while ('n' != end && 'N' != end);
};

//App coded according to steps defined on site:
//https://msdn.microsoft.com/en-us/library/ms720163(v=vs.85).aspx