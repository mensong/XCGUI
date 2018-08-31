/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct editStrList_
{
	HSTRING  hString;
	int      len;      //字符显示长度，像素
};

struct edit_
{
	scrollView_  scrollView;   //继承
	//--------------------
	HARRAY hArrayEdit;   //字符内容 editStrList_*

	POINT caretPt;       //插入符位置
	BOOL  bCaretCreate;  //插入符是否创建
	BOOL  bMoreLine;     //多行输入
	BOOL  bReadOnly;     //设置只读文本
	BOOL  bMenu;         //启用弹出菜单

	//文本内容与视口边框的间隔,不是与元素边框的间隔
	int   spacLeft;  //左间隔
	int   spacTop;   //上间隔
//	int   spacRight; //右间隔
//	int   spacBottom;//下间隔

	int   rowHeight; //行高
	int   row;       //当前行 从0开始
	int   rows;      //总行数 从0开始
	int   column;    //当前列 从0开始,一个字符为一列
	int   maxLine;   //最长的行 行号

	//文本选择
	BOOL  bDown;        //鼠标按下,准备选择文本
	BOOL  bDrawSelect;  //绘制选择文本背景色
	int   downX;        //按下位置
	int   downRow;      //行
	int   downColumn;   //列
	int   endX;
	int   endRow;
	int   endColumn;

	BOOL  bNumber;  //数子

	int   caretWidth; //插入符宽度
	//////密码框/////////////////密码框单行显示,不可以多行
	BOOL  bPass;     //密码框
	SIZE  sizePass;  //密码字符大小
	////////////////////////
	COLORREF selColor; //选择文本颜色
	BOOL  bMouseStay; //鼠标停留

	//贴图
	HIMAGE hImage_stay; //鼠标停留
};


//API:
XC_API HELE WINAPI XEdit_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
XC_API void WINAPI XEdit_EnableMultiLine(HELE hEle, BOOL b);  //启用多行输入
XC_API void WINAPI XEdit_EnablePassBox(HELE hEle, BOOL bPass); //启用密码框
XC_API void WINAPI XEdit_EnableNumber(HELE hEle, BOOL bNumber); //只能输入数字
XC_API void WINAPI XEdit_EnablePopupMenu(HELE hEle, BOOL bEnable);  //启用鼠标右键菜单

XC_API void WINAPI XEdit_InsertText(HELE hEle, wchar_t *pText, int row = -1, int column = -1); //插入文本,row=-1末尾行,column=-1末尾列;
XC_API void WINAPI XEdit_DeleteSelectText(HELE hEle); //删除选择文本,当只读属性时,也可以删除文本
XC_API void WINAPI XEdit_SetText(HELE hEle, wchar_t *pText);  //设置文本
XC_API void WINAPI XEdit_SetInt(HELE hEle, int value);  //设置整形内容
XC_API void WINAPI XEdit_SetReadOnly(HELE hEle, BOOL bRead);  //设置只读文本
XC_API void WINAPI XEdit_SetTextSpacingLeft(HELE hEle, int spacing);  //设置字体左对齐间隔
XC_API void WINAPI XEdit_SetTextSpacingTop(HELE hEle, int spacing);  //设置字体上对齐间隔
XC_API void WINAPI XEdit_SetPos(HELE hEle, int line, int column); //设置插入符位置
XC_API void WINAPI XEdit_SetCaretWidth(HELE hEle, int width); //设置编辑框插入符宽度
XC_API void WINAPI XEdit_SetBackspace(HELE hEle);  //退格
XC_API void WINAPI XEdit_SetSelectTextBkColor(HELE hEle, COLORREF color);//设置选择文本背景颜色
//XC_API void WINAPI XEdit_SetSelectText(HELE hEle, int startRow, int startCol, int endRow, int endCol);

XC_API void WINAPI XEdit_GetSelectText(HELE hEle, wchar_t *pOut, int len);  //获取选择内容
XC_API int  WINAPI XEdit_GetTextLength(HELE hEle); //获取内容长度
XC_API void WINAPI XEdit_GetText(HELE hEle, wchar_t *pOut, int len); //获取文本
XC_API int  WINAPI XEdit_GetInt(HELE hEle); //获取整形内容

XC_API int WINAPI XEdit_GetRowCount(HELE hEle);   //获取总行数
XC_API int WINAPI XEdit_GetColumnCount(HELE hEle, int row); //获取指定行字符数,row=-1末尾行;
XC_API int WINAPI XEdit_GetCurrentRow(HELE hEle);  //获取插入符位置当前行
XC_API int WINAPI XEdit_GetCurrentColumn(HELE hEle); //获取插入符位置当前列

XC_API BOOL WINAPI XEdit_IsEmpty(HELE hEle); //判断内容是否为空
XC_API void WINAPI XEdit_DeleteAll(HELE hEle);  //清空  删除所有文本

