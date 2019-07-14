// PictureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1027Client.h"
#include "PictureDlg.h"
#include "afxdialogex.h"

// CPictureDlg 对话框

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


// CPictureDlg 消息处理程序

extern 	CBitmap* pBitmap;


void CPictureDlg::OnBnClickedButton1()
{
	CRoomDlgg * pFrame = ((CMyDlgMain*)AfxGetMainWnd())->dlg;   
	static TCHAR BASED_CODE szFilter[] = _T("jpg (*.jpg)|*.jpg|")
		_T("png (*.png)|*.png|")
		_T("bmp (*.bmp)|*.bmp|");

	CFileDialog dlg(FALSE,L"jpg",L"未命名",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();

		CImage image;
		image.Attach((HBITMAP)(pBitmap->m_hObject));    //  在 image  装一个图片
		if(image.Save(str) == S_OK)
		{
			this -> MessageBox(L"保存成功");
		}
		else
			this -> MessageBox(L"保存失败");
		image.Detach();  //  分离
	}

	// TODO: 在此添加控件通知处理程序代码

}



void CPictureDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	HWND mHwndShow = GetDlgItem(IDC_STATIC)->GetSafeHwnd();
	CWnd *pWnd = CWnd::FromHandle(mHwndShow);
	CRect rect;
	pWnd->GetClientRect(&rect);			//获得pictrue控件所在的矩形区域
	CDC *pDC = pWnd->GetDC();			//获得pictrue控件的DC
	if (pDC == NULL) return;
	/*显示m_bitmapCam图片内容*/
	CDC dcimage;
	dcimage.CreateCompatibleDC(pDC);	//内存DC
	BITMAP bmp;
	pBitmap->GetBitmap(&bmp);			//获取位图信息
	dcimage.SelectObject(pBitmap);	//选取位图对象
	/*显示*/
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),&dcimage, 0, 0,bmp.bmWidth,bmp.bmHeight, SRCCOPY);
	pWnd->ReleaseDC(pDC);

}

void CPictureDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDOK);
	CDialogEx::OnClose();
}
