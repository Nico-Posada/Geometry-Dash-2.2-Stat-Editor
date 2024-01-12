#pragma once
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>

class driver {
private:
	const char* modname = nullptr;
	HANDLE hProc = NULL;

	bool attached = false;

public:
	DWORD base = NULL;
	driver(const wchar_t* procname)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (!Process32First(snapshot, &entry))
			return;

		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (wcscmp(entry.szExeFile, procname) == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				this->hProc = hProcess;

				HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, entry.th32ProcessID);
				MODULEENTRY32 ModuleEntry32;
				ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

				if (Module32First(hSnapshot, &ModuleEntry32))
				{
					do
					{
						if (wcscmp(ModuleEntry32.szModule, procname) == 0)
						{
							this->base = reinterpret_cast<DWORD>(ModuleEntry32.modBaseAddr);
							break;
						}
					}
					while (Module32Next(hSnapshot, &ModuleEntry32));
				}

				CloseHandle(hSnapshot);
				break;
			}
		}
		
		if (!this->base || !this->hProc)
			printf("FAILED TO GET INFO | base: %X, hProc: %X\n", this->base, reinterpret_cast<unsigned int>(this->hProc));
		else
			attached = true;

		CloseHandle(snapshot);
	}

	~driver()
	{
		CloseHandle(this->hProc);
	}

	bool is_attached()
	{
		return this->attached;
	}

	HANDLE get_hproc()
	{
		return this->hProc;
	}

	bool write_memory(void* pAddress, void* buffer, SIZE_T size)
	{
		return WriteProcessMemory(this->hProc, pAddress, buffer, size, NULL);
	}

	SIZE_T read_memory(void* pAddress, void* out_buffer, SIZE_T size)
	{
		SIZE_T bytes_read;
		if (!ReadProcessMemory(this->hProc, pAddress, out_buffer, size, &bytes_read))
			return 0;

		return bytes_read;
	}

	template<typename T>
	__declspec(noinline) T read(void* address)
	{
		T ret;
		read_memory(address, &ret, sizeof(T));
		return ret;
	}

	template<typename T>
	T read(DWORD address)
	{
		return read<T>(reinterpret_cast<void*>(address));
	}

	template<typename T>
	__declspec(noinline) bool write(void* address, T value)
	{
		return write_memory(address, &value, sizeof(T));
	}

	template<typename T>
	bool write(DWORD address, T value)
	{
		return write<T>(reinterpret_cast<void*>(address), value);
	}
};