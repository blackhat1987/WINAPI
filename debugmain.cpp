#include<Windows.h>
bool Beingdebug = true;
bool debugmethod1() {//ʹ��IsDebuggerPresent�����жϣ��÷������ƽⷽ��Ϊhook����Ӧ�ĺ���
	return IsDebuggerPresent();
}
bool debugmethod2() {//ʹ��CheckRemoteDebuggerPresent�����жϣ��÷������ƽⷽ��Ϊhook����Ӧ�ĺ���
	BOOL result=false;
	if (CheckRemoteDebuggerPresent((HANDLE)0xffffffff, &result)) {//�˴�ӦΪGetCurrentProcess(),����-1ͬ������ǰ���̵�α��������ٵ�ǰ��������
		return result;
	}
	else {
		MessageBox(NULL, TEXT("Can not use CheckRemoteDebuggerPresent"), TEXT("METHOD2"), MB_OKCANCEL);
		return result;
	}
}
bool debugmethod3() {//��ѯBeingDebugged��־λ������ͨ��ѭ����ѯ�����ж�
	bool result = 0;
	__asm {
		mov eax, fs:[30h];//���̵�PEB��ַ�����fs����Ĵ���λ����
		mov al, BYTE PTR[eax + 2];//��ѯBeingDebugged��־λ
		mov result, al;
	}
	return result;
}

//NTSYSAPI NTSTATUS NTAPI NtQueryInformationProcess(
//	IN HANDLE ����������������ProcessHandle, ������������// ���̾��
//	IN PROCESSINFOCLASS ����InformationClass, �������� // ��Ϣ����
//	OUT PVOID ����������������ProcessInformation, ������ // ����ָ��
//	IN ULONG ������������ ����ProcessInformationLength, // ���ֽ�Ϊ��λ�Ļ����С
//	OUT PULONG ���������� ����ReturnLength OPTIONAL     // д�뻺����ֽ���
//	);
bool debugmethod4() {//ntglobal
	int result = 0;
	__asm {
		mov eax, fs:[0x30];
		mov eax, [eax + 0x68];
		mov result, eax;
	}
	return result == 0x70;
}

bool debugmethod5()
{
	return false;
}
long __stdcall callback(_EXCEPTION_POINTERS * excp) {
	excp->ContextRecord->Eip += 1;//�ý��ָ̻�ִ��
	Beingdebug = false;//��������쳣�����޸ı�־λ�����ж��Ƿ��ڱ�����
	return EXCEPTION_CONTINUE_EXECUTION;
}

bool debugmethod6() {
	SetUnhandledExceptionFilter(callback);
	_asm int 3
	return false;
}
bool debugmethod7()
{
	char fib[1024] = { 0 };
	// ���׳�һ���쳣��������������
	DeleteFiber(fib);
	// 0x57����˼��ERROR_INVALID_PARAMETER
	return (GetLastError() == 0x57);
}
int WINAPI WinMain(
	HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow
	) {
	
	

	
	if (debugmethod4()) {
		MessageBox(NULL, TEXT("Being Debug!"), TEXT("M3"), MB_OKCANCEL);
	}
	else {
		MessageBox(NULL, TEXT("Not Debug!"), TEXT("M3"), MB_OKCANCEL);
	}
}