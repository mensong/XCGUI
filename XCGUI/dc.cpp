/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


HBITMAP XDraw_CreateDIBSection(HDC hdc, int cx, int cy)
{
	void *pBits;
	BITMAPINFO info;
	memset(&info.bmiHeader, 0, sizeof(BITMAPINFOHEADER));
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biBitCount = 32;
	info.bmiHeader.biCompression = BI_RGB;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biWidth = cx;
	info.bmiHeader.biHeight = cy;
	return CreateDIBSection(hdc, &info, DIB_RGB_COLORS, &pBits, NULL, 0);
}


void WINAPI XDraw_FillSolidRect(HDC hdc, RECT *pRect, COLORREF clr)
{
	if (hdc)
	{
		::SetBkColor(hdc, clr);
		::ExtTextOut(hdc, 0, 0, ETO_OPAQUE, pRect, NULL, 0, NULL);
	}
}

BOOL WINAPI XDraw_GradientFill2(HDC hdc, COLORREF color1, COLORREF color2, RECT *pRect, int mode)
{
	BYTE r1 = GetRValue(color1);
	BYTE g1 = GetGValue(color1);
	BYTE b1 = GetBValue(color1);
	BYTE r2 = GetRValue(color2);
	BYTE g2 = GetGValue(color2);
	BYTE b2 = GetBValue(color2);

	if (GRADIENT_FILL_RECT_V == mode)  //垂直填充
	{
		TRIVERTEX  vert[2];
		vert[0].x = pRect->left;
		vert[0].y = pRect->top;
		vert[0].Red = r1 << 8;
		vert[0].Green = g1 << 8;
		vert[0].Blue = b1 << 8;
		vert[0].Alpha = 0;

		vert[1].x = pRect->right;
		vert[1].y = pRect->bottom;
		vert[1].Red = r2 << 8;
		vert[1].Green = g2 << 8;
		vert[1].Blue = b2 << 8;
		vert[1].Alpha = 0;

		GRADIENT_RECT  Crect[1];
		Crect[0].UpperLeft = 0;
		Crect[0].LowerRight = 1;
		return GradientFill(hdc, vert, 2, Crect, 1, GRADIENT_FILL_RECT_V);
	}
	else if (GRADIENT_FILL_RECT_H == mode)
	{
		TRIVERTEX  vert[2];
		vert[0].x = pRect->left;
		vert[0].y = pRect->top;
		vert[0].Red = r1 << 8;
		vert[0].Green = g1 << 8;
		vert[0].Blue = b1 << 8;
		vert[0].Alpha = 0;

		vert[1].x = pRect->right;
		vert[1].y = pRect->bottom;
		vert[1].Red = r2 << 8;
		vert[1].Green = g2 << 8;
		vert[1].Blue = b2 << 8;
		vert[1].Alpha = 0;

		GRADIENT_RECT  Crect[1];
		Crect[0].UpperLeft = 0;
		Crect[0].LowerRight = 1;
		return GradientFill(hdc, vert, 2, Crect, 1, GRADIENT_FILL_RECT_H);
	}
	return FALSE;
}

BOOL WINAPI XDraw_GradientFill4(HDC hdc, COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, RECT *pRect, int mode)
{
	BYTE r1 = GetRValue(color1);
	BYTE g1 = GetGValue(color1);
	BYTE b1 = GetBValue(color1);
	BYTE r2 = GetRValue(color2);
	BYTE g2 = GetGValue(color2);
	BYTE b2 = GetBValue(color2);
	BYTE r3 = GetRValue(color3);
	BYTE g3 = GetGValue(color3);
	BYTE b3 = GetBValue(color3);
	BYTE r4 = GetRValue(color4);
	BYTE g4 = GetGValue(color4);
	BYTE b4 = GetBValue(color4);

	if (GRADIENT_FILL_RECT_V == mode)  //垂直填充
	{
		int halfY = pRect->top + (pRect->bottom - pRect->top) / 2; //中间坐标
		TRIVERTEX  vert[4];
		vert[0].x = pRect->left;
		vert[0].y = pRect->top;
		vert[0].Red = r1 << 8;
		vert[0].Green = g1 << 8;
		vert[0].Blue = b1 << 8;
		vert[0].Alpha = 0;

		vert[1].x = pRect->right;
		vert[1].y = halfY;
		vert[1].Red = r2 << 8;
		vert[1].Green = g2 << 8;
		vert[1].Blue = b2 << 8;
		vert[1].Alpha = 0;

		vert[2].x = pRect->left;
		vert[2].y = halfY;
		vert[2].Red = r3 << 8;
		vert[2].Green = g3 << 8;
		vert[2].Blue = b3 << 8;
		vert[2].Alpha = 0;

		vert[3].x = pRect->right;
		vert[3].y = pRect->bottom;
		vert[3].Red = r4 << 8;
		vert[3].Green = g4 << 8;
		vert[3].Blue = b4 << 8;
		vert[3].Alpha = 0;

		GRADIENT_RECT  Crect[2];
		Crect[0].UpperLeft = 0;
		Crect[0].LowerRight = 1;

		Crect[1].UpperLeft = 2;
		Crect[1].LowerRight = 3;
		return GradientFill(hdc, vert, 4, Crect, 2, GRADIENT_FILL_RECT_V);
	}
	else if (GRADIENT_FILL_RECT_H == mode)
	{
		int halfX = pRect->left + (pRect->right - pRect->left) / 2; //中间坐标
		TRIVERTEX  vert[4];
		vert[0].x = pRect->left;
		vert[0].y = pRect->top;
		vert[0].Red = r1 << 8;
		vert[0].Green = g1 << 8;
		vert[0].Blue = b1 << 8;
		vert[0].Alpha = 0;

		vert[1].x = halfX;
		vert[1].y = pRect->bottom;
		vert[1].Red = r2 << 8;
		vert[1].Green = g2 << 8;
		vert[1].Blue = b2 << 8;
		vert[1].Alpha = 0;

		vert[2].x = halfX;
		vert[2].y = pRect->top;
		vert[2].Red = r3 << 8;
		vert[2].Green = g3 << 8;
		vert[2].Blue = b3 << 8;
		vert[2].Alpha = 0;

		vert[3].x = pRect->right;
		vert[3].y = pRect->bottom;
		vert[3].Red = r4 << 8;
		vert[3].Green = g4 << 8;
		vert[3].Blue = b4 << 8;
		vert[3].Alpha = 0;

		GRADIENT_RECT  Crect[2];
		Crect[0].UpperLeft = 0;
		Crect[0].LowerRight = 1;

		Crect[1].UpperLeft = 2;
		Crect[1].LowerRight = 3;
		return GradientFill(hdc, vert, 4, Crect, 2, GRADIENT_FILL_RECT_H);
	}
	return FALSE;
}

void XDraw_Dottedline(HDC hdc, int x, int y, int length, COLORREF color, BOOL bHorizontal)  //绘制虚线
{
	int len = length / 2;
	if (bHorizontal)
	{
		for (int i = 0; i < len; i++)
		{
			::SetPixel(hdc, x, y, color);
			x += 2;
		}
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			::SetPixel(hdc, x, y, color);
			y += 2;
		}
	}
}

