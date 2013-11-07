//---------------------------------------------------------------------------

#ifndef MessagesH
#define MessagesH
//---------------------------------------------------------------------------
// Приходит от окна с видео и дает Handle в WParam в случае успеха
#define WM_INITVIDEO WM_USER+10
// Приходит от окна и дает номер дороги WParam и раастояние в LParam
// Visible 0x1 + Play 0x2
#define WM_VIDEOSTATUS WM_USER+11
// Устанавливает видео статус
// Visible 0x1 + Play 0x2 в LParam+ Handle(Road) WParam
#define WM_PUTPOSITION WM_USER+12

#define WM_CLOSEVIDEO WM_USER+13

#endif
