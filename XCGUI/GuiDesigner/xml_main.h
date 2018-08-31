#pragma once

//注册函数类型
#define  XC_XML_INIT            1  // 1 UI文件解析库初始化
#define  XC_XML_EXIT            2  // 2 UI文件解析库释放
#define  XC_XML_CREATE_WINDOW   3  // 3 窗口创建
#define  XC_CML_CREATE_ELEMENT  4  // 4 元素创建


// BOOL CALLBACK OnInit();    //1 UI文件解析库初始化
// BOOL CALLBACK OnExit();    //2 UI文件解析库释放
// BOOL CALLBACK OnCreateWindow(HWINDOW hWindow);  // 3 窗口创建
// BOOL CALLBACK OnCreateElement(HELE hEle);    // 4 元素创建