void WINAPI XDraw_Check(HDC hdc, int x, int y, COLORREF color, BOOL bCheck)
{
	int top = y;
	int left = x;
	//绘制边框
	HPEN hPenBk = CreatePen(PS_SOLID, 1, color);
	HGDIOBJ hOld = SelectObject(hdc, hPenBk);
	Rectangle(hdc, left, top, left + 13, top + 13);
	SelectObject(hdc, hOld);
	DeleteObject(hPenBk);

	//绘制背景
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	LinearGradientBrush  brush(Rect(left + 1, top + 1, 10, 10), Color(180, 180, 180), Color(255, 255, 255), LinearGradientModeForwardDiagonal);
	graphics.FillRectangle(&brush, Rect(left + 1, top + 1, 10, 10));

	if (bCheck)
	{
		//绘制勾选
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(66, 100, 147));
		HGDIOBJ hOld = SelectObject(hdc, hPen);
		MoveToEx(hdc, left + 2, top + 6, NULL);
		LineTo(hdc, left + 5, top + 9);

		MoveToEx(hdc, left + 4, top + 9, NULL);
		LineTo(hdc, left + 10, top + 3);

		SelectObject(hdc, hOld);
		DeleteObject(hPen);
	}
}

Status XDraw_GraphicsDrawImage(HDC hdc, Image *image, int x, int y)
{
	Graphics graphics(hdc);
	Status status = graphics.DrawImage(image, x, y, image->GetWidth(), image->GetHeight());
	return status;
}

Status XDraw_GraphicsDrawImageEx(HDC hdc, Image *image, int x, int y, int width, int height)
{
	Graphics graphics(hdc);
	Status status = graphics.DrawImage(image, x, y, width, height);
	return status;
}

//不拉伸图片
//x:目标X
//y:目标Y
void WINAPI XDraw_HImage(HDC hdc, HIMAGE hImage, int x, int y)
{
	if (NULL == hdc) return;
	IsHImageDebug(hImage, __FUNCTION__);

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;

	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	if (!pImage->bTransparentColor)
	{
		Graphics graphics(hdc);
		graphics.DrawImage(pImageX, x, y, pImageX->GetWidth(), pImageX->GetHeight());
	}
	else
	{
		Graphics graphics(hdc);
		Rect destRect;
		destRect.X = x;
		destRect.Y = y;
		destRect.Width = pImageX->GetWidth();
		destRect.Height = pImageX->GetHeight();

		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);

		ImageAttributes ImgAtt;
		ImgAtt.SetRemapTable(1, &newToold);

		graphics.DrawImage(pImageX, destRect, 0, 0,
			pImageX->GetWidth(),
			pImageX->GetHeight(),
			UnitPixel, &ImgAtt);
	}
}

//拉伸贴图
//x:目标X
//y:目标Y
//height:目标宽度
//height:目标高度
void WINAPI XDraw_HImageStretch(HDC hdc, HIMAGE hImage, int x, int y, int width, int height)
{
	if (NULL == hdc) return;
	IsHImageDebug(hImage, __FUNCTION__);

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	ImageAttributes ImgAtt;
	if (pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1, &newToold);
	}

	Graphics graphics(hdc);
	Rect destRect;
	destRect.X = x;
	destRect.Y = y;
	destRect.Width = width;
	destRect.Height = height;

	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(pImageX, destRect, 0, 0,
		pImageX->GetWidth(),
		pImageX->GetHeight(),
		UnitPixel, &ImgAtt);
}

//根据图片属性,自动绘制:普通,拉伸,自适应图片
//pRect:目标坐标
void WINAPI XDraw_HImageSuper(HDC hdc, HIMAGE hImage, RECT *pRect)
{
	if (NULL == hdc) return;
	IsHImageDebug(hImage, __FUNCTION__);
	switch (XImage_GetDrawType(hImage))
	{
	case XC_IMAGE_DEFAULT:
		XDraw_HImage(hdc, hImage, pRect->left, pRect->top);
		break;
	case XC_IMAGE_STRETCH:
		XDraw_HImageStretch(hdc, hImage, pRect->left, pRect->top, pRect->right - pRect->left,
			pRect->bottom - pRect->top);
		break;
	case XC_IMAGE_ADAPTIVE:
		XDraw_HImageAdaptive(hdc, hImage, pRect);
		break;
	case XC_IMAGE_TILE:
		XDraw_HImageExTile(hdc, hImage, pRect);
		break;
	}
}

//绘制图片指定区域
void WINAPI XDraw_HImageEx(HDC hdc, HIMAGE hImage, int x, int y, int width, int height, int srcX, int srcY)
{
	Graphics graphics(hdc);

	Rect destRect;
	destRect.X = x;
	destRect.Y = y;
	destRect.Width = width;
	destRect.Height = height;

	ImageAttributes ImgAtt;

	ximage_  *pImage = (ximage_*)hImage;

	int srcWidth = width;
	int srcHeight = height;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	if (pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1, &newToold);
	}

	if (Gdiplus::Ok != graphics.DrawImage(pImageX,
		destRect,
		srcX,    //srcX
		srcY,       //srcY
		destRect.Width,   //cx
		destRect.Height,   //cy
		UnitPixel, &ImgAtt, NULL, NULL))
	{
		XTRACE("图片无效 \n");
	}
}

void WINAPI XDraw_HImageExTile(HDC hdc, HIMAGE hImage, RECT *pRect, int flag)
{
	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	RECT rect = *pRect;

	Graphics graphics(hdc);
	HRGN hRgn = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
	SelectClipRgn(hdc, hRgn);
	if (0 == flag)
	{
		int posx = rect.left;
		int posy = rect.top;
		int posx2 = posx;
		int posy2 = posy;
		int imageWidth = pImageX->GetWidth();
		int imageHeight = pImageX->GetHeight();

		while (posy2 < rect.bottom)
		{
			while (posx2 < rect.right)
			{
				XDraw_HImage(hdc, hImage, posx2, posy2);
				posx2 += imageWidth;
			}
			posx2 = posx;
			posy2 += imageHeight;
		}
	}
	else if (1 == flag)
	{
		int posx = rect.left;
		int posy = rect.bottom;
		int posx2 = posx;
		int posy2 = posy;
		int imageWidth = pImageX->GetWidth();
		int imageHeight = pImageX->GetHeight();

		while (posy2 > pRect->top)
		{
			posy2 -= imageHeight;
			while (posx2 < rect.right)
			{
				XDraw_HImage(hdc, hImage, posx2, posy2);
				posx2 += imageWidth;
			}
			posx2 = posx;
		}
	}
	DeleteObject(hRgn);
	SelectClipRgn(hdc, NULL);
}

