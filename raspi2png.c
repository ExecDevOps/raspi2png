//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Andrew Duncan
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

#define _GNU_SOURCE

#include <getopt.h>
#include <math.h>
#include <png.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <microhttpd.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include "bcm_host.h"

char VIEW_PAGE[] = ""\
"<html>\n"\
"	<body>\n"\
"		<script type='text/javascript'>\n"\
"			var canvas = document.createElement('canvas');\n"\
"			canvas.__init__ = false;\n"\
"			var grafx = canvas.getContext('2d');\n"\
"			canvas.style.position = 'absolute';\n"\
"			canvas.style.top = '0px';\n"\
"			canvas.style.left = '0px';\n"\
"			canvas.style.height = '100%';\n"\
"			canvas.style.width = '100%';\n"\
"			var FULL_SCREEN = false;\n"\
"			document.body.onmouseup = function(e) {\n"\
"				FULL_SCREEN = !FULL_SCREEN;\n"\
"				if (FULL_SCREEN) {\n"\
"					document.body.requestFullscreen();\n"\
"				} else {\n"\
"					document.exitFullscreen();\n"\
"				}\n"\
"			}\n"\
"			var KEY_BUFF = new Array(0);\n"\
"			var KEY_MAP = new Array(256);\n"\
"			var KEY_SHIFT = false;\n"\
"			var KEY_CTRL = false;\n"\
"			var KEY_ALT = false;\n"\
"			var KEY_WIN = false;\n"\
"			KEY_MAP[8] = 14;\n"\
"			KEY_MAP[9] = 15;\n"\
"			KEY_MAP[13] = 28;\n"\
"			KEY_MAP[16] = 42;\n"\
"			KEY_MAP[17] = 29;\n"\
"			KEY_MAP[18] = 56;\n"\
"			KEY_MAP[19] = 119;\n"\
"			KEY_MAP[20] = 58;\n"\
"			KEY_MAP[27] = 1;\n"\
"			KEY_MAP[32] = 57;\n"\
"			KEY_MAP[33] = 104;\n"\
"			KEY_MAP[34] = 109;\n"\
"			KEY_MAP[35] = 107;\n"\
"			KEY_MAP[36] = 102;\n"\
"			KEY_MAP[37] = 105;\n"\
"			KEY_MAP[38] = 103;\n"\
"			KEY_MAP[39] = 106;\n"\
"			KEY_MAP[40] = 108;\n"\
"			KEY_MAP[45] = 110;\n"\
"			KEY_MAP[46] = 111;\n"\
"			KEY_MAP[48] = 11;\n"\
"			KEY_MAP[49] = 2;\n"\
"			KEY_MAP[50] = 3;\n"\
"			KEY_MAP[51] = 4;\n"\
"			KEY_MAP[52] = 5;\n"\
"			KEY_MAP[53] = 6;\n"\
"			KEY_MAP[54] = 7;\n"\
"			KEY_MAP[55] = 8;\n"\
"			KEY_MAP[56] = 9;\n"\
"			KEY_MAP[57] = 10;\n"\
"			KEY_MAP[65] = 30;\n"\
"			KEY_MAP[66] = 48;\n"\
"			KEY_MAP[67] = 46;\n"\
"			KEY_MAP[68] = 32;\n"\
"			KEY_MAP[69] = 18;\n"\
"			KEY_MAP[70] = 33;\n"\
"			KEY_MAP[71] = 34;\n"\
"			KEY_MAP[72] = 35;\n"\
"			KEY_MAP[73] = 23;\n"\
"			KEY_MAP[74] = 36;\n"\
"			KEY_MAP[75] = 37;\n"\
"			KEY_MAP[76] = 38;\n"\
"			KEY_MAP[77] = 50;\n"\
"			KEY_MAP[78] = 49;\n"\
"			KEY_MAP[79] = 24;\n"\
"			KEY_MAP[80] = 25;\n"\
"			KEY_MAP[81] = 16;\n"\
"			KEY_MAP[82] = 19;\n"\
"			KEY_MAP[83] = 31;\n"\
"			KEY_MAP[84] = 20;\n"\
"			KEY_MAP[85] = 22;\n"\
"			KEY_MAP[86] = 47;\n"\
"			KEY_MAP[87] = 17;\n"\
"			KEY_MAP[88] = 45;\n"\
"			KEY_MAP[89] = 21;\n"\
"			KEY_MAP[90] = 44;\n"\
"			KEY_MAP[91] = 125;\n"\
"			KEY_MAP[92] = 126;\n"\
"			KEY_MAP[112] = 59;\n"\
"			KEY_MAP[113] = 60;\n"\
"			KEY_MAP[114] = 61;\n"\
"			KEY_MAP[115] = 62;\n"\
"			KEY_MAP[116] = 63;\n"\
"			KEY_MAP[117] = 64;\n"\
"			KEY_MAP[118] = 65;\n"\
"			KEY_MAP[119] = 66;\n"\
"			KEY_MAP[120] = 67;\n"\
"			KEY_MAP[121] = 68;\n"\
"			KEY_MAP[122] = 87;\n"\
"			KEY_MAP[123] = 88;\n"\
"			KEY_MAP[186] = 39;\n"\
"			KEY_MAP[187] = 13;\n"\
"			KEY_MAP[188] = 51;\n"\
"			KEY_MAP[189] = 12;\n"\
"			KEY_MAP[190] = 52;\n"\
"			KEY_MAP[191] = 53;\n"\
"			KEY_MAP[192] = 41;\n"\
"			KEY_MAP[219] = 26;\n"\
"			KEY_MAP[220] = 43;\n"\
"			KEY_MAP[221] = 27;\n"\
"			KEY_MAP[222] = 40;\n"\
"\n"\
"			var keySend = function() {\n"\
"				if (KEY_BUFF.length == 0) {\n"\
"					setTimeout(function(){keySend();}, 1);\n"\
"					return;\n"\
"				}\n"\
"				var cmd = 'key=' + KEY_BUFF.splice(0, 1)[0];\n"\
"				if (KEY_CTRL) cmd += '&hold=29';\n"\
"				else if (KEY_ALT) cmd += '&hold=56';\n"\
"				else if (KEY_SHIFT) cmd += '&hold=42';\n"\
"				else if (KEY_WIN) cmd += '&hold=125';\n"\
"				var xhr = new XMLHttpRequest();\n"\
"				xhr.open('POST', '/control', true);\n"\
"				xhr.setRequestHeader('Content-Type', 'text/html');\n"\
"				xhr.onload = function() {keySend();}\n"\
"				xhr.send(cmd);\n"\
"			}\n"\
"			keySend();\n"\
"			document.body.onkeyup = function(e) {\n"\
"				if (e.keyCode == 17) KEY_CTRL = false;\n"\
"				else if (e.keyCode == 18) KEY_ALT = false;\n"\
"				else if (e.keyCode == 16) KEY_SHIFT = false;\n"\
"				else if (e.keyCode == 91 || e.keyCode == 92) KEY_WIN = false;\n"\
"				e.preventDefault();\n"\
"				return false;\n"\
"			}\n"\
"			document.body.onkeydown = function(e) {\n"\
"				if (e.keyCode == 17) KEY_CTRL = true;\n"\
"				else if (e.keyCode == 18) KEY_ALT = true;\n"\
"				else if (e.keyCode == 16) KEY_SHIFT = true;\n"\
"				else if (e.keyCode == 91 || e.keyCode == 92) KEY_WIN = true;\n"\
"				else if (KEY_MAP[e.keyCode] != undefined)\n"\
"					KEY_BUFF.push(KEY_MAP[e.keyCode]);\n"\
"				e.preventDefault();\n"\
"				return false;\n"\
/*"				switch (e.key) {\n"\
"					case '1':\n"\
"						canvas.style.width = '';\n"\
"						canvas.style.height = '';\n"\
"					break;\n"\
"					case '2':\n"\
"						canvas.style.width = '100%';\n"\
"						canvas.style.height = '';\n"\
"					break;\n"\
"					case '3':\n"\
"						canvas.style.width = '';\n"\
"						canvas.style.height = '100%';\n"\
"					break;\n"\
"					case '4':\n"\
"						canvas.style.width = '100%';\n"\
"						canvas.style.height = '100%';\n"\
"					break;\n"\
"				}\n"\
*/
"			}\n"\
"			var img = document.createElement('img');\n"\
"			img_loaded = false;\n"\
"			img.style.display = 'none';\n"\
"			document.body.appendChild(canvas);\n"\
"			img.onload = function() {\n"\
"				if (!canvas.__init__) {\n"\
"					canvas.width = img.width;\n"\
"					canvas.height = img.height;\n"\
"					canvas.__init__ = true;\n"\
"				}\n"\
"				grafx.drawImage(img, 0, 0);\n"\
"				img_loaded = true;\n"\
"			}\n"\
"			document.body.appendChild(img);\n"\
"			function refreshImage() {\n"\
"				img_loaded = false;\n"\
"				img.src = '/screen?time=' + new Date().getTime();\n"\
"			}\n"\
"			setInterval(function() {\n"\
"				if (img_loaded) {\n"\
"					refreshImage();\n"\
"				}\n"\
"			}, 1);\n"\
"			refreshImage();\n"\
"		</script>\n"\
"	</body>\n"\
"</html>";


//-----------------------------------------------------------------------

#ifndef ALIGN_TO_16
#define ALIGN_TO_16(x)  ((x + 15) & ~15)
#endif

//-----------------------------------------------------------------------

#define DEFAULT_DELAY 0
#define DEFAULT_DISPLAY_NUMBER 0
#define DEFAULT_NAME "snapshot.png"
//-----------------------------------------------------------------------

int KEYBOARD_ENABLED = 0;
int KEYBOARD_OPEN = 0;
int POST_OPEN = 0;
const char* program = NULL;

//-----------------------------------------------------------------------

void
usage(void)
{
    fprintf(stderr, "Usage: %s [--pngname name]", program);
    fprintf(stderr, " [--width <width>] [--height <height>]");
    fprintf(stderr, " [--compression <level>]");
    fprintf(stderr, " [--delay <delay>] [--display <number>]");
    fprintf(stderr, " [--stdout] [--help]\n");

    fprintf(stderr, "\n");

    fprintf(stderr, "    --pngname,-p - name of png file to create ");
    fprintf(stderr, "(default is %s)\n", DEFAULT_NAME);

    fprintf(stderr, "    --height,-h - image height ");
    fprintf(stderr, "(default is screen height)\n");

    fprintf(stderr, "    --width,-w - image width ");
    fprintf(stderr, "(default is screen width)\n");

    fprintf(stderr, "    --compression,-c - PNG compression level ");
    fprintf(stderr, "(0 - 9)\n");

    fprintf(stderr, "    --delay,-d - delay in seconds ");
    fprintf(stderr, "(default %d)\n", DEFAULT_DELAY);

    fprintf(stderr, "    --display,-D - Raspberry Pi display number ");
    fprintf(stderr, "(default %d)\n", DEFAULT_DISPLAY_NUMBER);

    fprintf(stderr, "    --stdout,-s - write file to stdout\n");

    fprintf(stderr, "    --help,-H - print this usage information\n");
    fprintf(stderr, "\n");

    fprintf(stderr, "Streaming usage: \n");
    fprintf(stderr, "    Streams the contents of the screen to the web browser at http://ip_address:port_number/view\n");
    fprintf(stderr, "\n");

    fprintf(stderr, "    %s stream - Start streaming on port 8888\n", program);
    fprintf(stderr, "    %s stream [port] - Start streaming on port [port]\n", program);
    fprintf(stderr, "    %s stream [port] [quality] - Stream quality, e.g. 0.5 for 50%c or 1 for 100%c\n", program, '%', '%');
    fprintf(stderr, "    %s stream [port] [quality] [ip_addr] - Only allow a specific IP to connect\n", program);
    fprintf(stderr, "    %s stream [port] [quality] [ip_addr] [control] - Use 1 for the control to enable keyboard input\n", program);
    fprintf(stderr, "    %s stop - Stop streaming\n", program);
    fprintf(stderr, "\n");
}


//-----------------------------------------------------------------------

float REQUESTED_SCALING;
char* DEFAULT_ARGV_BASE;
int
snapshot(
    int argc,
    char *argv[])
{
    int opt = 0;

    bool writeToStdout = false;
    char *pngName = DEFAULT_NAME;
    int32_t requestedWidth = 0;
    int32_t requestedHeight = 0;
    uint32_t displayNumber = DEFAULT_DISPLAY_NUMBER;
    int compression = Z_DEFAULT_COMPRESSION;
    int delay = DEFAULT_DELAY;

    VC_IMAGE_TYPE_T imageType = VC_IMAGE_RGBA32;
    int8_t dmxBytesPerPixel  = 4;

    int result = 0;

    program = basename(argv[0]);

    //-------------------------------------------------------------------

    char *sopts = "c:d:D:Hh:p:w:s";

    struct option lopts[] =
    {
        { "compression", required_argument, NULL, 'c' },
        { "delay", required_argument, NULL, 'd' },
        { "display", required_argument, NULL, 'D' },
        { "height", required_argument, NULL, 'h' },
        { "help", no_argument, NULL, 'H' },
        { "pngname", required_argument, NULL, 'p' },
        { "width", required_argument, NULL, 'w' },
        { "stdout", no_argument, NULL, 's' },
        { NULL, no_argument, NULL, 0 }
    };

    while ((opt = getopt_long(argc, argv, sopts, lopts, NULL)) != -1)
    {
        switch (opt)
        {
        case 'c':

            compression = atoi(optarg);

            if ((compression < 0) || (compression > 9))
            {
                compression = Z_DEFAULT_COMPRESSION;
            }

            break;

        case 'd':

            delay = atoi(optarg);
            break;

        case 'D':

            displayNumber = atoi(optarg);
            break;

        case 'h':

            requestedHeight = atoi(optarg);
            break;

        case 'p':
            pngName = optarg;
            break;

        case 'w':

            requestedWidth = atoi(optarg);
            break;

        case 's':

            writeToStdout = true;
            break;

        case 'H':
        default:

            usage();

            if (opt == 'H')
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                exit(EXIT_FAILURE);
            }

            break;
        }
    }

    //-------------------------------------------------------------------

    bcm_host_init();

    //-------------------------------------------------------------------

    if (delay)
    {
        sleep(delay);
    }

    //-------------------------------------------------------------------

    DISPMANX_DISPLAY_HANDLE_T displayHandle
        = vc_dispmanx_display_open(displayNumber);

    if (displayHandle == 0)
    {
        fprintf(stderr,
                "%s: unable to open display %d\n",
                program,
                displayNumber);

        exit(EXIT_FAILURE);
    }

    DISPMANX_MODEINFO_T modeInfo;
    result = vc_dispmanx_display_get_info(displayHandle, &modeInfo);

    if (result != 0)
    {
        fprintf(stderr, "%s: unable to get display information\n", program);
        exit(EXIT_FAILURE);
    }

    int32_t pngWidth = modeInfo.width;
    int32_t pngHeight = modeInfo.height;

    if (REQUESTED_SCALING != 1) {
      requestedWidth = pngWidth * REQUESTED_SCALING;
      requestedHeight = pngHeight * REQUESTED_SCALING;
    }

    if (requestedWidth > 0)
    {
        pngWidth = requestedWidth;

        if (requestedHeight == 0)
        {
            double numerator = modeInfo.height * requestedWidth;
            double denominator = modeInfo.width;

            pngHeight = (int32_t)ceil(numerator / denominator);
        }
    }

    if (requestedHeight > 0)
    {
        pngHeight = requestedHeight;

        if (requestedWidth == 0)
        {
            double numerator = modeInfo.width * requestedHeight;
            double denominator = modeInfo.height;

            pngWidth = (int32_t)ceil(numerator / denominator);
        }
    }

    //-------------------------------------------------------------------
    // only need to check low bit of modeInfo.transform (value of 1 or 3).
    // If the display is rotated either 90 or 270 degrees (value 1 or 3)
    // the width and height need to be transposed.

    int32_t dmxWidth = pngWidth;
    int32_t dmxHeight = pngHeight;

    if (modeInfo.transform & 1)
    {
        dmxWidth = pngHeight;
        dmxHeight = pngWidth;
    }

    int32_t dmxPitch = dmxBytesPerPixel * ALIGN_TO_16(dmxWidth);

    void *dmxImagePtr = malloc(dmxPitch * dmxHeight);

    if (dmxImagePtr == NULL)
    {
        fprintf(stderr, "%s: unable to allocated image buffer\n", program);
        exit(EXIT_FAILURE);
    }

    //-------------------------------------------------------------------

    uint32_t vcImagePtr = 0;
    DISPMANX_RESOURCE_HANDLE_T resourceHandle;
    resourceHandle = vc_dispmanx_resource_create(imageType,
                                                 dmxWidth,
                                                 dmxHeight,
                                                 &vcImagePtr);

    result = vc_dispmanx_snapshot(displayHandle,
                                  resourceHandle,
                                  DISPMANX_NO_ROTATE);

    if (result != 0)
    {
        vc_dispmanx_resource_delete(resourceHandle);
        vc_dispmanx_display_close(displayHandle);

        fprintf(stderr, "%s: vc_dispmanx_snapshot() failed\n", program);
        exit(EXIT_FAILURE);
    }

    VC_RECT_T rect;
    result = vc_dispmanx_rect_set(&rect, 0, 0, dmxWidth, dmxHeight);

    if (result != 0)
    {
        vc_dispmanx_resource_delete(resourceHandle);
        vc_dispmanx_display_close(displayHandle);

        fprintf(stderr, "%s: vc_dispmanx_rect_set() failed\n", program);
        exit(EXIT_FAILURE);
    }

    result = vc_dispmanx_resource_read_data(resourceHandle,
                                            &rect,
                                            dmxImagePtr,
                                            dmxPitch);


    if (result != 0)
    {
        vc_dispmanx_resource_delete(resourceHandle);
        vc_dispmanx_display_close(displayHandle);

        fprintf(stderr,
                "%s: vc_dispmanx_resource_read_data() failed\n",
                program);

        exit(EXIT_FAILURE);
    }

    vc_dispmanx_resource_delete(resourceHandle);
    vc_dispmanx_display_close(displayHandle);

    //-------------------------------------------------------------------
    // Convert from RGBA (32 bit) to RGB (24 bit)

    int8_t pngBytesPerPixel = 3;
    int32_t pngPitch = pngBytesPerPixel * pngWidth;
    void *pngImagePtr = malloc(pngPitch * pngHeight);

    int32_t j = 0;
    for (j = 0 ; j < pngHeight ; j++)
    {
        int32_t dmxXoffset = 0;
        int32_t dmxYoffset = 0;

        switch (modeInfo.transform & 3)
        {
        case 0: // 0 degrees

            if (modeInfo.transform & 0x20000) // flip vertical
            {
                dmxYoffset = (dmxHeight - j - 1) * dmxPitch;
            }
            else
            {
                dmxYoffset = j * dmxPitch;
            }

            break;

        case 1: // 90 degrees


            if (modeInfo.transform & 0x20000) // flip vertical
            {
                dmxXoffset = j * dmxBytesPerPixel;
            }
            else
            {
                dmxXoffset = (dmxWidth - j - 1) * dmxBytesPerPixel;
            }

            break;

        case 2: // 180 degrees

            if (modeInfo.transform & 0x20000) // flip vertical
            {
                dmxYoffset = j * dmxPitch;
            }
            else
            {
                dmxYoffset = (dmxHeight - j - 1) * dmxPitch;
            }

            break;

        case 3: // 270 degrees

            if (modeInfo.transform & 0x20000) // flip vertical
            {
                dmxXoffset = (dmxWidth - j - 1) * dmxBytesPerPixel;
            }
            else
            {
                dmxXoffset = j * dmxBytesPerPixel;
            }

            break;
        }

        int32_t i = 0;
        for (i = 0 ; i < pngWidth ; i++)
        {
            uint8_t *pngPixelPtr = pngImagePtr
                                 + (i * pngBytesPerPixel)
                                 + (j * pngPitch);

            switch (modeInfo.transform & 3)
            {
            case 0: // 0 degrees

                if (modeInfo.transform & 0x10000) // flip horizontal
                {
                    dmxXoffset = (dmxWidth - i - 1) * dmxBytesPerPixel;
                }
                else
                {
                    dmxXoffset = i * dmxBytesPerPixel;
                }

                break;

            case 1: // 90 degrees

                if (modeInfo.transform & 0x10000) // flip horizontal
                {
                    dmxYoffset = (dmxHeight - i - 1) * dmxPitch;
                }
                else
                {
                    dmxYoffset = i * dmxPitch;
                }

                break;

            case 2: // 180 degrees

                if (modeInfo.transform & 0x10000) // flip horizontal
                {
                    dmxXoffset = i * dmxBytesPerPixel;
                }
                else
                {
                    dmxXoffset = (dmxWidth - i - 1) * dmxBytesPerPixel;
                }

                break;

            case 3: // 270 degrees

                if (modeInfo.transform & 0x10000) // flip horizontal
                {
                    dmxYoffset = i * dmxPitch;
                }
                else
                {
                    dmxYoffset = (dmxHeight - i - 1) * dmxPitch;
                }

                break;
            }

            uint8_t *dmxPixelPtr = dmxImagePtr + dmxXoffset + dmxYoffset;

            memcpy(pngPixelPtr, dmxPixelPtr, 3);
        }
    }

    free(dmxImagePtr);
    dmxImagePtr = NULL;

    //-------------------------------------------------------------------

    png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                                 NULL,
                                                 NULL,
                                                 NULL);

    if (pngPtr == NULL)
    {
        fprintf(stderr,
                "%s: unable to allocated PNG write structure\n",
                program);

        exit(EXIT_FAILURE);
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);

    if (infoPtr == NULL)
    {
        fprintf(stderr,
                "%s: unable to allocated PNG info structure\n",
                program);

        exit(EXIT_FAILURE);
    }

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        fprintf(stderr, "%s: unable to create PNG\n", program);
        exit(EXIT_FAILURE);
    }

    FILE *pngfp = NULL;

    if (writeToStdout)
    {
        pngfp = stdout;
    }
    else
    {
        pngfp = fopen(pngName, "wb");

        if (pngfp == NULL)
        {
            fprintf(stderr,
                    "%s: unable to create %s - %s\n",
                    program,
                    pngName,
                    strerror(errno));

            exit(EXIT_FAILURE);
        }
    }

    png_init_io(pngPtr, pngfp);

    png_set_IHDR(
        pngPtr,
        infoPtr,
        pngWidth,
        pngHeight,
        8,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE,
        PNG_FILTER_TYPE_BASE);

    if (compression != Z_DEFAULT_COMPRESSION)
    {
        png_set_compression_level(pngPtr, compression);
    }

    png_write_info(pngPtr, infoPtr);

    int y = 0;
    for (y = 0; y < pngHeight; y++)
    {
        png_write_row(pngPtr, pngImagePtr + (pngPitch * y));
    }

    png_write_end(pngPtr, NULL);
    png_destroy_write_struct(&pngPtr, &infoPtr);

    if (pngfp != stdout)
    {
        fclose(pngfp);
    }

    //-------------------------------------------------------------------

    free(pngImagePtr);
    pngImagePtr = NULL;

    return 0;
}

void GetImagePath(char *str) {
	char fname[] = ".raspi2png_stream.png";
	char* home = getenv("HOME");
	if (home[strlen(home) - 1] != '/') {
		sprintf(str, "%s/%s%c", home, fname, 0);
	} else {
		sprintf(str, "%s%s%c", home, fname, 0);
	}
}
void GetPIDPath(char *str) {
	char fname[] = ".raspi2png_procid.log";
	char* home = getenv("HOME");
	if (home[strlen(home) - 1] != '/') {
		sprintf(str, "%s/%s%c", home, fname, 0);
	} else {
		sprintf(str, "%s%s%c", home, fname, 0);
	}
}
int streamExists() {
	char fpath[256];
	GetPIDPath(fpath);
	if (access(fpath, F_OK) != 0) {
		return 0;
	}
	return 1;
}
int stopStream(int verbose) {
	char fpath[256];
	GetImagePath(fpath);
	remove(fpath);
	GetPIDPath(fpath);
	if (access(fpath, F_OK) != 0) {
		if (verbose) {
			fprintf(stderr, "No ongoing stream detected.\n");
		}
		return 1;
	}
	if (verbose) {
		char cmd[512];
		sprintf(cmd, "kill -9 $(cat '%s') 2>/dev/null", fpath);
		system(cmd);
	}
	remove(fpath);
	return 0;
}

void SendKey(unsigned short key, int hold) {
	if (!KEYBOARD_ENABLED) {
		return;
	}
	if (KEYBOARD_OPEN) {
		fprintf(stderr, "Attempt to write to keyboard while it is open.\n");
		return;
	}
	KEYBOARD_OPEN = 1;
	struct libevdev *dev;
	struct libevdev_uinput *uidev;
	dev = libevdev_new();
	libevdev_set_name(dev, "rapsi2png keyboard");
	libevdev_enable_event_type(dev, EV_KEY);
	libevdev_enable_event_code(dev, EV_KEY, key, NULL);
	if (hold > 0) {
		libevdev_enable_event_code(dev, EV_KEY, hold, NULL);
	}
	int err = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);
	if (err != 0) {
		fprintf(stderr, "Keyboard emulation failed (run using sudo?).\n");
		stopStream(0);
		exit(1);
	}

	if (hold > 0) {
		libevdev_uinput_write_event(uidev, EV_KEY, hold, 1);
		libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
	}
	libevdev_uinput_write_event(uidev, EV_KEY, key, 1);
	libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
	libevdev_uinput_write_event(uidev, EV_KEY, key, 0);
	libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
	if (hold > 0) {
		libevdev_uinput_write_event(uidev, EV_KEY, hold, 0);
		libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
	}
	libevdev_uinput_destroy(uidev);
	KEYBOARD_OPEN = 0;
}

