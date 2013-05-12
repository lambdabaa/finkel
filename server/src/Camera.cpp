
#include "Camera.h"


Camera::Camera() {
}


BITMAP Camera::TakeScreenshot(HWND windowHandle) {
  // Get the dimensions of the window.
  RECT rect;
  GetClientRect(windowHandle, &rect);

  // Setup the in memory device and bitmap handles.
  HDC deviceHandle = GetDC(NULL);
  HDC memDeviceHandle = CreateCompatibleDC(deviceHandle);
  HBITMAP bitmapHandle = CreateCompatibleBitmap(
    deviceHandle,
    rect.right - rect.left /** nWidth */,
    rect.bottom - rect.top /** nHeight */
  );
  SelectObject(memDeviceHandle, bitmapHandle);

  // Print window into memory.
  PrintWindow(windowHandle, memDeviceHandle, PW_CLIENTONLY);

  BITMAP bitmap;
  GetObject(bitmapHandle, sizeof(BITMAP), &bitmap);

  // Release memory.
  DeleteDC(memDeviceHandle);
  DeleteObject(bitmapHandle);
  ReleaseDC(NULL, deviceHandle);

  return bitmap;
}