void WINAPI XDraw_HImageAdaptive(HDC hdc, HIMAGE hImage, RECT *pRect)
{
	if (NULL == hdc) return;
	IsHImageDebug(hImage, __FUNCTION__);

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	int  rectWidth = pRect->right - pRect->left;
	int  rectHeight = pRect->bottom - pRect->top;

	RECT rect = *pRect;

	Graphics graphics(hdc);
	Rect destRect1, destRect2, destRect3, destRect4, destRect5, destRect6, destRect7, destRect8, destRect9;

	destRect1.X = rect.left;
	destRect1.Y = rect.top;
	destRect1.Width = pImage->imageX1;
	destRect1.Height = pImage->imageY1;

	destRect3.Y = rect.top;
	destRect3.Width = pImage->imageWidth - pImage->imageX2;
	destRect3.Height = pImage->imageY1;
	destRect3.X = rect.right - destRect3.Width;

	destRect2.X = rect.left + pImage->imageX1;
	destRect2.Y = rect.top;
	destRect2.Width = rectWidth - destRect1.Width - destRect3.Width;
	destRect2.Height = pImage->imageY1;

	destRect7.X = rect.left;
	destRect7.Width = pImage->imageX1;
	destRect7.Height = pImage->imageHeight - pImage->imageY2;
	destRect7.Y = rect.bottom - destRect7.Height;

	destRect4.X = rect.left;
	destRect4.Y = rect.top + pImage->imageY1;
	destRect4.Width = pImage->imageX1;
	destRect4.Height = rectHeight - destRect1.Height - destRect7.Height;

	destRect9.Height = destRect7.Height;
	destRect9.Width = destRect3.Width;
	destRect9.X = rect.right - destRect9.Width;
	destRect9.Y = rect.bottom - destRect9.Height;

	//6
	destRect6.Height = rectHeight - destRect3.Height - destRect9.Height;
	destRect6.Width = destRect3.Width;
	destRect6.X = rect.right - destRect6.Width;
	destRect6.Y = rect.top + pImage->imageY1;

	//8
	destRect8.X = rect.left + pImage->imageX1;
	destRect8.Height = destRect7.Height;
	destRect8.Width = destRect2.Width;
	destRect8.Y = rect.bottom - destRect8.Height;

	//5
	destRect5.X = rect.left + pImage->imageX1;
	destRect5.Y = rect.top + pImage->imageY1;
	destRect5.Height = destRect4.Height;
	destRect5.Width = destRect2.Width;

	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);

	if (pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1, &newToold);
	}

	//1
	if (destRect1.Width > 0 && destRect1.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect1,
			0,                //srcX
			0,                //srcY
			pImage->imageX1,  //cx
			pImage->imageY1,  //cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}

	//2
	if (destRect2.Width > 0 && destRect2.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect2,
			pImage->imageX1,  //srcX
			0,                //srcY
			pImage->imageX2 - pImage->imageX1,//cx
			pImage->imageY1,  //cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}

	//3
	if (destRect3.Width > 0 && destRect3.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect3,
			pImage->imageX2,   //srcX
			0,                 //srcY
			destRect3.Width,   //cx
			pImage->imageY1,   //cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}

	//4
	if (destRect4.Width > 0 && destRect4.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect4,
			0,                              //srcX
			pImage->imageY1,                //srcY
			pImage->imageX1,                //cx
			pImage->imageY2 - pImage->imageY1,//cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}
	//5
	if (destRect5.Width > 0 && destRect5.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect5,
			pImage->imageX1,                              //srcX
			pImage->imageY1,                //srcY
			pImage->imageX2 - pImage->imageX1,                //cx
			pImage->imageY2 - pImage->imageY1,//cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}
	//6
	if (destRect6.Width > 0 && destRect6.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect6,
			pImage->imageX2,         //srcX
			pImage->imageY1,         //srcY
			destRect6.Width,         //cx
			pImage->imageY2 - pImage->imageY1,//cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}
	//7
	if (destRect7.Width > 0 && destRect7.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect7,
			0,                       //srcX
			pImage->imageY2,         //srcY
			pImage->imageX1,         //cx
			destRect7.Height,        //cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}
	//8
	if (destRect7.Width > 0 && destRect7.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect8,
			pImage->imageX1,         //srcX
			pImage->imageY2,         //srcY
			pImage->imageX2 - pImage->imageX1,  //cx
			destRect8.Height,        //cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}
	//9
	if (destRect7.Width > 0 && destRect7.Height > 0)
	{
		if (Gdiplus::Ok != graphics.DrawImage(pImageX,
			destRect9,
			pImage->imageX2,         //srcX
			pImage->imageY2,         //srcY
			destRect9.Width,         //cx
			destRect9.Height,        //cy
			UnitPixel, &ImgAtt, NULL, NULL)) {
			XTRACE("图片无效 \n");
		}
	}
	//	BitBlt(hdc,pRect->left,pRect->top,rectWidth,rectHeight,memDC,0,0,SRCCOPY);
	//	DeleteDC(memDC);
	//	DeleteObject(memBM);
}

//GDI+ 绘制圆角矩形
GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded)
{
	//ASSERT (percentageRounded >= 1 && percentageRounded <= 100);

	INT left = min(topLeft.X, bottomRight.X);
	INT right = max(topLeft.X, bottomRight.X);

	INT top = min(topLeft.Y, bottomRight.Y);
	INT bottom = max(topLeft.Y, bottomRight.Y);

	INT offsetX = (right - left)*percentageRounded / 100;
	INT offsetY = (bottom - top)*percentageRounded / 100;

	GraphicsPath pt;
	GraphicsPath * path = pt.Clone();

	path->AddArc(right - offsetX, top, offsetX, offsetY, 270, 90);
	path->AddArc(right - offsetX, bottom - offsetY, offsetX, offsetY, 0, 90);
	path->AddArc(left, bottom - offsetY, offsetX, offsetY, 90, 90);
	path->AddArc(left, top, offsetX, offsetY, 180, 90);
	path->AddLine(left + offsetX, top, right - offsetX / 2, top);
	return path;
}

//GDI+绘制矩形阴影
void DrawShadow(Graphics &g, GraphicsPath *ButtonPath)
{
	g.SetPageUnit(UnitPixel); //设置Graphics的坐标单位为像素

	GraphicsPath &ShadowPath = *(ButtonPath->Clone());    //拷贝一个按钮区域路径的副本，用来生成阴影区域路径

	// 获得阴影区域
	Matrix ShadowMatrix;
	ShadowMatrix.Translate(5, 5);// 平移，ShadowSize即阴影延伸出来的像素数，这里是向右下方移动的，可以根据实际情况修改。
	ShadowPath.Transform(&ShadowMatrix);    // 应用矩阵

	Region ButtonRegion(ButtonPath);  //利用按钮的路径建立按钮区域
	Region ShadowRegion(&ShadowPath);  //利用阴影路径建立阴影的区域

	ShadowRegion.Exclude(&ButtonRegion); // 区域求差，这样就得出了纯粹的阴影区域，排除了阴影区域和按钮区域重合的部分。

	// 初始化渐变画刷
	PathGradientBrush brush(&ShadowPath);
	brush.SetCenterColor(Color(255, 0, 0, 0)); // 这里利用的是路径渐变画刷
	Color colors[] = { Color(0, 0, 0, 0) };
	int count = 1;
	brush.SetSurroundColors(colors, &count);
	brush.SetFocusScales(0.75f, 0.75f);  //对渐变效果进行调整，使其更加自然。这句的实际作用是对渐变效果进行缩放。参数是横纵两个坐标轴的缩放比例。

	g.FillRegion(&brush, &ShadowRegion);

	delete &ShadowPath; //别忘了删除Clone出来的副本。
}

void Draw_GetData(HDC hdc, bitmap_info_ &info)
{
	if (NULL == hdc) return;
	HBITMAP  hBitmap = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);

	BITMAP  bitmap;
	int res = GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	if (0 == res) return;

	if (bitmap.bmWidth < 1 || bitmap.bmHeight < 1)
		return;

	int bitSize = bitmap.bmWidth*bitmap.bmHeight * 4; //rcCli.right*rcCli.bottom*4;  //总大小
	int lenrow = bitmap.bmWidth * 4;     //rcCli.right*4; //行长度

	BYTE *pData = (BYTE*)malloc(bitSize);

	GetBitmapBits(hBitmap, bitSize, pData);

	info.hBitmap = hBitmap;
	info.data = pData;
	info.bitSize = bitSize;
	info.width = bitmap.bmWidth;
	info.height = bitmap.bmHeight;
}

void Draw_SetPixelValue(bitmap_info_ &info, int x, int y, COLORREF color)
{
	COLORREF *pArray = (COLORREF*)info.data;

	int pos = y*info.width + x;
	pArray[pos] = color;
}

//绘制直线或竖线
void Draw_DrawStraightLine(bitmap_info_ &info, int x1, int y1, int x2, int y2, COLORREF color)
{
	COLORREF *pArray = (COLORREF*)info.data;
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			int pos = y*info.width + x;
			pArray[pos] = color;
		}
	}
}

void Draw_SetData(bitmap_info_ &info)
{
	SetBitmapBits(info.hBitmap, info.bitSize, info.data);
	free(info.data);
}

void Draw_DrawShadowLine(HDC hdc, RECT *pRect, bitmap_info_ &info)
{
	BYTE color = 0;
	BYTE add[8] = { 4, 10, 20, 30, 60, 83,111, 255 };  //15
	for (int i = 0; i < 7; i++)
	{
		color = add[i];
		//左
		Draw_DrawStraightLine(info, pRect->left + i - 7, pRect->top + 5, pRect->left + i - 7, pRect->bottom - 5, RGBA(color, 0, 0, 0));
		//上
		Draw_DrawStraightLine(info, pRect->left + 5, pRect->top + i - 7, pRect->right - 5, pRect->top + i - 7, RGBA(color, 0, 0, 0));
		//右
		Draw_DrawStraightLine(info, pRect->right + 7 - i, pRect->top + 5, pRect->right + 7 - i, pRect->bottom - 7, RGBA(color, 0, 0, 0));
		//下
		Draw_DrawStraightLine(info, pRect->left + 5, pRect->bottom + 7 - i, pRect->right - 5, pRect->bottom + 7 - i, RGBA(color, 0, 0, 0));
	}
}//Draw_DrawShadowLine()

BYTE shadow_data[16][16] =
{  //0, 1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15
	{0, 0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  3,  3,  3,  4,  4},  //0
	{0, 0,  0,  0,  1,  1,  2,  3,  5,  6,  7,  8,  9,  10, 11, 10}, //1
	{0, 0,  1,  1,  2,  4,  5,  8,  10, 13, 15, 18, 20, 21, 22, 20}, //2
	{0, 0,  1,  3,  4,  7,  10, 14, 18, 23, 27, 30, 33, 36, 38, 30}, //3
	{0, 1,  2,  5,  8,  12, 17, 23, 29, 35, 41, 47, 51, 54, 57, 60}, //4
	{0, 2,  4,  7,  12, 18, 25, 33, 43, 51, 60, 67, 72, 77, 80, 83}, //5
	{1, 2,  6,  10, 17, 25, 35, 47, 59, 70, 81, 90, 98, 103,107,111}, //6
	{1, 3,  8,  14, 23, 34, 47, 62, 78, 255,255,255,255,255,255,255}, //7
	{1, 5,  10, 18, 29, 43, 59, 78, 255}, //8
	{2, 6,  13, 23, 36, 52, 71, 78, 255}, //9
	{2, 7,  15, 27, 42, 60, 81, 255}, //10
	{3, 8,  18, 31, 47, 67, 90, 255}, //11
	{3, 10, 20, 34, 51, 73, 98, 255}, //12
	{3, 10, 21, 36, 55, 77,104, 255}, //13
	{4, 11, 22, 38, 57, 80,108, 255}, //14
	{4, 10, 20, 30, 60, 83,111, 255}, //15
};
void Draw_DrawWndShadow(HDC hdc, RECT *pRect)
{
	RECT rect = *pRect;
	rect.right--;
	rect.bottom--;
	bitmap_info_ info;
	Draw_GetData(hdc, info);

	Draw_DrawShadowLine(hdc, &rect, info);

	BYTE color = 0;
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			color = shadow_data[x][y];
			if (255 == color)
				break;

			//左上角
			Draw_SetPixelValue(info, rect.left - 7 + x, rect.top - 7 + y, RGBA(color, 0, 0, 0));

			//左下角
			Draw_SetPixelValue(info, rect.left - 7 + x, rect.bottom + 7 - y, RGBA(color, 0, 0, 0));

			//右上角
			Draw_SetPixelValue(info, rect.right + 7 - x, rect.top - 7 + y, RGBA(color, 0, 0, 0));

			//右下角
			Draw_SetPixelValue(info, rect.right + 7 - x, rect.bottom + 7 - y, RGBA(color, 0, 0, 0));
		}
	}
	Draw_SetData(info);
}

///////////////////////////////////////////////////////////

void Draw_SetTransparent(HDC hdc, BYTE alpha)  //分层窗口 设置指定区域透明度
{
	if (NULL == hdc) return;
	HBITMAP  hBitmap = (HBITMAP)GetCurrentObject(hdc, OBJ_BITMAP);

	BITMAP  bitmap;
	int res = GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	if (0 == res) return;

	if (bitmap.bmWidth < 1 || bitmap.bmHeight < 1)
		return;

	int bitSize = bitmap.bmWidth*bitmap.bmHeight * 4; //总大小
	int lenrow = bitmap.bmWidth * 4;     //行长度

	BYTE *pBuf = (BYTE*)malloc(bitSize);

	GetBitmapBits(hBitmap, bitSize, pBuf);

	for (int i = 0; i < bitSize; i += 4)
	{
		pBuf[i + 3] = alpha;
	}

	SetBitmapBits(hBitmap, bitSize, pBuf);
	free(pBuf);
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

/// @defgroup xc_draw 图形绘制
/// @ingroup  groupOther
/// 图形绘制接口,支持画布偏移量设置,解决GDI兼容问题,以及预防GDI泄露,减少代码书写.\n
/// XDraw_Destroy_()销毁图形绘制模块实例句柄,当用户创建GDI对象(位图,画刷,字体,画笔)忘记销毁,图形绘制模块销毁时会自动帮用户销毁,防止GDI泄露,并且还原到初始状态.\n
/// XDraw_GetOffset_()还原初始状态,当用户调用该函数,还原到初始的状态,释放用户创建的GDI对象,恢复初始选定对象(位图,画刷,字体,画笔).
/// @{


/// @brief    创建图形绘制模块实例.
/// @param hdc  设备上下文句柄HDC.
/// @return  图形绘制模块实例句柄.
HDRAW WINAPI XDraw_Create_(HDC hdc) //创建
{
	if (NULL == hdc) return NULL;
	draw_xc_ *pDraw = (draw_xc_*)malloc(sizeof(draw_xc_));
	if (pDraw)
	{
		memset(pDraw, 0, sizeof(draw_xc_));
		pDraw->hdc = hdc;
		pDraw->hArrayTemp = XArray_Create();
		pDraw->object.type = XC_HDRAW;
		return (HDRAW)pDraw;
	}
	return NULL;
}

/// @brief    销毁图形绘制模块实例句柄.
/// @param hDraw  图形绘制句柄.
void  WINAPI XDraw_Destroy_(HDRAW hDraw) //销毁
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	XDraw_RestoreGDIOBJ_(hDraw);
	XArray_Destroy(pDraw->hArrayTemp);
	free(hDraw);
}

/// @brief  设置坐标偏移量,X向左偏移为负数,向右偏移为正数.
/// @param hDraw  图形绘制句柄.
/// @param x  X轴偏移量.
/// @param y  Y轴偏移量.
void  WINAPI XDraw_SetOffset_(HDRAW hDraw, int x, int y) //设置坐标偏移量
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	pDraw->x = x;
	pDraw->y = y;
}

