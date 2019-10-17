#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <windows.h>
#include <mmsystem.h>

#include <map>
#include <string>
#include <vector>

#pragma comment(lib, "winmm")

std::map<std::wstring, LPCTSTR> map =
{
	{ L"SystemAsterisk", (LPCTSTR)SND_ALIAS_SYSTEMASTERISK },
	{ L"SystemDefault", (LPCTSTR)SND_ALIAS_SYSTEMDEFAULT},
	{ L"SystemExclamation", (LPCTSTR)SND_ALIAS_SYSTEMEXCLAMATION },
	{ L"SystemExit", (LPCTSTR)SND_ALIAS_SYSTEMEXIT },
	{ L"SystemHand", (LPCTSTR)SND_ALIAS_SYSTEMHAND },
	{ L"SystemQuestion", (LPCTSTR)SND_ALIAS_SYSTEMQUESTION },
	{ L"SystemStart", (LPCTSTR)SND_ALIAS_SYSTEMSTART },
	{ L"SystemWelcome", (LPCTSTR)SND_ALIAS_SYSTEMWELCOME },
};

std::vector<LPCTSTR> ParseCommandLine(int argc, PWSTR argv[])
{
	std::vector<LPCTSTR> result;

	if (argc == 1)
	{
		result.push_back((LPCTSTR)SND_ALIAS_SYSTEMDEFAULT);
	}
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			std::wstring arg(argv[i]);

			if (arg.compare(L"-l") == 0)
			{
				for (auto item : map)
				{
					wprintf(L"%ls\n", item.first.c_str());
				}
			}
			else
			{
				auto item = map.find(arg);
				if (item != map.end())
				{
					result.push_back(item->second);
				}
			}
		}
	}

	return result;
}

int wmain(int argc, PWSTR argv[])
{
	auto sounds = ParseCommandLine(argc, argv);

	for (auto sound : sounds)
	{
		(void)PlaySound(sound, GetModuleHandle(NULL), SND_SYSTEM | SND_ALIAS_ID | SND_SYNC | SND_SENTRY);
	}

	return 0;
}
