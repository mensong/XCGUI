/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct treeNode_  //�����
{
	treeNode_   *pParent;  //�����      ����ӽ��ӵ��ͬһ�������
	treeNode_   *pBrother; //���ֽ��    ͬ�����һ�����
	treeNode_   *pLeft;    //����
	treeNode_   *pRight;   //�ҽ��
	int         depth;     //������

	//����
	int      x;         //x����
	int      y;         //y����
	int      id;        //���ID
	int      imageId;   //ͼ������
	int      selectImageId; //ѡ���� ͼƬ����
	BOOL     bExpand;   //�Ƿ�չ�����
	HSTRING  hString;   //�ı�
	void*	 data;      //�û�����

	int      textWidth;  //�ı����
	int      state;      //״̬
	treeNode_  *pEnd;    //�ýڵ����һ�����һ���ӽڵ�

	BOOL  bCheck;  //��ѡ���Ƿ�ѡ��

	RECT rcButton; //��ť����
	RECT rcImage;  //ͼƬ����
	RECT rcText;   //�ı�����
	RECT rcCheck;  //��ѡ������

	HARRAY hArrayBindEle; //�󶨵�Ԫ�� itemBindEle_*
};

#define XTREE_H_LINE_LENGTH     10  //ˮƽ���߳���
#define XTREE_CHECK_SIZE        15  //��ѡ���С

struct tree_
{
	scrollView_  scrollView; //�̳�
	//-------------
	treeNode_  *pRoot;      //�������
	BOOL       bAdjust;     //������,TRUE��Ҫ����
	BOOL       bLine;       //�Ƿ���������
	BOOL       bRootLine;   //���Ӹ�������
	BOOL       bButton;     //�Ƿ���չ����ť
	BOOL       bCheck;      //��ѡ��
	int        uid;         //���ID���� ��ֹ�ظ�,��1��ʼ
	int        expandSize;  //չ����ť��ȸ߶�
	int        indentation; //�����������
	int        itemHeight;  //��߶�
	int        spacingLeft;     //����
	int        spacingTop;      //�ϼ��

	HXCGUI      hImageList;   //ͼƬ�б�
	treeNode_   *pCurrItem;   //��ǰѡ����ڵ�ָ��
	treeNode_   *pEnd;        //���ڵ�����һ���ڵ�

//--------------------------------------
	pFunTree_DrawItem  pDrawItem;
#ifdef	XCGUI_PLUS    //C++��֧��,�����Ա����ע���֧��
	void    *pClass_Fun_Info;//��Ϣ�¼��ص�������Ϣָ��
#endif
};

#ifdef	XCGUI_PLUS //C++��֧��,�����Ա����ע���֧��
XC_API void WINAPI XTree_SetUserDrawItemEx(HELE hEle, pFunClassEventMsg pCallBackFun, void *pClass_Fun_Info); //�����û��Ի���
#endif

//API:
XC_API HELE WINAPI XTree_Create(int x, int y, int cx, int cy, HXCGUI hParent = NULL);
//parentId:0Ϊ���ڵ�ID; insertAfter:����λ�ñ�ʶ,�����ǲ���ָ�������,���ID
XC_API int WINAPI XTree_InsertItem(HELE hEle, wchar_t *pText, int parentId = XTREE_ROOT, int imageId = -1, int selectImageId = -1, int insertAfter = XTREE_INSERT_LAST, BOOL bExpand = TRUE); //������

XC_API void WINAPI XTree_EnableButton(HELE hEle, BOOL bEnable);    //��ʾ��ť
XC_API void WINAPI XTree_EnableLine(HELE hEle, BOOL bEnable);      //��ʾ��������
XC_API void WINAPI XTree_EnableRootLine(HELE hEle, BOOL bEnable);  //�������Ӹ�������
XC_API BOOL WINAPI XTree_IsButton(HELE hEle);
XC_API BOOL WINAPI XTree_IsLine(HELE hEle);
XC_API BOOL WINAPI XTree_IsRootLine(HELE hEle);
XC_API BOOL WINAPI XTree_IsExpand(HELE hEle, int id); //�ж�ָ�����Ƿ�չ��

XC_API void WINAPI XTree_SetSpacingLeft(HELE hEle, int left);   //��������
XC_API void WINAPI XTree_SetSpacingTop(HELE hEle, int top);     //�����ϼ��
XC_API void WINAPI XTree_SetImageList(HELE hEle, HXCGUI hImageList); //����ͼƬ�б�
XC_API void WINAPI XTree_SetItemData(HELE hEle, int id, void* data);   //�����û�����
XC_API void WINAPI XTree_SetExpandButtonSize(HELE hEle, int size);   //����չ����ť��С
XC_API void WINAPI XTree_SetIndentation(HELE hEle, int width);  //���������������
XC_API void WINAPI XTree_SetSelectItem(HELE hEle, int id);     //����ѡ����
XC_API void WINAPI XTree_SetItemText(HELE hEle, int id, wchar_t *pText);//�������ı�
XC_API void WINAPI XTree_SetItemImage(HELE hEle, int id, int imageId);  //������ͼƬ
XC_API void WINAPI XTree_SetItemHeight(HELE hEle, int height); //������߶�
XC_API BOOL WINAPI XTree_SetItemBindEle(HELE hEle, int id, itemBindEle_ *pInfo); //��Ԫ��

XC_API void* WINAPI XTree_GetItemData(HELE hEle, int id); //��ȡ�û�����
XC_API int WINAPI XTree_GetItemHeight(HELE hEle);      //��ȡ��߶�
XC_API int WINAPI XTree_GetSelectItem(HELE hEle);   //��ȡ��ǰѡ�����
XC_API int WINAPI XTree_GetParentItem(HELE hEle, int id); //��ȡָ����ĸ���
XC_API int WINAPI XTree_GetChildItem(HELE hEle, int id);  //��ȡָ���������
XC_API int WINAPI XTree_GetNextSiblingItem(HELE hEle, int id); //��ȡָ�������һ���ֵ���
XC_API int WINAPI XTree_GetPrevSiblingItem(HELE hEle, int id); //��ȡָ�������һ���ֵ���
XC_API int WINAPI XTree_GetFirstItem(HELE hEle); //��ȡ��һ���ڵ�
XC_API int WINAPI XTree_GetItemDepth(HELE hEle, int id);//��ȡ�ڵ����

XC_API int WINAPI XTree_GetItemImage(HELE hEle, int id);  //��ȡ��ͼƬ
XC_API wchar_t* WINAPI XTree_GetItemText(HELE hEle, int id); //��ȡ���ı�
XC_API HXCGUI WINAPI XTree_GetImageList(HELE hEle); //��ȡͼƬ�б�
XC_API void WINAPI XTree_Expand(HELE hEle, int id, BOOL bExpand); //չ������ָ����
XC_API void WINAPI XTree_DeleteItem(HELE hEle, int id); //ɾ��һ����
XC_API void WINAPI XTree_DeleteAllItems(HELE hEle); //�����


XC_API int WINAPI XTree_HitTest(HELE hEle, POINT *pPt);  //���Ե��λ��,������ID


XC_API void WINAPI XTree_SetUserDrawItem(HELE hEle, pFunTree_DrawItem pFunDrawItem); //�����û��Ի���

XC_API void WINAPI XTree_EnableCheckBox(HELE hEle, BOOL bEnable);//���ø�ѡ��
XC_API BOOL WINAPI XTree_IsItemCheck(HELE hEle, int id); //�ж���ĸ�ѡ���Ƿ�ѡ
XC_API void WINAPI XTree_SetItemCheck(HELE hEle, int id, BOOL bCheck); //������ĸ�ѡ��

//˽�з���:
void Tree_Init(HELE hEle, int x, int y, int cx, int cy, int eleType, HXCGUI hParent);
int  Tree_AddID(HELE hEle); //������ID
BOOL Tree_AddIDTest(treeNode_ *pNode, int id); //���ID�Ƿ�ʹ��

BOOL Tree_InsertItem1(HELE hEle, treeNode_ *pNode);  //���ڵ�
BOOL Tree_InsertItem2(HELE hEle, treeNode_ *pNode, int insertAfter);  //���ڵ���ֵܽڵ�
BOOL Tree_InsertItem3(HELE hEle, treeNode_ *pNode, int parentId, int insertAfter);

treeNode_* Tree_GetTreeNode(HELE hEle, treeNode_ *pNode, int nodeId); //��ȡָ��ID���

void Tree_AdjustTree(HELE hEle);  //������
void Tree_TraversalAdjustTree(HELE hEle, treeNode_ *pNode, int x, int *pHeights, int *pWidths, BOOL bExpand); //����������

BOOL Tree_TestClick(HELE hEle, treeNode_ *pNode, POINT *pPt);   //�������������
BOOL Tree_TextDBClick(HELE hEle, treeNode_ *pNode, POINT *pPt); //�����������˫��
void Tree_DeleteNode(treeNode_ *pNode); //����ɾ�����,��������
void Tree_DrawItem(HELE hEle, HDRAW hDraw, treeNode_ *pNode);
treeNode_ *Tree_HitTestNode(HELE hEle, treeNode_ *pNode, POINT *pPt);  //���Ե��λ��

void Tree_UserDrawItem(HELE hEle, HDRAW hDraw, treeNode_ *pNode);

//�ص�����:
void CALLBACK Tree_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Tree_OnDrawScrollView(HELE hEle, HDRAW hDraw);
BOOL CALLBACK Tree_OnLButtonDown(HELE hEle, UINT flags, POINT *pPt);
BOOL CALLBACK Tree_OnRButtonDown(HELE hEle, UINT flags, POINT *pPt);

BOOL CALLBACK Tree_OnMouseDBClick(HELE hEle, POINT *pPt);

BOOL CALLBACK Tree_OnEventSetFocus(HELE hEle, HELE hEventEle);  //��ý���
BOOL CALLBACK Tree_OnEventKillFocus(HELE hEle, HELE hEventEle); //ʧȥ����


