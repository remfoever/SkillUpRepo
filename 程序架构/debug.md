# DEBUG模块



## debug_set.c

```c
#include "wx_debug_set.h"
#include "wx_include.h"


#define WX_DEBUG_SET_CMD_MAX_NUM 32
WxDbgCmdItem g_wxDbgSetItem[WX_DEBUG_SET_CMD_MAX_NUM] = {0};
UINT32 g_wxDbgSetItemNum = 0;

VOID WX_Debug_SetHelp(CHAR *argv[], UINT32 argc)
{
    wx_show("DEBUG Set Help");
    wx_show("--------------");
    wx_show("%-16s %s", "Cmd", "Description");
    WxDbgCmdItem *item = NULL;
    for (UINT32 i = 0; i < g_wxDbgSetItemNum; i++) {
        item = &g_wxDbgSetItem[i];
        wx_show("%-16s %s", item->cmdName, item->helpDesc);
    }
}

UINT32 WX_Debug_RegSetCmd(CHAR *cmdName, CHAR *helpDesc,
                          VOID (*cmdExecFunc)(CHAR *argv[], UINT32 argc))
{
    if (g_wxDbgSetItemNum >= WX_DEBUG_SET_CMD_MAX_NUM) {
        return WX_DBG_SET_ITEM_FULL;
    }

    g_wxDbgSetItem[g_wxDbgSetItemNum].cmdName = cmdName;
    g_wxDbgSetItem[g_wxDbgSetItemNum].helpDesc = helpDesc;
    g_wxDbgSetItem[g_wxDbgSetItemNum].cmdExecFunc = cmdExecFunc;

    g_wxDbgSetItemNum++;

    return WX_SUCCESS;
}

VOID WX_Debug_Set(CHAR *argv[], UINT32 argc)
{
    if (argc == 0) {
        WX_Debug_SetHelp(argv, argc);
        return;
    }

    CHAR *itemName = argv[0];
    WxDbgCmdItem *handle = NULL;

    for (UINT32 i = 0; i < g_wxDbgSetItemNum; i++) {
        handle = &g_wxDbgSetItem[i];

        if (strcmp(itemName, handle->cmdName) != 0) {
            continue;
        }

        if (handle->cmdExecFunc == NULL) {
            wx_show("<cmd> Set %s not support.", handle->cmdName);
            return;
        }

        handle->cmdExecFunc(&argv[1], argc - 1);
        return;
    }

    wx_show("(cmd) Set %s not exist.", argv[0]);
    return;
}

```



```c
#ifndef WX_DEBUG_SET_H
#define WX_DEBUG_SET_H
#include "wx_typedef.h"

VOID WX_Debug_SetHelp(CHAR *argv[], UINT32 argc);
UINT32 WX_Debug_RegSetCmd(CHAR *cmdName, CHAR* helpDesc, VOID (*cmdExecFunc)(CHAR *argv[], UINT32 argc));
/* Debug_Set主函数 */
VOID WX_Debug_Set(CHAR *argv[], UINT32 argc);

#endif

```

