/// @brief  获取坐标偏移量,X向左偏移为负数,向右偏移为正数.
/// @param hDraw  图形绘制句柄.
/// @param pX  接收X轴偏移量.
/// @param pY  接收Y轴偏移量.
void  WINAPI XDraw_GetOffset_(HDRAW hDraw, out_ int *pX, out_ int *pY) //获取坐标偏移量
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	*pX = pDraw->x;
	*pY = pDraw->y;
}

/// @brief 获取绑定的设备上下文HDC.
/// @param hDraw  图形绘制句柄.
/// @return 返回HDC句柄. 
HDC WINAPI XDraw_GetHDC_(HDRAW hDraw)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	return ((draw_xc_*)hDraw)->hdc;
}

/// @brief 还原状态,释放用户绑定的GDI对象,例如画刷,画笔.
/// @param hDraw  图形绘制句柄. 
void  WINAPI  XDraw_RestoreGDIOBJ_(HDRAW hDraw)  //还原状态,释放用户绑定的GDI对象
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;

	//还原绑定的GDI对象
	if (pDraw->OBJ_BITMAP_O)
	{
		SelectObject(pDraw->hdc, pDraw->OBJ_BITMAP_O);
		pDraw->OBJ_BITMAP_O = NULL;
	}
	if (pDraw->OBJ_BRUSH_O)
	{
		SelectObject(pDraw->hdc, pDraw->OBJ_BRUSH_O);
		pDraw->OBJ_BRUSH_O = NULL;
	}
	if (pDraw->OBJ_FONT_O)
	{
		SelectObject(pDraw->hdc, pDraw->OBJ_FONT_O);
		pDraw->OBJ_FONT_O = NULL;
	}
	if (pDraw->OBJ_PEN_O)
	{
		SelectObject(pDraw->hdc, pDraw->OBJ_PEN_O);
		pDraw->OBJ_PEN_O = NULL;
	}

	//释放临时创建的GDI对象
	int count = XArray_GetCount(pDraw->hArrayTemp);
	for (int i = 0; i < count; i++)
	{
		DeleteObject(XArray_GetAt(pDraw->hArrayTemp, i));
	}
	XArray_DeleteAll(pDraw->hArrayTemp);
}

