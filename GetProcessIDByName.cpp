#include<Windows.h>
#include<iostream>
#include<TlHelp32.h>
#include<vector>
using namespace std;
vector<DWORD> GetProcessIDByName(LPCTSTR szProcessName)
{
	STARTUPINFO st;
	PROCESS_INFORMATION pi;
	PROCESSENTRY32 ps;
	HANDLE hSnapshot;
	vector<DWORD> dwPID;
	ZeroMemory(&st, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	st.cb = sizeof(STARTUPINFO);
	ZeroMemory(&ps, sizeof(PROCESSENTRY32));
	ps.dwSize = sizeof(PROCESSENTRY32);
	
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//������̿���
	if (hSnapshot == INVALID_HANDLE_VALUE)//��������ʧ��
	{
		return dwPID;
	}


	if (!Process32First(hSnapshot, &ps))
	{
		return dwPID;
	}
	do
	{
		
		if (lstrcmpi(ps.szExeFile, szProcessName) == 0)//�������̿��գ��ȽϽ�����
		{
			 
			
			dwPID.push_back(ps.th32ParentProcessID);//������id�ŵ�������
		}
	} while (Process32Next(hSnapshot, &ps));
	// û���ҵ�  
	CloseHandle(hSnapshot);
	return dwPID;//��������
}
void main() {
	TCHAR name[] = TEXT("notepad.exe");
	vector<DWORD> idlist;
	idlist = GetProcessIDByName(name);
	if (idlist.size()) {//�����ҵ�
		cout << "���\t���̶�Ӧid(ʮ������)\t���̶�Ӧid(ʮ����)" << endl;
		for (vector<DWORD>::size_type it =0; it<idlist.size(); it++) {
			cout << it << "\t" << hex<<idlist[it] <<"\t\t\t"<<dec<<idlist[it]<<endl;
		}
	}
	else {//û�ҵ�
		cout << "δ�ҵ���Ӧ����" << endl;
	}
}