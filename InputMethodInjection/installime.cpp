#include<Windows.h>
#include<imm.h>
#include<iostream>
HKL m_hImeFile32;
DWORD m_retV;

void UnistallIME() {
	::SystemParametersInfo(SPI_SETDEFAULTINPUTLANG, 0, &m_retV, SPIF_SENDWININICHANGE);//��ԭĬ�����뷨
																					   //ж�����뷨
	if (UnloadKeyboardLayout(m_hImeFile32)) {
		MessageBox(NULL, L"UnInstallIME", L"tit", MB_OK);
	}
}
void InstallIME(int a) {
	//��ȡ��ǰ���뷨

	::SystemParametersInfo(
		SPI_GETDEFAULTINPUTLANG, 0, &m_retV, 0
		);
	if(a==1)
		m_hImeFile32 = ImmInstallIMEW(TEXT("Ime_A.ime"), TEXT("�ҵ����뷨"));//���뷨��װ
	else if(a==2)
		m_hImeFile32 = ImmInstallIMEW(TEXT("Ime_B.ime"), TEXT("�ҵ����뷨"));//���뷨��װ
	if (ImmIsIME(m_hImeFile32)) {
		SystemParametersInfo(SPI_SETDEFAULTINPUTLANG, 0, &m_hImeFile32, SPIF_SENDWININICHANGE);//����Ĭ�����뷨
		MessageBox(NULL, L"InstallIME", L"my", MB_OK);
	}
}
using namespace std;
void main() {
	int a;
	while (true) {
		cout << "��������ѡ��\n1.��װ���뷨1\n2.ж�����뷨1\n3.��װ���뷨2\n4.ж�����뷨2\n5.�˳�\n������:" << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			InstallIME(1);

			break;
		case 2:
			UnistallIME();
			break;
		case 3:
			InstallIME(2);

			break;
		case 4:
			UnistallIME();
			break;
		case 5:
			return;
		default:
			break;
		}
		getchar();
	}
}