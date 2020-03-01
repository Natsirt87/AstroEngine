#pragma once
#define RUNNING_WINDOWS
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

/* Currently unused, attempt at having some utility functions
but I haven't found it necessary. */

namespace Utils
{
	#ifdef RUNNING_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <Shlwapi.h>

	inline std::string GetWorkingDirectory()
	{
		HMODULE hModule = GetModuleHandle(nullptr);
		if (hModule)
		{
			wchar_t wPath[256];
			char mPath[257];
			size_t outputSize = 257;
			size_t charsConverted = 0;
			GetModuleFileName(hModule, wPath, sizeof(wPath));
			PathRemoveFileSpec(wPath);
			wcstombs_s(&charsConverted, mPath, wPath, outputSize);
			strcat_s(mPath, "\\");
			return std::string(mPath);
		}
		return "";
	}
	#elif defined RUNNING_LINUX
	#include <unistd.h>

	inline std::string GetWorkingDirectory()
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != nullptr)
		{
			return std::string(cwd) + sdt::string("/");
		}
		return "";
	}
	#endif
}