/// @brief 设置文本绘制颜色.
/// @param hDraw  图形绘制句柄.
/// @param crColor RGB颜色值
/// @return 返回先前的颜色.
COLORREF WINAPI XDraw_SetTextColor_(HDRAW hDraw, COLORREF crColor)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	return SetTextColor(((draw_xc_*)hDraw)->hdc, crColor);
}

/// @brief 选择对象到指定的设备上下文（DC）,新的对象,取代以前的相同类型的对象.
/// @param hDraw  图形绘制句柄.
/// @param hObj GDI对象
/// @return 返回先前的GDI对象.
HGDIOBJ WINAPI XDraw_SelectObject_(HDRAW hDraw, HGDIOBJ hObj)
{
	IsDrawDebug(hDraw, __FUNCTION__);

	draw_xc_ *pDraw = (draw_xc_*)hDraw;

	DWORD type = GetObjectType(hObj);
	if (0 == type) return NULL;

	HGDIOBJ hResult = SelectObject(pDraw->hdc, hObj);

	switch (type)
	{
	case OBJ_BITMAP:
		if (NULL == pDraw->OBJ_BITMAP_O)
			pDraw->OBJ_BITMAP_O = hResult;
		else if (hObj == pDraw->OBJ_BITMAP_O)
			pDraw->OBJ_BITMAP_O = NULL;
		break;
	case OBJ_BRUSH:
		if (NULL == pDraw->OBJ_BRUSH_O)
			pDraw->OBJ_BRUSH_O = hResult;
		else if (hObj == pDraw->OBJ_BRUSH_O)
			pDraw->OBJ_BRUSH_O = NULL;
		break;
	case OBJ_FONT:
		if (NULL == pDraw->OBJ_FONT_O)
			pDraw->OBJ_FONT_O = hResult;
		else if (hObj == pDraw->OBJ_FONT_O)
			pDraw->OBJ_FONT_O = NULL;
		break;
	case OBJ_PEN:
		if (NULL == pDraw->OBJ_PEN_O)
			pDraw->OBJ_PEN_O = hResult;
		else if (hObj == pDraw->OBJ_PEN_O)
			pDraw->OBJ_PEN_O = NULL;
		break;
		//	case OBJ_REGION: break;
	}
	return hResult;
}

/// @brief 删除一个逻辑笔,画笔,字体,位图,区域,或调色板,释放与对象关联的所有系统资源,对象被删除后,指定的句柄不再有效.
/// @param hDraw  图形绘制句柄.
/// @param hObj GDI对象
/// @return 如果成功返回值是0.
BOOL WINAPI XDraw_DeleteObject_(HDRAW hDraw, HGDIOBJ hObj)
{
	IsDrawDebug(hDraw, __FUNCTION__);

	if (NULL == hObj) return FALSE;

	draw_xc_ *pDraw = (draw_xc_*)hDraw;

	HGDIOBJ hTemp = NULL;
	int count = XArray_GetCount(pDraw->hArrayTemp);
	for (int i = 0; i < count; i++)
	{
		hTemp = (HGDIOBJ)XArray_GetAt(pDraw->hArrayTemp, i);
		if (hTemp == hObj)
		{
			XArray_DeleteIndex(pDraw->hArrayTemp, i);
			break;
		}
	}
	return DeleteObject(hObj);
}

/// @brief 选择一个区域作为当前裁剪区域.
/// @param hDraw  图形绘制句柄.
/// @param hRgn  区域句柄.
/// @return 返回值指定地区的复杂性，可以是下列值之一.\n
/// NULLREGION Region is empty.\n
/// SIMPLEREGION Region is a single rectangle.\n
/// COMPLEXREGION Region is more than one rectangle.\n
/// ERROR An error occurred. (The previous clipping region is unaffected).
int WINAPI XDraw_SelectClipRgn_(HDRAW hDraw, HRGN hRgn)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	return SelectClipRgn(pDraw->hdc, hRgn);
}

/// @brief 创建具有指定的纯色逻辑刷.
/// @param hDraw  图形绘制句柄.
/// @param crColor 画刷颜色.
/// @return 如果函数成功,返回值标识一个逻辑刷,如果函数失败,返回值是NULL.
HBRUSH WINAPI XDraw_CreateSolidBrush_(HDRAW hDraw, COLORREF crColor)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	HBRUSH hBrush = CreateSolidBrush(crColor);
	if (hBrush)
	{
		XArray_Add(pDraw->hArrayTemp, hBrush);
		return hBrush;
	}
	return NULL;
}

/// @brief 创建一个逻辑笔,有指定的样式,宽度和颜色,随后的笔可以选择到设备上下文,用于绘制线条和曲线.
/// @param hDraw  图形绘制句柄.
/// @param fnPenStyle 画笔颜色.
/// @param nWidth 画笔宽度.
/// @param crColor 颜色.
/// @return 如果函数成功,返回值是一个句柄,标识一个逻辑笔,如果函数失败,返回值是NULL.
HPEN WINAPI XDraw_CreatePen_(HDRAW hDraw, int fnPenStyle, int nWidth, COLORREF crColor)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	HPEN hPen = CreatePen(fnPenStyle, nWidth, crColor);
	if (hPen)
	{
		XArray_Add(pDraw->hArrayTemp, hPen);
		return hPen;
	}
	return NULL;
}

/// @brief 创建一个圆角的矩形区域.
/// @param hDraw  图形绘制句柄.
/// @param nLeftRect   X-坐标的左上角.
/// @param nTopRect    Y-坐标左上角坐标
/// @param nRightRect  X-坐标右下角
/// @param nBottomRect Y-坐标右下角
/// @param nWidthEllipse   椭圆的宽度.
/// @param nHeightEllipse  椭圆的高度.
/// @return 如果函数成功,返回值是该区域的句柄,如果函数失败,返回值是NULL.
HRGN WINAPI XDraw_CreateRoundRectRgn_(HDRAW hDraw, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidthEllipse, int nHeightEllipse)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;

	HRGN hRgn = CreateRoundRectRgn(nLeftRect + pDraw->x, nTopRect + pDraw->y, nRightRect + pDraw->x, nBottomRect + pDraw->y, nWidthEllipse, nHeightEllipse);
	if (hRgn)
	{
		XArray_Add(pDraw->hArrayTemp, hRgn);
		return hRgn;
	}
	return NULL;
}

