// winps.cpp : コンソール アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include <stdlib.h>

#include <windows.h>
#include <tlhelp32.h>


int print_process_list()
{
	HANDLE h_snap_process;
	PROCESSENTRY32 proc_entry;
	BOOL b_pret;


	h_snap_process = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(h_snap_process == NULL){
		printf("process snapshot get error\n");
		return 1;
	}

	printf("pid      ppid      ths     fname\n");

	proc_entry.dwSize = sizeof(PROCESSENTRY32);
	b_pret = Process32First(h_snap_process,&proc_entry);
	while(b_pret == TRUE){
		printf("%8d %8d %8d %s\n"
			,proc_entry.th32ProcessID
			,proc_entry.th32ParentProcessID 
			,proc_entry.cntThreads
			,proc_entry.szExeFile 
		);
		b_pret = Process32Next(h_snap_process,&proc_entry);
	}
	return 0;
}

int print_module_list(DWORD d_pid)
{
	HANDLE h_snap_mod;
	MODULEENTRY32 mod_entry;
	BOOL b_pret;


	h_snap_mod = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,d_pid);
	if(h_snap_mod == NULL){
		printf("module snapshot get error\n");
		return 1;
	}
	if(h_snap_mod == (HANDLE)-1){
		printf("module snapshot get error\n");
		return 1;
	}


//	printf("pid      ppid      ths     fname\n");

	mod_entry.dwSize = sizeof(MODULEENTRY32);
	b_pret = Module32First(h_snap_mod,&mod_entry);
	while(b_pret == TRUE){
		printf("%08X %08X %s %s\n"
			,mod_entry.modBaseAddr
			,mod_entry.modBaseSize
			,mod_entry.szModule  
			,mod_entry.szExePath  
		);
		b_pret = Module32Next(h_snap_mod,&mod_entry);
	}
	return 0;
}



int main(int argc, char* argv[])
{
	DWORD d_pid=0;
	int i;
	int moduleflag=0;

	for(i=1;i<argc;i++){
		if(strcmp("-p",argv[i]) == 0){
			return print_process_list();
			
		}else if(strcmp("-m",argv[i]) == 0){
			moduleflag = 1;
		}else if((moduleflag == 1)){
			d_pid = atol(argv[i]);
			return print_module_list(d_pid);
		}else{
			return -1;
		}
	}
	return 0;

}

