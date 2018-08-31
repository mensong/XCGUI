/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


struct button_  //按钮
{
	ele_  ele; //继承
	//--------------------
	HSTRING hString;  //文本
	int    state;     //状态
	BOOL   bCheck;    //勾选
	BOOL   bDown;
	int    textFlag; //文本对齐
	BOOL   bCursorHand; //鼠标停留,光标变为手型
	POINT  offset;   //内容偏移量

	HIMAGE hImage_leave;
	HIMAGE hImage_stay;
	HIMAGE hImage_down;
	HIMAGE hImage_check;
	HIMAGE hImage_disable;

	HIMAGE hImage_icon; //图标
	int    iconAlign;  //图标对齐方式

	//动态按钮
	BOOL   bAnimation;       //启用或关闭
	button_animation_group_  *pAnimation;  //动态图片数组 button_animation_group_
};

//API:
/// @defgroup button 按钮(Button)
/// @ingroup  groupElements
/// 按钮接口列表
/// @{


/// @brief    创建按钮元素
/// @param x  按钮x坐标
/// @param y  按钮y坐标
/// @param cx 宽度
/// @param cy 高度
/// @param pTitle  标题
/// @param hParent 父是窗口句柄或元素句柄.
/// @return 按钮元素句柄.
XC_API HELE WINAPI XBtn_Create(int x, int y, int cx, int cy, wchar_t *pTitle = NULL, HXCGUI hParent = NULL);  //创建按钮

/// @brief 获取按钮元素文本内容
/// @param hEle 元素句柄
/// @return 文本内容
XC_API wchar_t * WINAPI XBtn_GetText(HELE hEle);  //获取文本

/// @brief 设置按钮文本内容.
/// @param hEle 元素句柄
/// @param pText 文本内容
XC_API void  WINAPI XBtn_SetText(HELE hEle, wchar_t *pText);

/// @brief 设置按钮选中状态
/// @param hEle 元素句柄
/// @param bCheck TRUE选中,否则相反
XC_API void WINAPI XBtn_SetCheck(HELE hEle, BOOL bCheck);

/// @brief 判断按钮是否为选中状态.
/// @param hEle 元素句柄
/// @return  如果按钮选中状态返回TRUE,否则相反.
XC_API BOOL WINAPI XBtn_IsCheck(HELE hEle); //按钮是否被选中

/// @brief 获取按钮当前状态.
/// @param hEle 元素句柄
/// @return 按钮状态
XC_API int  WINAPI XBtn_GetState(HELE hEle);

/// @brief 设置鼠标离开状态按钮显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
XC_API void WINAPI XBtn_SetImageLeave(HELE hEle, HIMAGE hImage = NULL);  //鼠标离开时图片

/// @brief 设置鼠标在按钮上停留状态时显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
XC_API void WINAPI XBtn_SetImageStay(HELE hEle, HIMAGE hImage = NULL);   //鼠标停留时图片

/// @brief 设置按钮按下状态时显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
XC_API void WINAPI XBtn_SetImageDown(HELE hEle, HIMAGE hImage = NULL);   //鼠标按下时图片

/// @brief 设置按钮被选中时显示的图片,如果没有这个状态不使用.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
XC_API void WINAPI XBtn_SetImageCheck(HELE hEle, HIMAGE hImage = NULL);  //选中时图片

/// @brief 设置按钮禁用状态显示的图片.
/// @param hEle 元素句柄
/// @param hImage 图片句柄
XC_API void WINAPI XBtn_SetImageDisable(HELE hEle, HIMAGE hImage = NULL); //按钮禁用状态图片

/// @brief 设置文本对齐.
/// @param hEle 元素句柄.
/// @param flag 标识,请参见MSDN  DrawText().
XC_API void WINAPI XBtn_SetTextAlign(HELE hEle, int flag); //设置文本对齐

/// @brief 设置按钮图标.
/// @param hEle 元素句柄.
/// @param hImage 图片句柄.
XC_API void WINAPI XBtn_SetIcon(HELE hEle, HIMAGE hImage); //设置图标

/// @brief 设置图标对齐方式..
/// @param hEle 元素句柄.
/// @param align 对齐方式.
XC_API void WINAPI XBtn_SetIconAlign(HELE hEle, int align);

/// @brief 启用或关闭,当鼠标移动到按钮上时,鼠标光标形状变为手型.
/// @param hEle 元素句柄.
/// @param bEnable 是否启用.
XC_API void WINAPI XBtn_EnableCursorHand(HELE hEle, BOOL bEnable); //鼠标停留,光标变为手型


/// @brief 开始或关闭图片动画的播放.
/// @param hEle 元素句柄.
/// @param bEnable    开始播放动画TRUE,关闭播放动画FALSE.
/// @param bLoopPlay  是否循环播放.
XC_API void WINAPI XBtn_EnableAnimation(HELE hEle, BOOL bEnable, BOOL bLoopPlay = FALSE);

/// @brief 添加动画帧.
/// @param hEle 元素句柄.
/// @param hImage  图片句柄
/// @param uElapse 图片帧延时,单位毫秒.
XC_API void WINAPI XBtn_AddAnimationFrame(HELE hEle, HIMAGE hImage, UINT uElapse);


//删除所有的动画帧

/// @brief 设置内容坐标偏移量.
/// @param  hEle 元素句柄.
/// @param  x  偏移量.
/// @param  y  偏移量.
XC_API void WINAPI XBtn_SetOffset(HELE hEle, int x, int y); //设置内容坐标偏移量

///@}

//私有方法:
void Btn_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, wchar_t *pTitle, HXCGUI hParent);

void Btn_DrawDisable(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawCheck(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawLeave(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawStay(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawDown(HELE hEle, HDRAW hDraw, RECT &rect);

void Btn_DrawLeave2(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawStay2(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawDown2(HELE hEle, HDRAW hDraw, RECT &rect);
void Btn_DrawDisable2(HELE hEle, HDRAW hDraw, RECT &rect);

void Btn_DrawIconAndText(HELE hEle, HDRAW hDraw, RECT &rect); //绘制图标和文本

void Btn_StartAnimation(HELE hEle, BOOL bClockwise = TRUE);//开始动画

//回调函数:
void CALLBACK Btn_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Btn_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Btn_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Btn_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Btn_OnEventKeyDown(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Btn_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK Btn_OnEventMouseStay(HELE hEle, HELE hEventEle);
BOOL CALLBACK Btn_OnEventMouseLeave(HELE hEle, HELE hEventEle);
BOOL CALLBACK Btn_OnEventSetFocus(HELE hEle, HELE hEventEle); //获得焦点
BOOL CALLBACK Btn_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点

