/**************************************************************************\
*
* Copyright (c)  炫彩界面库. All Rights Reserved.
*
* 炫彩界面库 - 官方网站 : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


enum rictEdit_ItemType_ //项类型
{
	richEdit_itemType_char,
	richEdit_itemType_image,
	richEdit_itemType_gif,
	richEdit_itemType_ele,
};

//字体信息
struct richEdit_font_Info_
{
	HFONT    hFont;
	LOGFONT  info;
	int      index; //字体索引
};

//行对象
struct richEdit_line_
{
	HARRAY   hArrayItem; //行内容  richEdit_item_*
	int      lenPixel;        //字符串显示长度，像素
	int      maxItemHeight;  //项高度,取该行中最高项的值

	//是否为虚拟行,当启动自动换行
	//行间距,如果为-1使用默认间距

	int  top; //行的上边界,下边界等于上边界加maxItemHeight
};

//最小单元类型
struct richEdit_item_
{
	rictEdit_ItemType_ type; //类型
	richEdit_line_     *pLine; // 所属行节点
	SIZE               size;
};

struct richEdit_item_char_  //字符
{
	richEdit_item_  item;
	wchar_t   ch;

	//////自定义属性/////////////////////////
	HFONT     hFont;     //自定义字体
	richEdit_font_Info_  *pFontInfo;
	BOOL      bColor;    //颜色是否有效
	COLORREF  color;     //颜色
						 //自定义字符间距
};

struct richEdit_item_iamge_  //图片
{
	richEdit_item_  item;
	HIMAGE          hImage;
	HSTRING         hString;  //图片路径
};

class ImageEx;
struct richEdit_item_gif_    //GIF动画
{
	richEdit_item_  item;
	ImageEx         *pGif;
	HSTRING         hString;  //图片路径

	HELE            hView;   //RichEdit 视
	DWORD           timer;   //上次记录时间
	DWORD           ms;      // 当前帧延时
};

struct richEdit_item_ele_    //元素
{
	richEdit_item_  item;
	HELE           hEle;
};

struct richEdit_
{
	scrollView_  scrollView;   //继承
	//---------------------

	HARRAY hArrayLine;    //字符内容行列表 richEdit_line_*
	HARRAY hArrayFont;    //字体列表,防止重复创建相同的字体 richEdit_font_Info_*
	BOOL   bCaretCreate;  //插入符是否创建
	BOOL   bReadOnly;     //设置只读文本

	//全局设置------------------
	//文本内容与视口边框的间隔,不是与元素边框的间隔
	int   spacLeft;  //左间隔
	int   spacTop;   //上间隔

	int   row;       //当前行 从0开始
	int   rowCount;  //总行数 从1开始
	int   column;    //当前列 从0开始,一个字符为一列

	BOOL bAdjust;
	BOOL bAdjustCaret;     //需要调整插入符 
	BOOL bAdjustCalculate; //需要重新计算插入符坐标

	//字体间距
	//行间距

	//自动换行
	//是否接收TAB按键

	int   maxLine;       //最长行,行号,基于0索引

	//下划线
	int   lineHeight;     //行默认高度

	POINT caretPt;       //插入符位置
	int   caretHeight;   //插入符高度

	int   visibleBegin;  //可视第一行,行号,基于0索引
	int   visibleEnd;    //可视最后一行,行号,基于0索引

	//文本选择
	BOOL  bDown;        //鼠标按下,准备选择文本
	BOOL  bDrawSelect;  //绘制选择文本背景色
	int   downRow;      //行
	int   downColumn;   //列
	int   endRow;
	int   endColumn;
};
//行的实际高度=(最高项的高度 || 默认高度)+行间距

//API:
XC_API HELE WINAPI XRichEdit_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);

XC_API BOOL WINAPI XRichEdit_InsertText(HELE hEle, wchar_t *pText, int row, int column); //插入文本内容
XC_API BOOL WINAPI XRichEdit_InsertTextEx(HELE hEle, wchar_t *pText, int row, int column, LOGFONT *pFont, BOOL bColor = FALSE, COLORREF color = 0);
XC_API BOOL WINAPI XRichEdit_InsertData(HELE hEle, void *pData, int row, int column);
// BOOL WINAPI XRichEdit_InsertEle(HELE hEle,HELE hNew); //插入元素,到当前位置
XC_API BOOL WINAPI XRichEdit_InsertImage(HELE hEle, HIMAGE hImage, wchar_t *pImagePath, int row, int column); //插入图片,到当前位置
XC_API BOOL WINAPI XRichEdit_InsertImageGif(HELE hEle, wchar_t *pImageName, int row, int column);//插入GIF图片,到当前位置
//插入超链接

XC_API void WINAPI XRichEdit_SetText(HELE hEle, wchar_t *pText);  //设置文本内容,会清空之前的内容
XC_API BOOL WINAPI XRichEdit_SetPos(HELE hEle, int row, int column); //设置插入符位置
// BOOL WINAPI XRichEdit_SetItemFont(HELE hEle,int row,int column,HFONT hFont);//设置项字体
XC_API BOOL WINAPI XRichEdit_SetItemFontEx(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, LOGFONT *pFont);

// BOOL WINAPI XRichEdit_SetItemColor(HELE hEle,int row,int column,COLORREF color);//设置颜色
XC_API BOOL WINAPI XRichEdit_SetItemColorEx(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, COLORREF color);
XC_API void WINAPI XRichEdit_SetRowHeight(HELE hEle, int height); //设置默认行高
XC_API void WINAPI XRichEdit_SetReadOnly(HELE hEle, BOOL bRead);  //设置只读内容

XC_API int WINAPI XRichEdit_GetItemCount(HELE hEle); //获取内容数量,包括图片
XC_API void WINAPI XRichEdit_GetText(HELE hEle, HSTRING hString); //获取文本内容
XC_API void WINAPI XRichEdit_GetHTMLFormat(HELE hEle, HSTRING hString);  //获取HTML格式内容
XC_API void* WINAPI XRichEdit_GetData(HELE hEle);
XC_API void WINAPI XRichEdit_GetCurrentPos(HELE hEle, out_ int *pRow, out_ int *pColumn);//获取插入符位置,当前行和列
XC_API BOOL WINAPI XRichEdit_GetSelectPos(HELE hEle, out_ int *pBeginRow, out_ int *pBeginColumn, out_ int *pEndRow, out_ int *pEndColumn);//获取选择内容位置
XC_API int  WINAPI XRichEdit_GetSelectText(HELE hEle, wchar_t *pOut, int len);//获取选择内容
XC_API int  WINAPI XRichEdit_GetRowCount(HELE hEle);   //获取总行数
XC_API int  WINAPI XRichEdit_GetRowItemCount(HELE hEle, int row);   //获取指定行内容数量
XC_API void WINAPI XRichEdit_GetVisibleRow(HELE hEle, out_ int *pBeginRow, out_ int *pEndRow); //获取可视行范围
XC_API int  WINAPI XRichEdit_GetRowHeight(HELE hEle); //获取默认行高
XC_API int  WINAPI XRichEdit_GetFontCount(HELE hEle);  //获取字体数量

XC_API BOOL WINAPI XRichEdit_IsEmpty(HELE hEle);  //判断内容是否为空
XC_API BOOL WINAPI XRichEdit_CancelSelect(HELE hEle); //取消选择
XC_API void WINAPI XRichEdit_SelectAll(HELE hEle);  //全选  选择所有文本
XC_API void WINAPI XRichEdit_Select(HELE hEle, int minX, int minY, int maxX, int maxY);

XC_API void WINAPI XRichEdit_ClearFontTable(HELE hEle); //清理字体表,清理未使用的字体

XC_API BOOL WINAPI XRichEdit_DeleteEx(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn); //删除指定内容
XC_API BOOL WINAPI XRichEdit_DeleteSelect(HELE hEle); //删除选择内容
XC_API void WINAPI XRichEdit_DeleteAll(HELE hEle); //清空内容

XC_API BOOL WINAPI XRichEdit_Menu_Cut(HELE hEle);        //剪切  删除选择的文本,并将文本拷贝到剪切板中
XC_API BOOL WINAPI XRichEdit_Menu_Copy(HELE hEle);       //复制  复制选择的文本到剪切板中
XC_API BOOL WINAPI XRichEdit_Menu_Paste(HELE hEle);      //粘贴  将剪切板中的文本插入当前光标位置
// void WINAPI XRichEdit_Clear(HELE hEle);      //删除  删除选择的文本,当只读属性时无法删除文本

XC_API void WINAPI XRichEdit_Adjust(HELE hEle, int startIndex = 0); //调整

void RichEdit_Clipboard_Copy_Text(wchar_t *pText, int charLen);
void RichEdit_Clipboard_Copy_Data(HELE hEle, HARRAY hArrayItem, int dataSize);
void RichEdit_Clipboard_Copy_HTMLFormat(wchar_t *pText, int charLen);

BOOL RichEdit_Clipboard_Paste_Text(HELE hEle);
BOOL RichEdit_Clipboard_Paste_Data(HELE hEle);

BOOL RichEdit_SetItemFontExSingleLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, richEdit_font_Info_ *pFontInfo);
BOOL RichEdit_SetItemFontExMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, richEdit_font_Info_ *pFontInfo);

BOOL RichEdit_SetItemColorExSingleLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, COLORREF color);
BOOL RichEdit_SetItemColorExMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, COLORREF color);

int RichEdit_GetSelectSingleLine(HELE hEle, wchar_t *pOut, int len);
int RichEdit_GetSelectMultiLine(HELE hEle, wchar_t *pOut, int len);

BOOL RichEdit_Clipboard_CopySingleLine(HELE hEle);
BOOL RichEdit_Clipboard_CopyMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, BOOL bForward);

BOOL RichEdit_DeleteEx_SingleLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn);
BOOL RichEdit_DeleteEx_MultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn);

richEdit_font_Info_* RichEdit_GetFont(HELE hEle, LOGFONT *pFont);  //检查字体
BOOL RichEdit_IsUnUseFont(HARRAY hArrayLine, richEdit_font_Info_ *pFontInfo);

//私有方法:
void RichEdit_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);

void RichEdit_Char(HELE hEle, wchar_t ch);    //字符
void RichEdit_CharEnter(HELE hEle);          //回车
void RichEdit_CharBackspace(HELE hEle);      //退格
void RichEdit_CharBackspaceEnter(HELE hEle); //退格,当前删除的是回车
void RichEdit_CharDeleteKey(HELE hEle);      //删除键

void RichEdit_Calculate_VisibleLine(HELE hEle); //计算可视行
BOOL RichEdit_Calculate_LineMaxHeight(HELE hEle, int row); //计算当前行最大高度值
BOOL RichEdit_Calculate_CaretPos(HELE hEle); //计算插入符位置

void RichEdit_CreateCaret(HELE hEle);
void RichEdit_SetCaretPos(HELE hEle);

void RichEdit_ScrollH(HELE hEle);
void RichEdit_ScrollV(HELE hEle);

BOOL RichEdit_TestDown(HELE hEle, POINT *pPt);

BOOL RichEdit_GetItemRect(richEdit_item_ *pItem, RECT *pRect); //获取项坐标,如果不在绘制范围内,返回FALSE
BOOL RichEdit_GetItemRect2(HELE hEle, richEdit_item_ *pItem, RECT *pRect); //获取项坐标,基于视口坐标,如果不在绘制范围内,返回FALSE


void RichEidt_MouseCreatLeft(HELE hEle);   //移动插入符 向左 ←
void RichEidt_MouseCreatRight(HELE hEle);  //移动插入符 向右 →
void RichEidt_MouseCreatTop(HELE hEle);    //移动插入符 向上 ↑
void RichEidt_MouseCreatBottom(HELE hEle); //移动插入符 向下 ↓

void RichEdit_FreeItem(richEdit_item_ *pItem);
void RichEdit_FreeLine(richEdit_line_ *pLine);
BOOL RichEdit_DeleteSelect(HELE hEle);
BOOL RichEdit_DeleteSelectSingleLine(HELE hEle);
BOOL RichEdit_DeleteSelectMultiLine(HELE hEle, int beginRow, int beginColumn, int endRow, int endColumn, BOOL bForward);

void RichEdit_DrawSelectBG(HELE hEle, HDRAW hDraw); //绘制选择内容背景


//回调函数:
BOOL CALLBACK RichEdit_OnEventChar(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RichEdit_OnEventKeyDown(HELE hEle, HELE hEventEle, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RichEdit_OnEventSetFocus(HELE hEle, HELE hEventEle); //获得焦点
BOOL CALLBACK RichEdit_OnEventKillFocus(HELE hEle, HELE hEventEle); //失去焦点
BOOL CALLBACK RichEdit_OnEventSetFont(HELE hEle, HELE hEventEle);


BOOL CALLBACK RichEdit_OnEventHScrollView(HELE hEle, HELE hEventEle, int pos);
BOOL CALLBACK RichEdit_OnEventVScrollView(HELE hEle, HELE hEventEle, int pos);

BOOL CALLBACK RichEdit_OnDrawScrollView(HELE hEle, HDRAW hDraw);
void CALLBACK RichEdit_OnEventDestroy(HELE hEle);

//视元素
BOOL CALLBACK RichEdit_OnLButtonDown_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK RichEdit_OnLButtonUp_View(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK RichEdit_OnMouseMove_View(HELE hEle, UINT flags, POINT *pPt);



/////////////////////////////////////////////////
struct richEdit_clipboard_header_ //头信息
{
	wchar_t    name[15]; //开始标识  XCGUI_RichEdit
	LOGFONT    font;     //默认字体
	COLORREF   color;    //默认颜色
	int        size;     //内容总长度,字节为单位
	int        itemCount;      //内容项数量,项为字体或图片
	int        fontCount; //个性化字体数量
};

//struct richEdit_clipboard_fontTable_ //字体表
//{
//	LOGFONT  font;  //字体信息
//};

struct richEdit_clipboard_char_ //内容元素
{
	rictEdit_ItemType_ type;
	int       fontIndex; //字体索引, -1为默认字体
	COLORREF  color;     //颜色
	BOOL      bColor;    //颜色是否有效
	wchar_t   ch;        //字CH
};

struct richEdit_clipboard_iamge_//内容图片
{
	rictEdit_ItemType_  type;
	int      size;          //字节为单位长度,包含空终止符
	int      chs;  //图片地址
};
