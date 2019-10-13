//InforMation.cpp
#include "InforMation.h"
#include "CodeEditorForm.h"

BEGIN_MESSAGE_MAP(InforMation, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnClose)
	ON_WM_CLOSE()
	ON_STN_CLICKED(IDC_STATIC_INFORMATION_TEXT, &InforMation::OnStnClickedStaticInformationText)
END_MESSAGE_MAP()

InforMation::InforMation(CodeEditorForm* codeEditorForm) :CDialog(InforMation::IDD, codeEditorForm) {
	this->codeEditorForm = codeEditorForm;
}

BOOL InforMation::OnInitDialog() {
	CDialog::OnInitDialog(); //오버라이딩

	RTL_OSVERSIONINFOW os;
	CString info = "버전 ";
	CString str;
	Long i = 0;
	BOOL state = FALSE;

	os = this->GetRealOSVersion(); //레지스트리를 참조하여 윈도우정보를 가져온다.

	//Operating system을 구한다.
	if (os.dwMajorVersion == 6 && os.dwMinorVersion == 1) {
		info.Insert(0, "Microsoft Windows 7\n");
	}
	else if (os.dwMajorVersion == 10 && os.dwMinorVersion == 0){
		info.Insert(0, "Microsoft Windows 10\n");
	}

	str.Format(_T("%d"), os.dwMajorVersion); //메이저 버전을 형변환
	info.Insert(info.GetLength(), str + '.'); //info에 붙인다

	str.Format(_T("%d"), os.dwMinorVersion); //마이너 버전을 형변환
	info.Insert(info.GetLength(), str + " (" + "빌드 "); //info에 붙인다

	str.Format(_T("%d"), os.dwBuildNumber); //빌드번호를 형변환
	info.Insert(info.GetLength(), str); //info에 붙인다

	if (os.szCSDVersion[0] != '\0') { //서비스팩 버전이 있다면 콜론을 붙인다.
		info.Insert(info.GetLength(), " : ");
	}

	while (i < 128 && state == FALSE) { //CSD버전을 구한다.
		if (os.szCSDVersion[i] != '\0') { //널문자가 아니면 info에 붙인다.
			info.Insert(info.GetLength(), os.szCSDVersion[i]);
		}
		else {
			info.Insert(info.GetLength(), ')');
			state = TRUE;
		}
		i++;
	}

	info.Insert(info.GetLength(), "\nCopyright ⓒ 2009 Microsoft Corporation, All rights reserved.");

	GetDlgItem(IDC_STATIC_OSVERSION_TEXT)->SetWindowText(info); //윈도우 정보를 적는다.

	return FALSE;
}

void InforMation::OnClose() {
	this->EndDialog(0);
}

RTL_OSVERSIONINFOW InforMation::GetRealOSVersion() {
	HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
	if (hMod) {
		RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
		if (fxPtr != nullptr) {
			RTL_OSVERSIONINFOW rovi = { 0 };
			rovi.dwOSVersionInfoSize = sizeof(rovi);
			if (STATUS_SUCCESS == fxPtr(&rovi)) {
				return rovi;
			}
		}
	}
	RTL_OSVERSIONINFOW rovi = { 0 };
	return rovi;
}

void InforMation::OnStnClickedStaticInformationText()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
