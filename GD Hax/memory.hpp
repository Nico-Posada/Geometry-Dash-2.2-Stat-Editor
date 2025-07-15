#pragma once
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <cstdint>
#include <print>

class driver {
private:
	const char* modname = nullptr;
	HANDLE hProc = NULL;

	bool attached = false;

public:
	uintptr_t base = NULL;
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
							this->base = reinterpret_cast<uint64_t>(ModuleEntry32.modBaseAddr);
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
			std::println("Failed to get process info!\nBase Address: {:#x}, hProc: {:#x}", this->base, reinterpret_cast<uintptr_t>(this->hProc));
		else
			attached = true;

		CloseHandle(snapshot);
	}

	~driver()
	{
		CloseHandle(this->hProc);
	}

	bool is_attached() const
	{
		return this->attached;
	}

	HANDLE get_hproc() const
	{
		return this->hProc;
	}

	bool write_memory(void* pAddress, void* buffer, SIZE_T size) const
	{
		return WriteProcessMemory(this->hProc, pAddress, buffer, size, NULL);
	}

	SIZE_T read_memory(void* pAddress, void* out_buffer, SIZE_T size) const
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
	T read(uintptr_t address)
	{
		return read<T>(reinterpret_cast<void*>(address));
	}

	template<typename T>
	__declspec(noinline) bool write(void* address, T value)
	{
		return write_memory(address, &value, sizeof(T));
	}

	template<typename T>
	bool write(uintptr_t address, T value)
	{
		return write<T>(reinterpret_cast<void*>(address), value);
	}
};