//---------------------------------------------------------------------------

#ifndef MessagesH
#define MessagesH
//---------------------------------------------------------------------------
// �������� �� ���� � ����� � ���� Handle � WParam � ������ ������
#define WM_INITVIDEO WM_USER+10
// �������� �� ���� � ���� ����� ������ WParam � ���������� � LParam
// Visible 0x1 + Play 0x2
#define WM_VIDEOSTATUS WM_USER+11
// ������������� ����� ������
// Visible 0x1 + Play 0x2 � LParam+ Handle(Road) WParam
#define WM_PUTPOSITION WM_USER+12

#define WM_CLOSEVIDEO WM_USER+13

#endif
