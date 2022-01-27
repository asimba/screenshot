#include <wchar.h>
#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

void ScreenCapture(){
  HDC hDc=CreateCompatibleDC(0);
  if(hDc){
    HDC hScrn=GetDC(0);
    int w=GetSystemMetrics(SM_CXSCREEN),h=GetSystemMetrics(SM_CYSCREEN);
    HBITMAP hBmp=CreateCompatibleBitmap(hScrn,w,h);
    if(hBmp){
      SelectObject(hDc,hBmp);
      BitBlt(hDc,0,0,w,h,hScrn,0,0,SRCCOPY);
      SYSTEMTIME tms;
      GetLocalTime(&tms);
      wchar_t path[MAX_PATH];
      swprintf(path,L".\\%04d%02d%02d%02d%02d%02d.png",
              tms.wYear,tms.wMonth,tms.wDay,tms.wHour,tms.wMinute,tms.wSecond);
      UINT num=0,size=0;
      ULONG_PTR gdiplusToken;
      GdiplusStartupInput gdiplusStartupInput;
      if(GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL)==Ok){
        GetImageEncodersSize(&num,&size);
        if(size){
          ImageCodecInfo* pImageCodecInfo=(ImageCodecInfo*)(malloc(size));
          if(pImageCodecInfo){
            GetImageEncoders(num,size,pImageCodecInfo);
            for(UINT j=0;j<num;j++){
              if(wcscmp(pImageCodecInfo[j].MimeType,L"image/png")==0){
                Bitmap *SrcBitmap=new Bitmap(hBmp,0);
                if(SrcBitmap){
                  SrcBitmap->Save(path,&pImageCodecInfo[j].Clsid,NULL);
                  delete SrcBitmap;
                };
                break;
              };
            };
            free(pImageCodecInfo);
          };
        };
        GdiplusShutdown(gdiplusToken);
      };
      DeleteObject(hBmp);
    };
    DeleteDC(hDc);
    ReleaseDC(NULL,hScrn);
  };
}

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){
  ScreenCapture();
  return 0;
}
