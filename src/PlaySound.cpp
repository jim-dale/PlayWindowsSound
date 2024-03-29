#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <windows.h>
#include <mmsystem.h>

#include <map>
#include <string>
#include <vector>

#include "resource.h"

#pragma comment(lib, "winmm")

struct Sound
{
	DWORD type;
	LPCWSTR sound;
};

// This lookup table is used to find the sound entry given its name.
// The names in the following map MUST be all lowercase otherwise the name will not be matched
std::map<std::wstring, Sound> soundsMap =
{
	{ L"systemdefault",		{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMDEFAULT } },
	{ L"systemasterisk",	{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMASTERISK } },
	{ L"systemexclamation", { SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMEXCLAMATION } },
	{ L"systemexit",		{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMEXIT } },
	{ L"systemhand",		{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMHAND } },
	{ L"systemquestion",	{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMQUESTION } },
	{ L"systemstart",		{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMSTART } },
	{ L"systemwelcome",		{ SND_ALIAS_ID, (LPCWSTR)SND_ALIAS_SYSTEMWELCOME } },
	{ L"whistle",			{ SND_RESOURCE, MAKEINTRESOURCE(IDR_TOS_BOSUN_WHISTLE_1) } },
};

std::vector<Sound> ParseCommandLine(int argc, PWSTR argv[])
{
	std::vector<Sound> result;

	if (argc == 1)
	{
		result.push_back(soundsMap.at(L"systemdefault"));
	}
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			std::wstring arg(_wcslwr(argv[i]));

			if (arg.compare(L"-l") == 0)
			{
				for (auto item : soundsMap)
				{
					wprintf(L"%ls\n", item.first.c_str());
				}
			}
			else
			{
				auto item = soundsMap.find(arg);
				if (item != soundsMap.end())
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
		HMODULE hModule = nullptr;
		if ((sound.type & SND_RESOURCE) == SND_RESOURCE)
		{
			hModule = GetModuleHandle(nullptr);
		}

		(void)PlaySound(sound.sound, hModule, sound.type | SND_SYSTEM | SND_SYNC | SND_SENTRY | SND_NODEFAULT);
	}

	return 0;
}