/*int ConnInfo_Callback(
	void *cls,
	enum MHD_ValueKind kind,
	const char *key,
	const char *value
) {
	printf("[%s] %s\n", key, value);
	return MHD_YES;
}*/
char ALLOWED_IP[32];
int ConnInit_Callback (
	void *cls,
	const struct sockaddr *addr,
	socklen_t addrlen
) {
	if (strlen(ALLOWED_IP) == 0) {
		return MHD_YES;
	}
	struct sockaddr_in* sock = (struct sockaddr_in*)addr;
	if (strcmp(inet_ntoa(sock->sin_addr), ALLOWED_IP) == 0) {
		return MHD_YES;
	}
	return MHD_NO;
}

int ConnProc_Callback(
	void *cls,
	struct MHD_Connection *conn,
	const char *url,
	const char *method,
	const char *version,
	const char *upload_data,
	size_t *upload_data_size,
	void **con_cls
) {
	//MHD_get_connection_values(conn, MHD_HEADER_KIND, &ConnInfo_Callback, NULL);
	const char *pageNotFound = "<html><body><h1>404 Page not found.</h1></body></html>";
	int ret = MHD_NO;
	struct MHD_Response *response = NULL;
	if (strcmp(method, "GET") == 0) {
		if (strcmp(url, "/view") == 0) {
			response = MHD_create_response_from_buffer(
				strlen(VIEW_PAGE),
				(void*)VIEW_PAGE,
				MHD_RESPMEM_PERSISTENT
			);
			ret = MHD_queue_response(conn, MHD_HTTP_OK, response);
		} else if (strcmp(url, "/screen") == 0) {
			char path[256];
			GetImagePath(path);
			char* argv[3];
			argv[0] = DEFAULT_ARGV_BASE;
			argv[1] = "-p";
			argv[2] = path;
			program = NULL;
			optind = 1;
			snapshot(3, argv);
			int fd = open(path, O_RDONLY);
			if (fd == 0) {
				fprintf(stderr, "Permission error.\n");
				stopStream(0);
				exit(1);
			}
			struct stat buf;
			fstat(fd, &buf);
			response = MHD_create_response_from_fd_at_offset64(buf.st_size, fd, 0);
			MHD_add_response_header(response, "Content-Type", "image/png");
			ret = MHD_queue_response(conn, MHD_HTTP_OK, response);
		} else {
			response = MHD_create_response_from_buffer(
				strlen(pageNotFound),
				(void*)pageNotFound,
				MHD_RESPMEM_PERSISTENT
			);
			ret = MHD_queue_response(conn, 404, response);
		}
	} else if (strcmp(method, "POST") == 0) {
		static char* data;
		static size_t data_size;
		if (*con_cls == (void*)0) {
			if (POST_OPEN) {
				fprintf(stderr, "POST requests sent too fast.");
				return MHD_NO;
			}
			*con_cls = (void*)1;
			data = malloc(0);
			data_size = 0;
			POST_OPEN = 1;
			return MHD_YES;
		} else if (*upload_data_size > 0) {
			data_size += *upload_data_size;
			if ((data = realloc(data, data_size)) == NULL) {
				fprintf(stderr, "Severe memory error.\n");
				stopStream(0);
				exit(1);
			}
			memcpy(data + (data_size - *upload_data_size), upload_data, *upload_data_size);
			*upload_data_size = 0; //this is necessary for the next recursion to be called
			return MHD_YES;
		} else {
			if ((data = realloc(data, data_size + 1)) == NULL) {
				fprintf(stderr, "Severe memory error.\n");
				stopStream(0);
				exit(1);
			}
			data[data_size] = 0;
			const int maxKeys = 4;
			int pos[maxKeys * 2];
			int dataFound = 0;
			if (data_size > 0) {
				pos[0] = 0;
				dataFound = 1;
			}
			for (int i = 1; i < data_size; i++) {
				if (data[i] == '&' || data[i] == '=') {
					if (i < data_size - 1) {
						pos[dataFound++] = i + 1;
					}
					data[i] = 0;
					if (dataFound >= maxKeys * 2) {
						break;
					}
				}
			}
			int keyToSend = -1;
			int keyHold = -1;
			for (int i = 0; i < dataFound - (dataFound % 2); i += 2) {
				char *key = data + pos[i];
				char *val = data + pos[i + 1];
				if (strcmp(key, "key") == 0) {
					keyToSend = atoi(val);
				}
				if (strcmp(key, "hold") == 0) {
					keyHold = atoi(val);
				}
			}
			if (keyToSend != -1) {
				SendKey(keyToSend, keyHold);
			}
			free(data);
			response = MHD_create_response_from_buffer(
				strlen(pageNotFound),
				(void*)pageNotFound,
				MHD_RESPMEM_PERSISTENT
			);
			ret = MHD_queue_response(conn, MHD_HTTP_OK, response);
			POST_OPEN = 0;
		}
	}
	if (response != NULL) {
		MHD_destroy_response(response);
	}
	return ret;
}
int stream(int argc, char** argv) {
	if (streamExists()) {
		fprintf(stderr, "A stream is already running.\n");
		return 1;
	}
	pid_t procid = getpid();
	char fpath[256];
	GetPIDPath(fpath);
	FILE* file = fopen(fpath, "wb");
	if (file == NULL) {
		fprintf(stderr, "Permission error.\n");
		return 1;
	}
	fprintf(file, "%i\n", procid);
	fclose(file);
	int port = 8888;
	if (argc >= 3) {
		port = atoi(argv[2]);
	}
	if (argc >= 4) {
		REQUESTED_SCALING = atof(argv[3]);
		if (REQUESTED_SCALING > 1) {
			fprintf(stderr, "Scaling factor cannot be greater than 1.\n");
			stopStream(0);
			return 1;
		} else if (REQUESTED_SCALING <= 0) {
			fprintf(stderr, "The scaling factor cannot be less than or equal to zero.\n");
			stopStream(0);
			return 1;
		}
	}
	if (argc >= 5) {
		memcpy(ALLOWED_IP, argv[4], strlen(argv[4]) + 1);
	}
	if (argc >= 6) {
		if (argv[5][0] == '1') {
			KEYBOARD_ENABLED = 1;
		}
	}
	//printf("Starting stream on port %i...", port);
	struct MHD_Daemon* d = MHD_start_daemon(
		MHD_USE_THREAD_PER_CONNECTION,
		port,
		&ConnInit_Callback,
		NULL,
		&ConnProc_Callback,
		NULL,
		MHD_OPTION_END
	);
	if (d == NULL) {
		fprintf(stderr, "Failed to start daemon.\n");
		stopStream(0);
		return 1;
	}
	while (true);
	MHD_stop_daemon(d);
	return 0;
}
int main(int argc, char** argv) {
	ALLOWED_IP[0] = 0;
	REQUESTED_SCALING = 1;
	DEFAULT_ARGV_BASE = argv[0];
	if (argc < 2) {
		return snapshot(argc, argv);
	} else if (strcmp(argv[1], "stop") == 0) {
		return stopStream(1);
	} else if (strcmp(argv[1], "stream") != 0) {
		return snapshot(argc, argv);
	} else {
		return stream(argc, argv);
	}
}
