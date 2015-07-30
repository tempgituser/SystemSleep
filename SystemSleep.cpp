#pragma once
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
/*
bHibernate:TRUEÐÝÃß FALSEË¯Ãß
*/
BOOL MySystemSleep(BOOL bHibernate = FALSE)
{
	HMODULE hModule = NULL;
	BOOL bRet = FALSE;
	// 		BOOLEAN WINAPI SetSuspendState(
	// 			__in          BOOLEAN Hibernate,
	// 			__in          BOOLEAN ForceCritical,
	// 			__in          BOOLEAN DisableWakeEvent
	// 			);
	typedef BOOL(WINAPI *PSetSuspendState)(BOOL Hibernate,
		BOOL ForceCritical,
		BOOL DisableWakeEvent);
	hModule = LoadLibrary(_T("PowrProf.dll"));
	if (hModule)
	{
		PSetSuspendState pSetSuspendState = NULL;
		pSetSuspendState = (PSetSuspendState)::GetProcAddress(hModule, "SetSuspendState");
		if (pSetSuspendState != NULL)
		{
			bRet = pSetSuspendState(bHibernate, 0, 0);
		}
		FreeLibrary(hModule);
	}
	return bRet;
}
void echoHelp(){
	printf("            -s : Sleep.\n");
	printf("            -h : Hibernate.\n");
}
int main(int argc, char* argv[])
{
	if (argc <= 1){
		printf("SystemSleep:\n");
		echoHelp();
		return 0;
	}
	else if (argc > 2){
		printf("SystemSleep:Too many arguments.\n");
		echoHelp();
		exit(1);
	}
	else{
		char* msChar = (char*)argv[1];
		//cout << msChar << endl;
		int length = strlen(msChar);
		if (length == 2 && msChar[0] == '-'){
			if (msChar[1] == 's'){
				printf("Sleep.\n");
				MySystemSleep(FALSE);
			}
			else if (msChar[1] == 'h'){
				printf("Hibernate.\n");
				MySystemSleep(TRUE);
			}
			else{
				printf("SystemSleep:Wrong argument.\n");
				echoHelp();
			}
		}
		else{
			printf("SystemSleep:Wrong argument.\n");
			echoHelp();
		}
	}
	return 0;
}