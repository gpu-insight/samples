/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2018 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glxext.h>

void print_x_visualinfo(XVisualInfo *visinfo)
{
    assert(NULL != visinfo);

    std::cout << "\nThe following XVisualInfo best matched:\n";
    std::cout << std::setw(20) << "Visual:" << visinfo->visual << "\n";
    std::cout << std::setw(20) << "VisualID:" << visinfo->visualid << "\n";
    std::cout << std::setw(20) << "screen:" << visinfo->screen << "\n";
    std::cout << std::setw(20) << "depth:" << visinfo->depth << "\n";
#if defined(__cplusplus) || defined(c_plusplus)
    std::cout << std::setw(20) << "c_class:" << visinfo->c_class << "\n";
#else
    std::cout << std::setw(20) << "class:" << visinfo->class << "\n";
#endif
    std::cout << std::setw(20) << "red_mask:" << std::hex << visinfo->red_mask << "\n";
    std::cout << std::setw(20) << "green_mask:" << visinfo->green_mask << "\n";
    std::cout << std::setw(20) << "blue_mask:" << visinfo->blue_mask << std::dec << "\n";
    std::cout << std::setw(20) << "colormap_size:" << visinfo->colormap_size << "\n";
    std::cout << std::setw(20) << "bits_per_rgb:" << visinfo->bits_per_rgb << "\n";
}

int
main(int argc, char *argv[])
{
    Display *dpy;
    char *dpyName = getenv("DISPLAY");

    dpy = XOpenDisplay(dpyName);
    if (!dpy) {
        std::cout << "Error: couldn't open display " << dpyName << "\n";
        return -1;
    }

    int attrib[] = { GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                     GLX_RENDER_TYPE,   GLX_RGBA_BIT,
                     GLX_RED_SIZE,      1,
                     GLX_GREEN_SIZE,    1,
                     GLX_BLUE_SIZE,     1,
                     GLX_DOUBLEBUFFER,  GL_TRUE,
                     GLX_DEPTH_SIZE,    1,
                     None };

    XVisualInfo * visinfo;
    GLXFBConfig * fbconfig;
    GLXContext ctx = NULL;
    XSetWindowAttributes attr;
    Window root;
    Window win;
    int num_configs;
    int scrnum;
    unsigned long mask;

    scrnum = DefaultScreen(dpy);
    root = RootWindow(dpy, scrnum);

    fbconfig = glXGetFBConfigs(dpy, scrnum, &num_configs);
    if (fbconfig == NULL) {
        std::cout << "Error: couldn't get an RGB, Double-buffered visual\n";
        exit(1);
    }
    std::cout << "Totol "<< num_configs << " fbconfigs are available on the specified screen(display).\n";

    num_configs = 0;
    fbconfig = glXChooseFBConfig(dpy, scrnum, attrib, &num_configs);
    if (fbconfig == NULL) {
        std::cout << "Error: couldn't get an RGB, Double-buffered visual\n";
        exit(1);
    }
    std::cout << "Totol "<< num_configs << " fbconfigs meet the requirements.\n";

    ctx = glXCreateNewContext(dpy, fbconfig[0], GLX_RGBA_TYPE, NULL, true);
    if (ctx == NULL) {
        std::cout << "Error: couldn't create an RGB, Double-buffered context\n";
        exit(1);
    }

    visinfo = glXChooseVisual(dpy, scrnum, attrib);
    if (visinfo == NULL) {
        std::cout << "Error: couldn't get an RGB, Double-buffered visual\n";
        exit(1);
    }

    print_x_visualinfo(visinfo);

    /* window attributes */
    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap( dpy, root, visinfo->visual, AllocNone);
    attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
    /* XXX this is a bad way to get a borderless window! */
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    win = XCreateWindow(dpy, root, 0, 0, 300, 300,
                        0, visinfo->depth, InputOutput,
                        visinfo->visual, mask, &attr);
    XSizeHints sizeHints;
    sizeHints.flags = USPosition;
    sizeHints.x = 10;
    sizeHints.y = 10;

    XSetStandardProperties(dpy, win, "Botson GLX Demo", "", None, 0, 0, &sizeHints);
    XMapWindow(dpy, win);
    XEvent event;

    XIfEvent(dpy, &event, [](Display *display, XEvent *event, char *windowPointer) -> Bool {
        return (event->type == MapNotify && event->xmap.window == (*((Window *) windowPointer)));
    }, (char *) &win);
    XSetWMColormapWindows(dpy, win, &win, 1);

    if (!glXMakeContextCurrent(dpy, win, win, ctx))
    {
        std::cout << "Error: couldn't bind the GLXContext and Window\n";
        exit(1);
    }

    glXSwapBuffers(dpy, win);

    ctx = glXGetCurrentContext();
    if (ctx == NULL) {
        std::cout << "Error: couldn't get the current context\n";
        exit(1);
    }

    Bool is_direct = glXIsDirect(dpy, ctx);
    assert(is_direct == true);

    int errBase, evtBase;
    int major, minor;

    Bool result = glXQueryExtension(dpy, &errBase, &evtBase);
    if (result)
    {
        std::cout << "errorBase: " << errBase << ", eventBase: " << evtBase << "\n";
    }
    else
    {
        std::cout << "X server supports no GLX extension\n";
    }

    result = glXQueryVersion(dpy, &major, &minor);
    if (result)
    {
        std::cout << "GLX extension version: " << major << "." << minor << "\n";
    }

    const char *str = glXQueryExtensionsString(dpy, scrnum);
    if (!str)
    {
        std::cout << "Error: couldn't get GLX extensions string\n";
    }
    else
    {
        std::cout << "glXQueryExtensionsString() >>>\n" << str << "\n";
    }

    const char *client_exts = glXGetClientString(dpy, GLX_EXTENSIONS);
    if (!client_exts)
    {
        std::cout << "Error: couldn't get GLX extensions string\n";
    }
    else
    {
        std::cout << "glXGetClientString() >>>\n" << client_exts << "\n";
    }

    sleep(2);

    return 0;
}
