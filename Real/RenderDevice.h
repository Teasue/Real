#pragma once
#include "Vector2.h"
#include <windows.h>

class RenderDevice{
private:
	int mWidth;
	int mHeight;

	HWND mHWnd;
	HDC mHDC;
	HBITMAP		mBitMap;
	HBITMAP		mOldBitMap;
	LPVOID		mFrameBuffer;

public:
	RenderDevice() :mHWnd(NULL), mHDC(NULL), mBitMap(NULL), mOldBitMap(NULL), mWidth(800), mHeight(600) {};
	RenderDevice(int w, int h) :mHWnd(NULL), mHDC(NULL), mBitMap(NULL), mOldBitMap(NULL), mWidth(w), mHeight(h) {};
	~RenderDevice() {};


	bool IsKeyDown(int key);
	inline LPVOID GetFramebuffer() { return mFrameBuffer; }
	void Init(int w, int h);
	void Dispatch();
	void Update();
	void Close();
};

