#include "Base.h"
#include "Platform.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <sys/time.h>
#include "glew/include/glxew.h"
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <fstream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;
struct timespec timespec;
static double timeStart;
static double timeAbsolute;

namespace KillerbyteGameEngine
{
	double timespec2millis(struct timespec *a)
	{
		return (1000.0 * a->tv_sec) + (0.000001 * a->tv_nsec);
	}
  
	Platform::~Platform()
	{
		
	}
	 
	void Platform::Initialize(Game* game)
	{
		dpy = XOpenDisplay(NULL);

		if(dpy == NULL) {
			printf("\n\tcannot connect to X server\n\n");
			//exit(0);
		}

		root = DefaultRootWindow(dpy);

		vi = glXChooseVisual(dpy, 0, att);

		if(vi == NULL) {
			printf("\n\tno appropriate visual found\n\n");
			//exit(0);
		} 
		else {
			printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
		}


		cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask;

		win = XCreateWindow(dpy, root, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

		XMapWindow(dpy, win);
		XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);

		glEnable(GL_DEPTH_TEST); 
	}
	
	void DrawAQuad() {
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-1., 1., -1., 1., 1., 20.);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
		
		glBegin(GL_QUADS);
		glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
		glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
		glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
		glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
		glEnd();
	} 
	 
	void Platform::Run()
	{
		bool finished = false;
		
		while (!finished)
		{
			XNextEvent(dpy, &xev);

			if(xev.type == Expose) {
				XGetWindowAttributes(dpy, win, &gwa);
				ResizeEvent(gwa.width, gwa.height);
				DrawAQuad(); // Game Render code here 
				glXSwapBuffers(dpy, win);
			}
			else if(xev.type == KeyPress) {
				finished = true;
			}
		}
	}
	 
	void Platform::Shutdown()
	{
		glXMakeCurrent(dpy, None, NULL);
		glXDestroyContext(dpy, glc);
		
		//XDestroyWindow(dpy, win);
		XFreeColormap(dpy, cmap);
		XCloseDisplay(dpy); 
	}
	
	unsigned int Platform::getDisplayWidth()
	{
		XWindowAttributes windowAttribs;
		XGetWindowAttributes(dpy, win, &windowAttribs);
		return windowAttribs.width;
	}
	
	unsigned int Platform::getDisplayHeight()
	{
		XWindowAttributes windowAttribs;
		XGetWindowAttributes(dpy, win, &windowAttribs);
		return windowAttribs.height;
	}
	
	double Platform::GetAbsoluteTime()
	{
		clock_gettime(CLOCK_REALTIME, &timespec);
        	double now = timespec2millis(&timespec);
        	timeAbsolute = now - timeStart;

        	return timeAbsolute;
	}
	
	void Platform::SetAbsoluteTime(double time)
	{
		timeAbsolute = time;
	}
}