/// @brief 创建一个多边形区域.
/// @param hDraw 图形绘制句柄.
/// @param pPt  POINT数组.
/// @param cPoints 数组大小.
/// @param fnPolyFillMode 多边形填充模式,指定用于确定在该地区的像素填充模式,这个参数可以是下列值之一.\n
///  ALTERNATE Selects alternate mode (fills area between odd-numbered and even-numbered polygon sides on each scan line).\n
///  WINDING Selects winding mode (fills any region with a nonzero winding value).
/// @return  如果函数成功,返回值是该区域的句柄,如果函数失败,返回值是NULL.
HRGN WINAPI XDraw_CreatePolygonRgn_(HDRAW hDraw, POINT *pPt, int cPoints, int fnPolyFillMode)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	for (int i = 0; i < cPoints; i++)
	{
		pPt[i].x += pDraw->x;
		pPt[i].y += pDraw->y;
	}
	HRGN hRgn = CreatePolygonRgn(pPt, cPoints, fnPolyFillMode);
	if (hRgn)
	{
		XArray_Add(pDraw->hArrayTemp, hRgn);
		return hRgn;
	}
	return NULL;
}
/// @brief 通过使用指定的刷子填充一个矩形,此功能包括左侧和顶部的边界,但不包括矩形的右边和底部边界.
/// @param hDraw 图形绘制句柄.
/// @param pRect 矩形区域.
/// @param hbr 画刷句柄.
/// @return 如果函数成功,返回非零值,如果函数失败,返回值是零.
int WINAPI XDraw_FillRect_(HDRAW hDraw, RECT *pRect, HBRUSH hbr)
{
	IsDrawDebug(hDraw, __FUNCTION__);

	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rc = *pRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;

	return FillRect(pDraw->hdc, &rc, hbr);
}
/// @brief 通过使用指定的画刷填充一个区域.
/// @param hDraw 图形绘制句柄.
/// @param hrgn 区域句柄.
/// @param hbr 画刷句柄.
/// @return 如果函数成功,返回非零值,如果函数失败,返回值是零.
BOOL WINAPI XDraw_FillRgn_(HDRAW hDraw, HRGN hrgn, HBRUSH hbr)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	return FillRgn(((draw_xc_*)hDraw)->hdc, hrgn, hbr);
}

/// @brief 填充指定矩形,使用给定的颜色.
/// @param hDraw 图形绘制句柄.
/// @param pRect 矩形区域
/// @param clr   RGB颜色.
void WINAPI XDraw_FillSolidRect_(HDRAW hDraw, RECT *pRect, COLORREF clr)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rc = *pRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;

	::SetBkColor(pDraw->hdc, clr);
	::ExtTextOut(pDraw->hdc, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
}

/// @brief 渐变填充,从一种颜色过渡到另一种颜色.
/// @param hDraw 图形绘制句柄.
/// @param color1 开始颜色.
/// @param color2 结束颜色.
/// @param pRect 矩形坐标.
/// @param mode  模式.
/// GRADIENT_FILL_RECT_H 水平填充 .
/// GRADIENT_FILL_RECT_V 垂直填充.
/// GRADIENT_FILL_TRIANGLE 三角形.
/// @return 如果函数成功，返回值为TRUE,如果函数失败,返回值是FALSE.
BOOL WINAPI XDraw_GradientFill2_(HDRAW hDraw, COLORREF color1, COLORREF color2, RECT *pRect, int mode)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rc = *pRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;

	return XDraw_GradientFill2(pDraw->hdc, color1, color2, &rc, mode);
}

/// @brief 渐变填充,从一种颜色过渡到另一种颜色.
/// @param hDraw 图形绘制句柄.
/// @param color1 开始颜色.
/// @param color2 结束颜色,中间.
/// @param color3 开始颜色,中间.
/// @param color4 结束颜色.
/// @param pRect 矩形坐标.
/// @param mode  模式.
/// GRADIENT_FILL_RECT_H 水平填充. 
/// GRADIENT_FILL_RECT_V 垂直填充.
/// GRADIENT_FILL_TRIANGLE 三角形.
/// @return 如果函数成功，返回值为TRUE,如果函数失败,返回值是FALSE.
BOOL WINAPI XDraw_GradientFill4_(HDRAW hDraw, COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, RECT *pRect, int mode)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rc = *pRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;

	return XDraw_GradientFill4(((draw_xc_*)hDraw)->hdc, color1, color2, color3, color4, &rc, mode);
}

/// @brief 绘制边框,使用指定的画刷绘制指定的区域的边框.
/// @param hDraw 图形绘制句柄.
/// @param hrgn 区域句柄.
/// @param hbr  画刷句柄.
/// @param nWidth 边框宽度,垂直边.
/// @param nHeight 边框高度,水平边.
/// @return 如果函数成功,返回非零值,如果函数失败,返回值是零.
BOOL WINAPI XDraw_FrameRgn_(HDRAW hDraw, HRGN hrgn, HBRUSH hbr, int nWidth, int nHeight)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	return FrameRgn(((draw_xc_*)hDraw)->hdc, hrgn, hbr, nWidth, nHeight);
}

/// @brief 绘制矩形边框,使用指定的画刷.
/// @param hDraw 图形绘制句柄.
/// @param pRect 矩形坐标
/// @param hbr 画刷句柄.
/// @return  如果函数成功,返回非零值,如果函数失败,返回值是零.
int WINAPI XDraw_FrameRect_(HDRAW hDraw, RECT *pRect, HBRUSH hbr)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rc = *pRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;
	return FrameRect(((draw_xc_*)hDraw)->hdc, &rc, hbr);
}

/// @brief 绘制焦点矩形.
/// @param hDraw 图形绘制句柄.
/// @param pRect 矩形坐标.
/// @return 不使用.
BOOL WINAPI XDraw_FocusRect_(HDRAW hDraw, RECT *pRect)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;

	RECT rc = *pRect;

	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;

	XDraw_Dottedline(pDraw->hdc, rc.left, rc.top, rc.right - rc.left, RGB(0, 0, 0));
	XDraw_Dottedline(pDraw->hdc, rc.left, rc.bottom - 1, rc.right - rc.left, RGB(0, 0, 0));

	XDraw_Dottedline(pDraw->hdc, rc.left, rc.top, rc.bottom - rc.top, RGB(0, 0, 0), FALSE);
	XDraw_Dottedline(pDraw->hdc, rc.right - 1, rc.top, rc.bottom - rc.top, RGB(0, 0, 0), FALSE);

	return TRUE;
}

/// @brief 绘制矩形,使用当前的画刷和画笔.
/// @param hDraw 图形绘制句柄.
/// @param nLeftRect 左上角X坐标.
/// @param nTopRect  左上角Y坐标.
/// @param nRightRect 右下角X坐标.
/// @param nBottomRect  右下角Y坐标.
/// @return 如果函数成功,返回非零值,如果函数失败,返回值是零.
BOOL WINAPI XDraw_Rectangle_(HDRAW hDraw, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	return Rectangle(pDraw->hdc, nLeftRect + pDraw->x, nTopRect + pDraw->y, nRightRect + pDraw->x, nBottomRect + pDraw->y);
}

/// @brief 更新当前位置到指定点，并返回以前的位置。
/// @param hDraw 图形绘制句柄.
/// @param X 坐标.
/// @param Y 坐标.
/// @param lpPoint 接收以前的当前位置到一个POINT结构的指针,如果这个参数是NULL指针,没有返回原来的位置.
/// @return 如果函数成功,返回非零值,如果函数失败,返回值是零.
BOOL WINAPI XDraw_MoveToEx_(HDRAW hDraw, int X, int Y, LPPOINT lpPoint)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	return MoveToEx(((draw_xc_*)hDraw)->hdc, X + pDraw->x, Y + pDraw->y, lpPoint);
}

