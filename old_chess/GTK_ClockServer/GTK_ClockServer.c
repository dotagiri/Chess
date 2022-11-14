/* GTK_ClockServer.c: GUI example TCP/IP server with timeout support
 * Author: Rainer Doemer, 2/23/17 (based on simple ClockServer.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <math.h>

/* #define DEBUG */	/* be verbose */
#define BUFFSIZE 256
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/*** type definitions ****************************************************/

typedef void (*ClientHandler)(int DataSocketFD);
typedef void (*TimeoutHandler)(void);

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;
int Shutdown		/* keep running until Shutdown == 1 */
	= 0;
char ClockBuffer[26]	/* current time in printable format */
	= "";
GtkLabel *DigitalClock	/* label widget displaying digital time */
	= NULL;
GtkWidget *AnalogClock	/* drawing widget displaying analog clock */
	= NULL;

/*** GUI functions *******************************************************/

gboolean DrawAreaExposed(	/* drawing area is displayed, */
	GtkWidget *Widget,	/* render an analog clock     */
	GdkEventExpose *Event,
	gpointer Data)
{
    GtkWidget *DrawArea;
    gint Width, Height;
    cairo_t *cr;
    int h, m, s;
    double AngleH, AngleM, AngleS;

#ifdef DEBUG
    printf("%s: DrawAreaExposed callback starting...\n", Program);
#endif
    DrawArea = Widget;
    Width = DrawArea->allocation.width;
    Height = DrawArea->allocation.height;
#ifdef DEBUG
    printf("%s: Drawing area width=%d, height=%d.\n", Program, Width, Height);
#endif
    /* prepare a cairo context for the drawing */
    cr = gdk_cairo_create(DrawArea->window);
    /* draw a white rectangular background */
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_rectangle(cr, 0, 0, Width, Height);
    cairo_fill(cr);
    /* draw a black circle */
    cairo_translate(cr, Width / 2.0, Height / 2.0);
    cairo_scale(cr, Width / 2.0, Height / 2.0);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_arc(cr, 0.0, 0.0, 1.0, 0.0, 2 * M_PI);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_arc(cr, 0.0, 0.0, 0.95, 0.0, 2 * M_PI);
    cairo_fill(cr);
    /* get the current time */
    h =(ClockBuffer[11]-'0')*10 + ClockBuffer[12]-'0';
    m =(ClockBuffer[14]-'0')*10 + ClockBuffer[15]-'0';
    s =(ClockBuffer[17]-'0')*10 + ClockBuffer[18]-'0';
#ifdef DEBUG
    printf("%s: h=%d, m=%d, s=%d.\n", Program, h,m,s);
#endif
    if (h<0 || h>23 || m<0 || m>59 || s<0 || s>59)
    {
	return TRUE; /* time invalid, don't draw hands */
    }
    h = h % 12;
    AngleH = (h+m/60.0) * (2*M_PI/12);
    AngleM = (m+s/60.0) * (2*M_PI/60);
    AngleS = s * (2*M_PI/60);
    /* draw the three clock hands */
    cairo_set_line_width(cr, 0.1);
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, sin(AngleH)*0.7, -cos(AngleH)*0.7);
    cairo_stroke(cr);
    cairo_set_line_width(cr, 0.05);
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, sin(AngleM)*0.85, -cos(AngleM)*0.85);
    cairo_stroke(cr);
    cairo_set_line_width(cr, 0.01);
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_line_to(cr, sin(AngleS)*0.95, -cos(AngleS)*0.95);
    cairo_stroke(cr);
    /* delete the cairo context (free its memory) */
    cairo_destroy(cr);
#ifdef DEBUG
    printf("%s: DrawAreaExposed callback done.\n", Program);
#endif
    return TRUE; /* area drawn, done with expose event */
} /* end of DrawAreaExposed */

void ShutdownClicked(		/* shutdown button was clicked */
	GtkWidget *Widget,
	gpointer Data)
{
#ifdef DEBUG
    printf("%s: ShutdownClicked callback starting...\n", Program);
#endif
    Shutdown = 1;	/* initiate server shutdown */
    DigitalClock = NULL;/* turn clocks off */
    AnalogClock = NULL;
#ifdef DEBUG
    printf("%s: ShutdownClicked callback done.\n", Program);
#endif
} /* end of ShutdownClicked */

