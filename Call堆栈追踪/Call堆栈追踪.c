#include<stdio.h>
#include<Windows.h>

IMAGE_DOS_HEADER DosHeader;
IMAGE_NT_HEADERS NtHeader;
//IMAGE_FILE_HEADER FileHeader;
//IMAGE_OPTIONAL_HEADER OptionalHeader;
PIMAGE_SECTION_HEADER SectionHeader = NULL;

//typedef struct _SECTION_INFO
//{
//	PCHAR Name;
//	DWORD Address;
//	DWORD Size;
//
//}SECTION_INFO, *PSECTION_INFO;


//PSECTION_INFO SectionInfo = NULL;
DWORD ProgramBaseAddress = NULL;
DWORD ProgramMaxBaseAddress = NULL;

void CallStackTest(int TestTimes)
{
	DWORD CurrentEbp = NULL;
	DWORD ReturnAddress = NULL;









	__asm
	{
		mov CurrentEbp, ebp
	}
	for (int n = 0; n < TestTimes; n++)
	{
		CurrentEbp = *((PDWORD)CurrentEbp);
		ReturnAddress = *((PDWORD)(CurrentEbp + 0x4));

		//判断地址是否合法

		if (ReturnAddress > ProgramMaxBaseAddress || ReturnAddress < ProgramBaseAddress)
		{
			
			MessageBoxA(NULL, "检测到非法Call调用!", "警告", NULL);


		}


	}


}


int add(int a, int b)
{
	CallStackTest(3);
	int c = 0;
	c = a + b;
	return c;
}

int main()
{
	////测试LoadLibraryA返回的地址与GetModuleHandle是否一样

	//printf("GetMoudleHandle return the address:%X\n", GetModuleHandle(NULL));
	//printf("LoadLibraryA return the address:%X\n", LoadLibraryA("Call堆栈追踪.exe"));

	////结果是一样的

	//初始化结构体
	memset(&DosHeader, 0, sizeof(IMAGE_DOS_HEADER));
	memset(&NtHeader, 0, sizeof(IMAGE_NT_HEADERS));
	//memset(&FileHeader, 0, sizeof(IMAGE_FILE_HEADER));
	//memset(&OptionalHeader, 0, sizeof(IMAGE_OPTIONAL_HEADER));
	ProgramBaseAddress = LoadLibraryA("Call堆栈追踪.exe");
	DosHeader = *(PIMAGE_DOS_HEADER)ProgramBaseAddress;
	NtHeader = *(PIMAGE_NT_HEADERS)(DosHeader.e_lfanew + ProgramBaseAddress);
	//SectionHeader = (PIMAGE_SECTION_HEADER)(DosHeader.e_lfanew + ProgramBaseAddress + 0x18 + 0x60 + 0x80);
	//SectionInfo = (PSECTION_INFO)malloc(NtHeader.FileHeader.NumberOfSections * sizeof(SECTION_INFO));
	ProgramMaxBaseAddress = ProgramBaseAddress + NtHeader.OptionalHeader.SizeOfImage;




	//printf("SizeofCode:%X\n", NtHeader.OptionalHeader.SizeOfCode);
	//printf("SizeofImage:%X\n", NtHeader.OptionalHeader.SizeOfImage);


	//for (int n = 0; n < NtHeader.FileHeader.NumberOfSections; n++)
	//{
	//	//SectionInfo[n].Name = SectionHeader->Name;

	//	SectionInfo[n].Name = (SectionHeader->Name);
	//	SectionInfo[n].Address = ProgramBaseAddress + SectionHeader->VirtualAddress;

	//	SectionInfo[n].Size = ((int)(SectionHeader->SizeOfRawData / NtHeader.OptionalHeader.SectionAlignment))*NtHeader.OptionalHeader.SectionAlignment + NtHeader.OptionalHeader.SectionAlignment;
	//	SectionHeader = SectionHeader + 1;
	//}
	//for (int n = 0; n < NtHeader.FileHeader.NumberOfSections; n++)
	//{
	//	//SectionInfo[n].Name = SectionHeader->Name;


	//	printf("SectionName:%s\n", SectionInfo[n].Name);
	//	printf("SectionAddress:%X\n", SectionInfo[n].Address);
	//	printf("SectionSize:%X\n", SectionInfo[n].Size);

	//}
	add(1, 2);

	getchar();
	return 0;
}