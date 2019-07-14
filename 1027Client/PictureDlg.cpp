// PictureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1027Client.h"
#include "PictureDlg.h"
#include "afxdialogex.h"

// CPictureDlg �Ի���

IMPLEMENT_DYNAMIC(CPictureDlg, CDialogEx)

CPictureDlg::CPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPictureDlg::IDD, pParent)
{

}

CPictureDlg::~CPictureDlg()
{
}

void CPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPictureDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPictureDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPictureDlg ��Ϣ�������

extern 	CBitmap* pBitmap;


void CPictureDlg::OnBnClickedButton1()
{
	CRoomDlgg * pFrame = ((CMyDlgMain*)AfxGetMainWnd())->dlg;   
	static TCHAR BASED_CODE szFilter[] = _T("jpg (*.jpg)|*.jpg|")
		_T("png (*.png)|*.png|")
		_T("bmp (*.bmp)|*.bmp|");

	CFileDialog dlg(FALSE,L"jpg",L"δ����",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();

		CImage image;
		image.Attach((HBITMAP)(pBitmap->m_hObject));    //  �� image  װһ��ͼƬ
		if(image.Save(str) == S_OK)
		{
			this -> MessageBox(L"����ɹ�");
		}
		else
			this -> MessageBox(L"����ʧ��");
		image.Detach();  //  ����
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������

}



void CPictureDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	HWND mHwndShow = GetDlgItem(IDC_STATIC)->GetSafeHwnd();
	CWnd *pWnd = CWnd::FromHandle(mHwndShow);
	CRect rect;
	pWnd->GetClientRect(&rect);			//���pictrue�ؼ����ڵľ�������
	CDC *pDC = pWnd->GetDC();			//���pictrue�ؼ���DC
	if (pDC == NULL) return;
	/*��ʾm_bitmapCamͼƬ����*/
	CDC dcimage;
	dcimage.CreateCompatibleDC(pDC);	//�ڴ�DC
	BITMAP bmp;
	pBitmap->GetBitmap(&bmp);			//��ȡλͼ��Ϣ
	dcimage.SelectObject(pBitmap);	//ѡȡλͼ����
	/*��ʾ*/
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),&dcimage, 0, 0,bmp.bmWidth,bmp.bmHeight, SRCCOPY);
	pWnd->ReleaseDC(pDC);

}

void CPictureDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(IDOK);
	CDialogEx::OnClose();
}
