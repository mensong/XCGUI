#pragma once


//文件选择编辑框



struct editFile_
{
	edit_  edit; //继承
	//-------------
	BOOL    bEdit;      //可编辑内容
	int     heights;    //总高度
	BOOL    bOpenBrowseFile; //是否打开文件浏览窗口

	HSTRING  hType;  //打开文件类型
	HSTRING  hDefaultFile;  //默认目录
	HSTRING  hRelativeDir;  //相对目录 Relative directory

	//下拉按钮:
	struct
	{
		RECT rcButton;//下拉按钮
		int  state;   //状态
	}button_;

	//贴图
	HIMAGE hImage_stay; //鼠标停留
	HIMAGE hImage_down; //鼠标按下
};

//API:
XC_API HELE WINAPI XEditFile_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);

XC_API void WINAPI XEditFile_SetOpenFileType(HELE hEle, wchar_t *pType); //设置打开文件类型
XC_API void WINAPI XEditFile_SetDefaultFile(HELE hEle, wchar_t *pFile); //设置默认目录文件
XC_API void WINAPI XEditFile_SetRelativeDir(HELE hEle, wchar_t *pDir); //TODO:设置相对路径

//私有方法:
void EditFile_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void EditFile_Adjust(HELE hEle);
void EditFile_DrawBk(HELE hEle, HDRAW hDraw); //绘制背景
void EditFile_BrowseFile(HELE hEle); //浏览文件

//回调函数:
BOOL CALLBACK EditFile_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK EditFile_OnLButtonUp(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK EditFile_OnMouseMove(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK EditFile_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK EditFile_OnRButtonUp(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK EditFile_OnEventMouseLeave(HELE hEle, HELE hEventEle);
BOOL CALLBACK EditFile_OnEventKillFocus(HELE hEle, HELE hEventEle);

BOOL CALLBACK EditFile_OnEventSetFocus(HELE hEle, HELE hEventEle);
BOOL CALLBACK EditFile_OnEventSize(HELE hEle, HELE hEventEle);

BOOL CALLBACK EditFile_OnDraw(HELE hEle, HDRAW hDraw);
void CALLBACK EditFile_OnDestroy(HELE hEle); //销毁

BOOL CALLBACK EditFile_OnDrawButton(HELE hEle, HDRAW hDraw); //绘制下拉按钮