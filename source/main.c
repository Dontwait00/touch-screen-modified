#include <string.h>
#include <stdio.h>

#include <switch.h>

//See also libnx hid.h.

int main(int argc, char **argv)
{
    u32 prev_touchcount=0;

    gfxInitDefault();
    consoleInit(NULL);

	printf("\x1b[1;1HPress PLUS to exit.");
    printf("\x1b[2;1HTouch Screen position:");
	
	int touchY;
	int touchX;
	
    // Main loop
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

        touchPosition touch;

        u32 i;
        u32 touch_count = hidTouchCount();

        if (touch_count != prev_touchcount)
        {
            prev_touchcount = touch_count;

            consoleClear();

            printf("\x1b[1;1HPress PLUS to exit.");
            printf("\x1b[2;1HTouch Screen position:");
        }
		
		touchY = touch.py / 16;
		touchX = touch.px / 16;
		touchY++;
		touchX++;

        printf("\x1b[3;1H");

        for(i=0; i<touch_count; i++)
        {
            //Read the touch screen coordinates
            hidTouchRead(&touch, i);

            //Print the touch screen coordinates
            printf("[point_id=%d] px=%03d, py=%03d, row=%d, column=%d\n", i, touch.px, touch.py, touchY, touchX);
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
    }
 // 1 < 3
    gfxExit();
    return 0;
}