GtkWidget *CreateWindow(	/* create the server window */
	int *argc,
	char **argv[])
{
    GtkWidget *Window;
    GtkWidget *VBox, *DrawArea, *Frame, *Label;
    GtkWidget *ShutdownButton;

    /* initialize the GTK libraries */
    gtk_init(argc, argv);

    /* create the main, top level window */
    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(Window), Program);
    gtk_window_set_default_size(GTK_WINDOW(Window), 260, 280);
    gtk_container_set_border_width (GTK_CONTAINER(Window), 10);

    /* overall vertical arrangement in the window */
    VBox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(Window), VBox);

    /* on the top, put a drawing area */
    DrawArea = gtk_drawing_area_new();
    gtk_widget_set_size_request(DrawArea, 250, 250);
    gtk_container_add(GTK_CONTAINER(VBox), DrawArea);

    /* in the middle, a frame with the digital display of the time */
    Frame = gtk_frame_new("Time and Date");
    gtk_container_add(GTK_CONTAINER(VBox), Frame);
    Label = gtk_label_new("n/a");
    gtk_container_add(GTK_CONTAINER(Frame), Label);

    /* on the bottom, a button to shutdown the server and quit */
    ShutdownButton = gtk_button_new_with_label("Shutdown Server and Quit");
    gtk_container_add(GTK_CONTAINER(VBox), ShutdownButton);

    /* make sure that everything becomes visible */
    gtk_widget_show_all(Window);

    /* connect drawing area with function to render a clock */
    g_signal_connect(DrawArea, "expose_event",
			G_CALLBACK(DrawAreaExposed), NULL);

    /* make clock widgets public */
    DigitalClock = (GtkLabel*)Label;
    AnalogClock = DrawArea;

    /* connect window-close with function terminating this server */
    g_signal_connect(Window, "destroy",
			G_CALLBACK(ShutdownClicked), NULL);

    /* connect shutdown button with function terminating this server */
    g_signal_connect(ShutdownButton, "clicked",
                        G_CALLBACK(ShutdownClicked), NULL);

    return(Window);
} /* end of CreateWindow */

void UpdateWindow(void)		/* render the window on screen */
{
   /* this server has it's own main loop for handling client connections;
    * as such, it can't have the usual GUI main loop (gtk_main);
    * instead, we call this UpdateWindow function on regular basis
    */
    while(gtk_events_pending())
    {
	gtk_main_iteration();
    }
} /* end of UpdateWindow */

void DisplayCurrentTime(void)	/* update and display the current real time */
{
    time_t CurrentTime;
    char   *TimeString;

    CurrentTime = time(NULL);
    TimeString = ctime(&CurrentTime);
    strncpy(ClockBuffer, TimeString, 25);
    ClockBuffer[24] = 0;
#ifdef DEBUG
    printf("\r%s: current time is %s", Program, ClockBuffer);
    fflush(stdout);
#endif
    if (DigitalClock)	/* if digital clock is functional, */
    {
	gtk_label_set_label(DigitalClock, ClockBuffer);	/* update it! */
    }
    if (AnalogClock)	/* if analog clock is functional, */
    {
	gdk_window_invalidate_rect(AnalogClock->window,	/* update it! */
		&AnalogClock->allocation, /* invalidate entire region */
		FALSE);	/* no children */
    }
} /* end of DisplayCurrentTime */

/*** global functions ****************************************************/

void FatalError(		/* print error diagnostics and abort */
	const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */

int MakeServerSocket(		/* create a socket on this server */
	uint16_t PortNo)
{
    int ServSocketFD;
    struct sockaddr_in ServSocketName;

    /* create the socket */
    ServSocketFD = socket(PF_INET, SOCK_STREAM, 0);
    if (ServSocketFD < 0)
    {   FatalError("service socket creation failed");
    }
    /* bind the socket to this server */
    ServSocketName.sin_family = AF_INET;
    ServSocketName.sin_port = htons(PortNo);
    ServSocketName.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ServSocketFD, (struct sockaddr*)&ServSocketName,
		sizeof(ServSocketName)) < 0)
    {   FatalError("binding the server to a socket failed");
    }
    /* start listening to this socket */
    if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
    {   FatalError("listening on socket failed");
    }
    return ServSocketFD;
} /* end of MakeServerSocket */