XC_API void WINAPI XEdit_Menu_Cut(HELE hEle);        //剪切  删除选择的文本,并将文本拷贝到剪切板中
XC_API void WINAPI XEdit_Menu_Copy(HELE hEle);       //复制  复制选择的文本到剪切板中
XC_API void WINAPI XEdit_Menu_Paste(HELE hEle);      //粘贴  将剪切板中的文本插入当前光标位置
XC_API void WINAPI XEdit_Menu_Clear(HELE hEle);      //删除  删除选择的文本,当只读属性时无法删除文本
XC_API void WINAPI XEdit_Menu_SelectAll(HELE hEle);  //全选  选择所有文本
XC_API void WINAPI XEdit_Menu_DeleteAll(HELE hEle);  //清空  删除所有文本


//贴图:
XC_API void WINAPI XEdit_SetImageLeave(HELE hEle, HIMAGE hImage = NULL); //鼠标离开
XC_API void WINAPI XEdit_SetImageStay(HELE hEle, HIMAGE hImage = NULL); //鼠标停留

//私有方法:
void Edit_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
void Edit_CreateCaret(HELE hEle);
void Edit_SetCaretPos(HELE hEle);
void Edit_TestDown(HELE hEle, in_out_ POINT *pPt);

void Edit_AdjustViewSize(HELE hEle); //挑战视图内容大小
void Edit_ScrollH(HELE hEle);    //向左拖到滚动条滚动,水平滚动
void Edit_ScrollV(HELE hEle);  //向下拖动滚动条,垂直滚动

BOOL Edit_SetText_ExamineStringNumber(HELE hEle, wchar_t *pText);
void Edit_SetText_SingleLine(HELE hEle, wchar_t *pText);
void Edit_SetText_MoreLine(HELE hEle, wchar_t *pText);

void Edit_InsertText_SingleLine(HELE hEle, wchar_t *pText, wchar_t *pBuf, int row, int column);
void Edit_InsertText_MoreLine(HELE hEle, wchar_t *pText, wchar_t *pBuf, int row, int column);

void Edit_Char(HELE hEle, wchar_t ch);  //字符
void Edit_CharEnter(HELE hEle);   //回车
void Edit_CharBackspace(HELE hEle);  //退格
void Edit_CharBackspaceEnter(HELE hEle); //退格,当前删除的是回车
void Edit_CharDeleteKey(HELE hEle); //Delete键

void Eidt_MouseCreatLeft(HELE hEle);   //移动插入符 向左 ←
void Eidt_MouseCreatRight(HELE hEle);  //移动插入符 向右 →
void Eidt_MouseCreatTop(HELE hEle);    //移动插入符 向上 ↑
void Eidt_MouseCreatBottom(HELE hEle); //移动插入符 向下 ↓

HSTRING Edit_GetSelectText(HELE hEle); //获取选择文本

BOOL Edit_DeleteSelectText(HELE hEle);
void Edit_DeleteSelectTextHandle(HELE hEle, int beginRow, int endRow, int beginColumn, int endColumn, int beginX); //删除选择文本
void Edit_GetSelectTextHandle(HELE hEle, HSTRING hString, int beginRow, int endRow, int beginColumn, int endColumn);

BOOL Edit_InsertText(HELE hEle, wchar_t *pText, int row, int column);


//绘制文本选择
void Edit_DrawSelect(HELE hEle, HDRAW hDraw); //会在选择文本背景
void Edit_DrawSelectBottom(HELE hEle, HDRAW hDraw, HBRUSH hBrush);
void Edit_DrawSelectTop(HELE hEle, HDRAW hDraw, HBRUSH hBrush);

//回调函数:
void CALLBACK Edit_OnDestroy(HELE hEle);  //销毁
BOOL CALLBACK Edit_OnDraw(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Edit_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Edit_OnEventMouseStay(HELE hEle, HELE hEventEle);
BOOL CALLBACK Edit_OnEventMouseLeave(HELE hEle, HELE hEventEle);

BOOL CALLBACK Edit_OnEventHScrollView(HELE hEle, HELE hEventEle, int pos);
BOOL CALLBACK Edit_OnEventVScrollView(HELE hEle, HELE hEventEle, int pos);
BOOL CALLBACK Edit_OnEventSetFocus(HELE hEle, HELE hEventEle); //获得焦点
BOOL CALLBACK Edit_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点
BOOL CALLBACK Edit_OnEventChar(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Edit_OnEventKeyDown(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Edit_OnEventMenuSelect(HELE hEle, HELE hEventEle, int id); //菜单选择事件
BOOL CALLBACK Edit_OnEventSize(HELE hEle, HELE hEventEle); //元素大小位置改变
BOOL CALLBACK Edit_OnEventSetFont(HELE hEle, HELE hEventEle);


BOOL CALLBACK Edit_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Edit_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Edit_OnMouseMove_View(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK Edit_OnRButtonDown_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Edit_OnRButtonUp_View(HELE hEle, UINT flags, POINT *pPt);