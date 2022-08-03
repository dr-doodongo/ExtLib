#ifndef __GET_INC_H__
#define __GET_INC_H__

#include <ExtLib.h>
#include <ExtGui/Cursor.h>
#include <ExtGui/Input.h>
#include <ExtGui/Matrix.h>
#include <ExtGui/View.h>
#include <ExtGui/Theme.h>
#include <ExtGui/GeoGrid.h>
#include <ExtGui/Collision.h>

struct MessageWindow;

typedef void (* CallbackFunc)(void*);
typedef void (* DropCallback)(GLFWwindow*, s32, char* item[]);

typedef enum {
	APP_RESIZE_CALLBACK = 1 << 0,
	APP_MAIN            = 1 << 1,
	APP_MSG_WIN         = 1 << 2,
	APP_CLOSED          = 1 << 3,
} AppState;

typedef struct AppInfo {
	GLFWwindow*  window;
	CallbackFunc updateCall;
	CallbackFunc drawCall;
	Input*   input;
	void*    context;
	Vec2s    wdim;
	Vec2s    bufDim;
	Vec2s    prevWinDim;
	AppState state;
	struct SubWindow* subWinHead;
} AppInfo;

typedef struct SubWindow {
	AppInfo app;
	Input   input;
	void*   vg;
	struct SubWindow* next;
} SubWindow;

typedef struct MessageWindow {
	SubWindow   window;
	s32 value;
	const char* message;
} MessageWindow;

AppInfo* GetAppInfo(void* window);
void* GetUserCtx(void* window);

extern const f64 gNativeFPS;
extern ThreadLocal bool gLimitFPS;

void* Interface_Init(
	const char* title,
	AppInfo* app,
	Input* input,
	void* context,
	CallbackFunc
	updateCall,
	CallbackFunc drawCall,
	DropCallback dropCallback,
	u32 x, u32 y,
	u32 samples
);
void Interface_Main(AppInfo* app);
void Interface_Destroy(AppInfo* app);
SubWindow* Interface_MessageWindow(AppInfo* parentApp, const char* title, const char* message);

#endif