void ProcessRequest(		/* process a time request by a client */
	int DataSocketFD)
{
    int  l, n;
    char RecvBuf[256];	/* message buffer for receiving a message */
    char SendBuf[256];	/* message buffer for sending a response */

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0) 
    {   FatalError("reading from data socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received message: %s\n", Program, RecvBuf);
#endif
    if (0 == strcmp(RecvBuf, "TIME"))
    {   strncpy(SendBuf, "OK TIME: ", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClockBuffer, sizeof(SendBuf)-1-strlen(SendBuf));
    }
    else if (0 == strcmp(RecvBuf, "SHUTDOWN"))
    {   Shutdown = 1;
	strncpy(SendBuf, "OK SHUTDOWN", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
    }
    else
    {   strncpy(SendBuf, "ERROR unknown command ", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
    }
    l = strlen(SendBuf);
#ifdef DEBUG
    printf("%s: Sending response: %s.\n", Program, SendBuf);
#endif
    n = write(DataSocketFD, SendBuf, l);
    if (n < 0)
    {   FatalError("writing to data socket failed");
    }
} /* end of ProcessRequest */

void ServerMainLoop(		/* simple server main loop */
	int ServSocketFD,		/* server socket to wait on */
	ClientHandler HandleClient,	/* client handler to call */
	TimeoutHandler HandleTimeout,	/* timeout handler to call */
	int Timeout)			/* timeout in micro seconds */
{
    int DataSocketFD;	/* socket for a new client */
    socklen_t ClientLen;
    struct sockaddr_in
	ClientAddress;	/* client address we connect with */
    fd_set ActiveFDs;	/* socket file descriptors to select from */
    fd_set ReadFDs;	/* socket file descriptors ready to read from */
    struct timeval TimeVal;
    int res, i;

    FD_ZERO(&ActiveFDs);		/* set of active sockets */
    FD_SET(ServSocketFD, &ActiveFDs);	/* server socket is active */
    while(!Shutdown)
    {
	UpdateWindow();	/* update the GUI window */
	ReadFDs = ActiveFDs;
	TimeVal.tv_sec  = Timeout / 1000000;
	TimeVal.tv_usec = Timeout % 1000000;
	/* block until input arrives on active sockets or until timeout */
	res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);
	if (res < 0)
	{   FatalError("wait for input or timeout (select) failed");
	}
	if (res == 0)	/* timeout occurred */
	{
	    HandleTimeout();
	}
	else		/* some FDs have data ready to read */
	{   for(i=0; i<FD_SETSIZE; i++)
	    {   if (FD_ISSET(i, &ReadFDs))
		{   if (i == ServSocketFD)
		    {	/* connection request on server socket */
#ifdef DEBUG
			printf("%s: Accepting new client...\n", Program);
#endif
			ClientLen = sizeof(ClientAddress);
			DataSocketFD = accept(ServSocketFD,
				(struct sockaddr*)&ClientAddress, &ClientLen);
			if (DataSocketFD < 0)
			{   FatalError("data socket creation (accept) failed");
			}
#ifdef DEBUG
			printf("%s: New client connected from %s:%hu.\n",
				Program,
				inet_ntoa(ClientAddress.sin_addr),
				ntohs(ClientAddress.sin_port));
#endif
			FD_SET(DataSocketFD, &ActiveFDs);
		    }
		    else
		    {   /* active communication with a client */
#ifdef DEBUG
			printf("%s: Dealing with client on FD%d...\n",
				Program, i);
#endif
			HandleClient(i);
#ifdef DEBUG
			printf("%s: Closing client connection FD%d.\n",
				Program, i);
#endif
			close(i);
			FD_CLR(i, &ActiveFDs);
		    }
		}
	    }
	}
    }
} /* end of ServerMainLoop */

/*** main function *******************************************************/

int main(			/* the main function */
	int argc,
	char *argv[])
{
    int ServSocketFD;	/* socket file descriptor for service */
    int PortNo;		/* port number */
    GtkWidget *Window;	/* the server window */

    Program = argv[0];	/* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", Program);
#endif
    if (argc < 2)
    {   fprintf(stderr, "Usage: %s port\n", Program);
	exit(10);
    }
    PortNo = atoi(argv[1]);	/* get the port number */
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Creating the server socket...\n", Program);
#endif
    ServSocketFD = MakeServerSocket(PortNo);

#ifdef DEBUG
    printf("%s: Creating the server window...\n", Program);
#endif
    Window = CreateWindow(&argc, &argv);
    if (!Window)
    {   fprintf(stderr, "%s: cannot create GUI window\n", Program);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Providing current time at port %d...\n", Program, PortNo);
#endif
    ServerMainLoop(ServSocketFD, ProcessRequest,
			DisplayCurrentTime, 250000);
#ifdef DEBUG
    printf("\n%s: Shutting down.\n", Program);
#endif
    close(ServSocketFD);
    return 0;
} /* end of main */

/* EOF GTK_ClockServer.c */