/// @brief 函数绘制一条线从当前位置到,但不包括指定点.
/// @param hDraw 图形绘制句柄.
/// @param nXEnd X坐标,线结束点.
/// @param nYEnd Y坐标,线结束点.
/// @return  如果函数成功,返回非零值,如果函数失败,返回值是零.
BOOL WINAPI XDraw_LineTo_(HDRAW hDraw, int nXEnd, int nYEnd)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	return LineTo(((draw_xc_*)hDraw)->hdc, nXEnd + pDraw->x, nYEnd + pDraw->y);
}

/// @brief 绘制复选框.
/// @param hDraw 图形绘制句柄.
/// @param x  坐标.
/// @param y  坐标.
/// @param color 边框颜色.
/// @param bCheck 是否选中状态.
void WINAPI XDraw_Check_(HDRAW hDraw, int x, int y, COLORREF color, BOOL bCheck)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	XDraw_Check(((draw_xc_*)hDraw)->hdc, x + ((draw_xc_*)hDraw)->x, y + ((draw_xc_*)hDraw)->y, color, bCheck);
}


void WINAPI XDraw_Dottedline_(HDRAW hDraw, int x, int y, int length, COLORREF color, BOOL bHorizontal) //绘制虚线
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	XDraw_Dottedline(pDraw->hdc, x + pDraw->x, y + pDraw->y, length, color, bHorizontal); //绘制虚线
}

/// @brief 函数设置在指定的坐标到指定的颜色的像素.
/// @param hDraw 图形绘制句柄.
/// @param X 坐标
/// @param Y 坐标
/// @param crColor RGB颜色值
/// @return 如果函数成功返回RGB值,如果失败返回-1.
COLORREF WINAPI XDraw_SetPixel_(HDRAW hDraw, int X, int Y, COLORREF crColor)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	return SetPixel(pDraw->hdc, X + pDraw->x, Y + pDraw->y, crColor);
}

/// @brief 参见MSDN.
/// @param hDraw 图形绘制句柄.
/// @param xLeft
/// @param yTop
/// @param hIcon
/// @param cxWidth
/// @param cyWidth
/// @param istepIfAniCur
/// @param hbrFlickerFreeDraw
/// @param diFlags
/// @return 
BOOL WINAPI XDraw_DrawIconEx_(HDRAW hDraw, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	return DrawIconEx(((draw_xc_*)hDraw)->hdc, xLeft + ((draw_xc_*)hDraw)->x, yTop + ((draw_xc_*)hDraw)->y, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags);
}

/// @brief 参见MSDN.
/// @param hDrawDest 图形绘制句柄.
/// @param nXDest
/// @param nYDest
/// @param nWidth
/// @param nHeight
/// @param hdcSrc
/// @param nXSrc
/// @param nYSrc
/// @param dwRop
/// @return 
BOOL WINAPI XDraw_BitBlt_(HDRAW hDrawDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
	IsDrawDebug(hDrawDest, __FUNCTION__);
	return BitBlt(((draw_xc_*)hDrawDest)->hdc, nXDest + ((draw_xc_*)hDrawDest)->x, nYDest + ((draw_xc_*)hDrawDest)->y, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
}

/// @brief 参见MSDN.
/// @param hDrawDest 图形绘制句柄.
/// @param nXDest
/// @param nYDest
/// @param nWidth
/// @param nHeight
/// @param hDrawSrc
/// @param nXSrc
/// @param nYSrc
/// @param dwRop
/// @return 
BOOL WINAPI XDraw_BitBlt2_(HDRAW hDrawDest, int nXDest, int nYDest, int nWidth, int nHeight, HDRAW hDrawSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
	IsDrawDebug(hDrawDest, __FUNCTION__);
	draw_xc_ *pDraw1 = (draw_xc_*)hDrawDest;
	draw_xc_ *pDraw2 = (draw_xc_*)hDrawSrc;
	return BitBlt(((draw_xc_*)hDrawDest)->hdc, nXDest + pDraw1->x, nYDest + pDraw1->y,
		nWidth, nHeight, pDraw2->hdc, nXSrc + pDraw2->x, nYSrc + pDraw2->y, dwRop);
}

/// @brief 绘制三角型箭头.
/// @param hDraw 图形绘制句柄.
/// @param hBrush 画刷.
/// @param align  箭头方向,左1,上2,右3,下4.
/// @param x 中心点X坐标.
/// @param y 中心点Y坐标.
/// @param width 三角形宽度.
/// @param height 三角形高度.
void WINAPI XDraw_TriangularArrow(HDRAW hDraw, HBRUSH hBrush, int align, int x, int y, int width, int height)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	int left = x + pDraw->x;
	int top = y + pDraw->y;

	if (1 == align) //left
	{
		POINT  pt[3];
		pt[0].x = left - (width / 2);
		pt[0].y = top;
		pt[1].x = left + (width / 2);
		pt[1].y = top + (height / 2);
		pt[2].x = left + (width / 2);
		pt[2].y = top - (height / 2);
		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		XDraw_FillRgn_(hDraw, hRgn, hBrush);
		XDraw_DeleteObject_(hDraw, hRgn);
	}
	else if (2 == align) //top
	{
		POINT  pt[3];
		pt[0].x = left - (width / 2);
		pt[0].y = top + (height / 2);
		pt[1].x = left + (width / 2);
		pt[1].y = top + (height / 2);
		pt[2].x = left;
		pt[2].y = top - (height / 2);
		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		XDraw_FillRgn_(hDraw, hRgn, hBrush);
		XDraw_DeleteObject_(hDraw, hRgn);
	}
	else if (3 == align) //right
	{
		POINT  pt[3];
		pt[0].x = left - (width / 2);
		pt[0].y = top - (height / 2);
		pt[1].x = left - (width / 2);
		pt[1].y = top + (height / 2);
		pt[2].x = left + (width / 2);
		pt[2].y = top;
		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		XDraw_FillRgn_(hDraw, hRgn, hBrush);
		XDraw_DeleteObject_(hDraw, hRgn);
	}
	else if (4 == align) //bottom
	{
		POINT  pt[3];
		pt[0].x = left - (width / 2);
		pt[0].y = top - (height / 2);
		pt[1].x = left;
		pt[1].y = top + (height / 2);
		pt[2].x = left + (width / 2);
		pt[2].y = top - (height / 2);
		HRGN hRgn = XDraw_CreatePolygonRgn_(hDraw, pt, 3, ALTERNATE);
		XDraw_FillRgn_(hDraw, hRgn, hBrush);
		XDraw_DeleteObject_(hDraw, hRgn);
	}
}

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param x
/// @param y
/// @return 
void WINAPI XDraw_HImage_(HDRAW hDraw, HIMAGE hImage, int x, int y)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	IsHImageDebug(hImage, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	x += pDraw->x;
	y += pDraw->y;

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;

	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	if (!pImage->bTransparentColor)
	{
		Graphics graphics(pDraw->hdc);
		graphics.DrawImage(pImageX, x, y, pImageX->GetWidth(), pImageX->GetHeight());
	}
	else
	{
		Graphics graphics(pDraw->hdc);
		Rect destRect;
		destRect.X = x;
		destRect.Y = y;
		destRect.Width = pImageX->GetWidth();
		destRect.Height = pImageX->GetHeight();

		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);

		ImageAttributes ImgAtt;
		ImgAtt.SetRemapTable(1, &newToold);

		graphics.DrawImage(pImageX, destRect, 0, 0,
			pImageX->GetWidth(),
			pImageX->GetHeight(),
			UnitPixel, &ImgAtt);
	}
}

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param x
/// @param y
/// @param width
/// @param height
void WINAPI XDraw_HImage2_(HDRAW hDraw, HIMAGE hImage, int x, int y, int width, int height)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	IsHImageDebug(hImage, __FUNCTION__);

	x += ((draw_xc_*)hDraw)->x;
	y += ((draw_xc_*)hDraw)->y;

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	ImageAttributes ImgAtt;
	if (pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1, &newToold);
	}

	Graphics graphics(((draw_xc_*)hDraw)->hdc);
	Rect destRect;
	destRect.X = x;
	destRect.Y = y;
	destRect.Width = width;
	destRect.Height = height;

	//ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(pImageX, destRect, 0, 0,
		width,
		height,
		UnitPixel, &ImgAtt);
}

//拉伸贴图
//x:目标X
//y:目标Y
//height:目标宽度
//height:目标高度

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param x
/// @param y
/// @param width
/// @param height
void WINAPI XDraw_HImageStretch_(HDRAW hDraw, HIMAGE hImage, int x, int y, int width, int height)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	if (NULL == hDraw) return;
	IsHImageDebug(hImage, __FUNCTION__);

	x += ((draw_xc_*)hDraw)->x;
	y += ((draw_xc_*)hDraw)->y;

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	ImageAttributes ImgAtt;
	if (pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1, &newToold);
	}

	Graphics graphics(((draw_xc_*)hDraw)->hdc);
	Rect destRect;
	destRect.X = x;
	destRect.Y = y;
	destRect.Width = width;
	destRect.Height = height;

	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(pImageX, destRect, 0, 0,
		pImageX->GetWidth(),
		pImageX->GetHeight(),
		UnitPixel, &ImgAtt);
}

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param pRect
void WINAPI XDraw_HImageAdaptive_(HDRAW hDraw, HIMAGE hImage, RECT *pRect)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rc = *pRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;

	XDraw_HImageAdaptive(((draw_xc_*)hDraw)->hdc, hImage, &rc);
}

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param pRect
/// @param flag
void WINAPI XDraw_HImageExTile_(HDRAW hDraw, HIMAGE hImage, RECT *pRect, int flag)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	RECT rect = *pRect;

	Graphics graphics(pDraw->hdc);
	HRGN hRgn = CreateRectRgn(rect.left + pDraw->x, rect.top + pDraw->y, rect.right + pDraw->x, rect.bottom + pDraw->y);
	SelectClipRgn(pDraw->hdc, hRgn);
	if (0 == flag)
	{
		int posx = rect.left;
		int posy = rect.top;
		int posx2 = posx;
		int posy2 = posy;
		int imageWidth = pImageX->GetWidth();
		int imageHeight = pImageX->GetHeight();

		while (posy2 < rect.bottom)
		{
			while (posx2 < rect.right)
			{
				XDraw_HImage_(hDraw, hImage, posx2, posy2);
				posx2 += imageWidth;
			}
			posx2 = posx;
			posy2 += imageHeight;
		}
	}
	else if (1 == flag)
	{
		int posx = rect.left;
		int posy = rect.bottom;
		int posx2 = posx;
		int posy2 = posy;
		int imageWidth = pImageX->GetWidth();
		int imageHeight = pImageX->GetHeight();

		while (posy2 > pRect->top)
		{
			posy2 -= imageHeight;
			while (posx2 < rect.right)
			{
				XDraw_HImage_(hDraw, hImage, posx2, posy2);
				posx2 += imageWidth;
			}
			posx2 = posx;
		}
	}
	DeleteObject(hRgn);
	SelectClipRgn(pDraw->hdc, NULL);
}

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param pRect
void WINAPI XDraw_HImageSuper_(HDRAW hDraw, HIMAGE hImage, RECT *pRect)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	IsHImageDebug(hImage, __FUNCTION__);
	switch (XImage_GetDrawType(hImage))
	{
	case XC_IMAGE_DEFAULT:
		XDraw_HImage_(hDraw, hImage, pRect->left, pRect->top);
		break;
	case XC_IMAGE_STRETCH:
		XDraw_HImageStretch_(hDraw, hImage, pRect->left, pRect->top, pRect->right - pRect->left,
			pRect->bottom - pRect->top);
		break;
	case XC_IMAGE_ADAPTIVE:
		XDraw_HImageAdaptive_(hDraw, hImage, pRect);
		break;
	case XC_IMAGE_TILE:
		//XDraw_HImageExTile_(hDraw,hImage,pRect->left,pRect->top,pRect->right-pRect->left,
		//	pRect->bottom-pRect->top);
		XDraw_HImageExTile_(hDraw, hImage, pRect, 0);
		break;
	}
}

/// @brief 绘制图片.
/// @param hDraw 图形绘制句柄.
/// @param hImage
/// @param pRcDest
/// @param pSrcRect
void WINAPI XDraw_HImageSuper2_(HDRAW hDraw, HIMAGE hImage, RECT *pRcDest, RECT *pSrcRect)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	if (NULL == hDraw) return;
	IsHImageDebug(hImage, __FUNCTION__);

	ximage_  *pImage = (ximage_*)hImage;

	Gdiplus::Image *pImageX = NULL;
	if (pImage->pImage)
	{
		pImageX = pImage->pImage;
	}
	else if (pImage->bBitmap && pImage->pBitmap)
	{
		pImageX = pImage->pBitmap;
	}

	if (NULL == pImageX) return;

	draw_xc_ *pDraw = (draw_xc_*)hDraw;

	RECT rcDest = *pRcDest;
	RECT rcSrc = *pSrcRect;

	rcDest.left += pDraw->x;
	rcDest.right += pDraw->x;
	rcDest.top += pDraw->y;
	rcDest.bottom += pDraw->y;

	ImageAttributes ImgAtt;
	if (pImage->bTransparentColor)
	{
		ColorMap   newToold;
		newToold.oldColor = pImage->transparentColor;
		newToold.newColor = Color(0, 255, 255, 255);
		ImgAtt.SetRemapTable(1, &newToold);
	}

	Graphics graphics(((draw_xc_*)hDraw)->hdc);

	Rect destRect;
	destRect.X = rcDest.left;
	destRect.Y = rcDest.top;
	destRect.Width = rcDest.right - rcDest.left;
	destRect.Height = rcDest.bottom - rcDest.top;

	graphics.DrawImage(pImageX, destRect, rcSrc.left, rcSrc.top,
		rcSrc.right - rcSrc.left,
		rcSrc.bottom - rcSrc.top,
		UnitPixel, &ImgAtt);
}

/// @brief 绘制文本,参见MSDN.
/// @param hDraw 图形绘制句柄.
/// @param lpString
/// @param nCount
/// @param lpRect
/// @param uFormat
int WINAPI XDraw_DrawText_(HDRAW hDraw, wchar_t * lpString, int nCount, RECT* lpRect, UINT uFormat)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	if (uFormat & DT_CALCRECT)
	{
		return DrawText(pDraw->hdc, lpString, nCount, lpRect, uFormat);
	}

	RECT rc = *lpRect;
	rc.left += pDraw->x;
	rc.right += pDraw->x;
	rc.top += pDraw->y;
	rc.bottom += pDraw->y;
	return DrawText(pDraw->hdc, lpString, nCount, &rc, uFormat);
}

/// @brief 绘制文本,参见MSDN.
/// @param hDraw 图形绘制句柄.
/// @param nXStart
/// @param nYStart
/// @param lpString
/// @param cbString
/// @return
BOOL WINAPI XDraw_TextOut_(HDRAW hDraw, int nXStart, int nYStart, wchar_t * lpString, int cbString)
{
	IsDrawDebug(hDraw, __FUNCTION__);
	draw_xc_ *pDraw = (draw_xc_*)hDraw;
	return TextOut(pDraw->hdc, nXStart + pDraw->x, nYStart + pDraw->y, lpString, cbString);
}

///@}

