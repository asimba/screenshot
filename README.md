# screenshot
Simple Windows OS C++ screenshot code.  

---  
_**Build instructions (MinGW):**_ ```i686-w64-mingw32-g++ -Os -m32 -mwindows -march=i686 -mtune=generic -s -Wall -fmerge-constants -fno-exceptions -fno-builtin -fno-rtti -nostartfiles -Wl,--entry=_WinMain -Wl,--enable-stdcall-fixup -o screenshot.exe screenshot.cc -lgdi32 -lgdiplus```  
