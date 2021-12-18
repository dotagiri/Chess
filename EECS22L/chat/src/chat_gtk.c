//command line to run: gcc chat_gtk.c -o runchat `pkg-config --cflags --libs gtk+-2.0`
//Daisuke: try this command line if it doesn't work:
//gcc 'pkg-config --cflags gtk+-2.0' chat gtk.c -o chat.gtk 'pkg-config --libs gtk+-2.0'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include "UserList.h"
#include "chat_gtk.h"
#include "Chat.h"

GtkTextBuffer *buffer;
GtkTextIter iter;

/*** global variables***/
const char *Program = NULL; /*program name for descriptive diagnostics*/
int Shutdown = 0;
GtkWidget *list;
static GtkWidget *entry1;
static GtkWidget *entry2;
static GtkWidget *reg_entry1;
static GtkWidget *reg_entry2;
static GtkWidget *reg_entry3;

const gchar *entry_text; 
int client_Socket; 

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry)
{
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
  
  if(strcmp(entry_text,"USERS") == 0)	//strcmp returns zero if true
		{	
			send(client_Socket,entry_text,1024,0);	//gets a list of users from the server
			//printf("USERS is working!\n");
		}
  
  char input[1024] = {0};
  int length = strlen (entry_text);
  //printf("\nlength of string is %d\n", length);
  int i = 0;
		for (i=0; i< length; i++)
		{
			if (entry_text[i] != ' ')      
				input[i] = entry_text[i];
			else
				input[i] = '\0';
		}
		
  if(strcmp(input,"SEND") == 0)	//in order to send a message
		{
			send(client_Socket,input,1024,0);
			
			input[0] = entry_text[5];
			input[1] = '\0';
			send(client_Socket,input,1024,0);
			
			int k = 7;
			int j = 0;
			while (entry_text[k] != '\0')
			{
				input[j] = entry_text[k];
				k++;
				j++;
			}
	
			input[j] = '\0';
			printf("\nMessage sent is %s\n", input);
			send(client_Socket,input,1024,0);
			
			//printf("SEND is working!\n\n");
		}
  
  gtk_text_buffer_insert(buffer, &iter, "\n", -1);
  gtk_text_buffer_insert(buffer, &iter, entry_text, -1);
  gtk_text_buffer_insert(buffer, &iter, "\n", -1);
}

void hide(GtkWidget *Widget)
{
	gtk_widget_hide(Widget);
} /*end of hide*/


void LoginButton(GtkWidget *button, gpointer data)
{
	const gchar *username;
	const gchar *password;

	username = gtk_entry_get_text(GTK_ENTRY(entry1));	
	password = gtk_entry_get_text(GTK_ENTRY(entry2));
	mainMenu();
} /*end of LoginFunction*/

void RegistrationButton(GtkWidget *button, gpointer data)
{
	gchar r_username[20];
	gchar r_password[20];
	gchar retype_password[20];
	//const gchar *username;
	//const gchar *password;

	g_print("Register Process");
	strcpy(r_username, gtk_entry_get_text(GTK_ENTRY(reg_entry1)));
	strcpy(r_password, gtk_entry_get_text(GTK_ENTRY(reg_entry2)));
	strcpy(retype_password, gtk_entry_get_text(GTK_ENTRY(reg_entry3)));
	g_print("Password: %s", r_password);
	g_print("Retype Password: %s", retype_password);

	if (strcmp(retype_password, r_password) != 0){
		g_print("Passwords don't match");
		}
	
} /*end of RegistrationFunction*/


void AddUserButton(GtkWidget *button, gpointer data)
{	
	//gchar username[20];
	//const gchar* friend_username;
} /*end of AddUserButton*/

void add_Friend(GtkWidget *widget, gpointer name){
   GtkListStore *storage;
   GtkTreeIter iter; 
   const gchar *str = gtk_entry_get_text(name);
   storage = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
   gtk_list_store_append(storage,&iter);
   gtk_list_store_set(storage,&iter,0,str,-1);
   gtk_entry_set_text(name,"");
}

void delete_Friend(GtkWidget *widget, gpointer name){
   GtkListStore *storage;
   GtkTreeModel *model;
   GtkTreeIter iter;
   storage =GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
   model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));
   if(gtk_tree_model_get_iter_first(model,&iter)==FALSE){
	return;
   }
   if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(name),&model,&iter)){
	gtk_list_store_remove(storage,&iter);	
   }
}

void init_list(GtkWidget *list){
  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *col;
  GtkListStore       *storage;

  renderer = gtk_cell_renderer_text_new();
  col = gtk_tree_view_column_new_with_attributes("List Item",
          renderer, "text",0, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), col);

  storage = gtk_list_store_new(1, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(storage));

  g_object_unref(storage);
}

void destroyWindow(GtkWidget *window){
   gtk_widget_destroy(window);
}

void Create_ChatWindow ()
{	
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entry;
    //GtkWidget *button;
    GtkWidget *view;
	
    //gtk_init (&argc, &argv);
	
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 700, 350);
    gtk_window_set_title (GTK_WINDOW (window), "Chess Chat Window");
	
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
	
    view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 0);
    gtk_widget_show (view);
	
    //without this line below, segmentation fault occurs
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
		
    g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event",G_CALLBACK (gtk_widget_destroy), window);
	
    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate",G_CALLBACK (enter_callback), entry);		  
    gtk_text_buffer_insert(buffer, &iter, "Hello, welcome to chess chat\n", -1);			
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);
	
/*
    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (button, "clicked",G_CALLBACK (gtk_widget_destroy),window);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
    gtk_widget_set_can_default (button, TRUE);
    gtk_widget_grab_default (button);
    gtk_widget_show (button);
*/
	
    gtk_widget_show  (window);
    
    gtk_main ();

//    return window;
} /*end of Create_ChatWindow*/

void Create_RegisterWindow()
{
	GtkWidget *Window;
	GtkWidget *HBox, *HBox1, *HBox2, *HBox3, *HBox4;
	GtkWidget *Label1, *Label2, *Label3;
//	GtkWidget *entry1, *entry2, *entry3;
	GtkWidget *button1, *button2;
	GtkWidget *Vbox;
	GtkWidget *adjustment;
//	GtkWidget *popup;
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(G_OBJECT(Window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_window_set_title(GTK_WINDOW(Window), "Register");
	gtk_window_set_position(GTK_WINDOW(Window), GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(Window, 480, 270);

	adjustment=gtk_alignment_new(0.5,0.5,0,0);
	HBox=gtk_hbox_new(1,0);
        HBox1=gtk_hbox_new(1,0);
        HBox2=gtk_hbox_new(1,0);
        HBox3=gtk_hbox_new(1,0);
        HBox4=gtk_hbox_new(1,0);
        Vbox=gtk_vbox_new(1,0);

	//Username entry	
	Label1 = gtk_label_new("Username: ");
	reg_entry1 = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(HBox), Label1, 1, 1, 5);
	gtk_box_pack_start(GTK_BOX(HBox), reg_entry1, 1, 1, 5);

	//Password entry
	Label2 = gtk_label_new("Password: ");
	reg_entry2 = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(HBox1), Label2,1,1,5);
	gtk_box_pack_start(GTK_BOX(HBox1), reg_entry2,1,1,5);

	//Retype Password entry
	Label3 = gtk_label_new("Retype Password: ");
	reg_entry3 = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(HBox2),Label3,1,1,5);
	gtk_box_pack_start(GTK_BOX(HBox2),reg_entry3,1,1,5);

	button1 = gtk_button_new_with_label("Cancel");
	gtk_box_pack_end(GTK_BOX(HBox4), button1, TRUE, TRUE, 10);

	button2 = gtk_button_new_with_label("Register");
//	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(LoginButton), (gpointer) 1);		
//	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(hide), Window);
	gtk_box_pack_end(GTK_BOX(HBox4), button2, TRUE, TRUE, 5);
	
//	button = gtk_button_new_with_label("Register");
/*	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), Window); */
//	gtk_box_pack_start(GTK_BOX(HBox4), button, TRUE, TRUE, 10);

//	button = gtk_button_new_with_label("Cancel");
/*	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(login function here), (gpointer)6);		
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(hide), Window);
*///	gtk_box_pack_start(GTK_BOX(HBox4), button, TRUE, TRUE, 5);

	gtk_box_pack_start(GTK_BOX(Vbox),HBox,1,1,0);
        gtk_box_pack_start(GTK_BOX(Vbox),HBox1,1,1,0);
        gtk_box_pack_start(GTK_BOX(Vbox),HBox2,1,1,0);
        gtk_box_pack_start(GTK_BOX(Vbox),HBox3,1,1,0);
        gtk_box_pack_start(GTK_BOX(Vbox),HBox4,1,1,0);
	
	gtk_container_add(GTK_CONTAINER(adjustment),Vbox);
	gtk_container_add(GTK_CONTAINER(Window),adjustment);
	gtk_widget_show_all(Window);
//	return Window;
} /*of Create_RegisterWindow*/

GtkWidget *Create_LoginWindow()
{
	GtkWidget *Window;
	GtkWidget *HBox, *HBox1, *HBox2, *HBox3, *VBox;
//	GtkWidget *entry1, *entry2;
	GtkWidget *Label1, *Label2;
	GtkWidget *button1,*button2,*button3;
	GtkWidget *adjustment;
	
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(Window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(Window), "Login");
	gtk_window_set_position(GTK_WINDOW(Window), GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(Window, 480, 270);	
	
	VBox = gtk_vbox_new(1, 0);
	HBox = gtk_hbox_new(1,0);
	HBox1 = gtk_hbox_new(1, 0);
	HBox2 = gtk_hbox_new(1, 0);
	HBox3 = gtk_hbox_new(1, 0);
	adjustment = gtk_alignment_new(0.5,0.5,0,0);

	Label1 = gtk_label_new("Username: ");
	entry1 = gtk_entry_new();
	Label2 = gtk_label_new("Password: ");
	entry2 = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(HBox),Label1,1,1,5);
	gtk_box_pack_start(GTK_BOX(HBox),entry1,1,1,5);
	gtk_box_pack_start(GTK_BOX(HBox1),Label2,1,1,5);
        gtk_box_pack_start(GTK_BOX(HBox1),entry2,1,1,5);
	button1=gtk_button_new_with_label("Log in");
	gtk_box_pack_start(GTK_BOX(HBox3),button1,1,1,5);
	button2=gtk_button_new_with_label("Cancel");
        gtk_box_pack_start(GTK_BOX(HBox3),button2,1,1,5);
	button3=gtk_button_new_with_label("Register");
        gtk_box_pack_start(GTK_BOX(HBox3),button3,1,1,5);
	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(LoginButton),Window);
//        g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(),Window);
        g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(Create_RegisterWindow),Window);

	gtk_box_pack_start(GTK_BOX(VBox),HBox,1,1,0);	
	gtk_box_pack_start(GTK_BOX(VBox),HBox1,1,1,0);
        gtk_box_pack_start(GTK_BOX(VBox),HBox2,1,1,0);
        gtk_box_pack_start(GTK_BOX(VBox),HBox3,1,1,0);
	gtk_container_add(GTK_CONTAINER(adjustment),VBox);
        gtk_container_add(GTK_CONTAINER(Window),adjustment);
	gtk_widget_show_all(Window);
	
	return Window;
} /*end of Create_LoginWindow*/

void Add_UserWindow()
{
	GtkWidget *Window;
	GtkWidget *VBox, *HBox1, *HBox2;
	GtkWidget *Label1;
//	GtkWidget *entry1;
	GtkWidget *button;
	GtkWidget *adjustment;

	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(Window), "Chess Chat Add User/Friend");
	gtk_window_set_position(GTK_WINDOW(Window), GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request (GTK_WIDGET (Window), 480, 270);
        g_signal_connect(G_OBJECT(Window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	adjustment=gtk_alignment_new(0.5,0.5,0,0);
	
	HBox1 = gtk_hbox_new(1,0);
	HBox2 = gtk_hbox_new(1,0);
	VBox = gtk_vbox_new(1,0);
	
	Label1 = gtk_label_new("Add User: ");
	entry1 = gtk_entry_new();
	g_signal_connect (entry1, "activate",
		      G_CALLBACK (gtk_widget_destroy), entry1);		  
	gtk_box_pack_start(GTK_BOX(HBox1), Label1, 1, 1, 5);
	gtk_box_pack_start(GTK_BOX(HBox1), entry1, 1, 1, 5);
	
	button = gtk_button_new_with_label("Add");
	gtk_box_pack_start(GTK_BOX(HBox2),button,1,1,0);
	button = gtk_button_new_with_label("Cancel");
        gtk_box_pack_start(GTK_BOX(HBox2),button,1,1,0);
	gtk_box_pack_start (GTK_BOX (VBox), HBox1, TRUE, TRUE, 0);
        gtk_box_pack_start (GTK_BOX (VBox), HBox2, TRUE, TRUE, 0);
    
	gtk_container_add(GTK_CONTAINER(adjustment),VBox);
        gtk_container_add(GTK_CONTAINER(Window),adjustment);	

	gtk_widget_set_can_default (button, TRUE);
    	gtk_widget_grab_default (button);
    	gtk_widget_show (button);
	
	gtk_widget_show_all (Window);
	
//	return Window;
}

void FriendListWindow(){
   GtkWidget *Window,*adjustment;
   GtkWidget *add,*delete,*name;
   GtkWidget *vbox, *hbox;
   GtkTreeSelection *select;
   Window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(Window),"Friend List");
   gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
   gtk_widget_set_size_request(Window,400,300);
   adjustment=gtk_scrolled_window_new(0,0);
   list=gtk_tree_view_new();
   gtk_container_add(GTK_CONTAINER(adjustment),list);
   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(adjustment),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(adjustment),GTK_SHADOW_ETCHED_IN);
   gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list),FALSE);
   vbox=gtk_vbox_new(0,0);
   gtk_box_pack_start(GTK_BOX(vbox),adjustment,1,1,0);
   hbox=gtk_hbox_new(0,5);
   add = gtk_button_new_with_label("Add");
   delete = gtk_button_new_with_label("Remove");
   name = gtk_entry_new();
   gtk_box_pack_start(GTK_BOX(hbox),add,0,1,0);
   gtk_box_pack_start(GTK_BOX(hbox),name,0,1,0);
   gtk_box_pack_start(GTK_BOX(hbox),delete,0,1,0);
   gtk_box_pack_start(GTK_BOX(vbox),hbox,0,1,0);
   gtk_container_add(GTK_CONTAINER(Window),vbox);
   init_list(list);
   select=gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
   g_signal_connect(G_OBJECT(add),"clicked",G_CALLBACK(add_Friend),name);
   g_signal_connect(G_OBJECT(delete),"clicked",G_CALLBACK(delete_Friend),select);
   g_signal_connect(G_OBJECT(Window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
   gtk_widget_show_all(Window);
//   return Window;

}

void mainMenu(){
   GtkWidget *window, *button1, *button2, *hbox,*adjustment;
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   gtk_window_set_title(GTK_WINDOW(window), "Main Menu");
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   gtk_widget_set_size_request(window, 480, 270);
   adjustment=gtk_alignment_new(0.5,0.5,0,0);
   hbox = gtk_hbox_new(1, 0);
   button1=gtk_button_new_with_label("Chat");
   button2=gtk_button_new_with_label("Friend");
   gtk_box_pack_start(GTK_BOX(hbox), button1, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);
   g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Create_ChatWindow), G_OBJECT(window));
   g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(FriendListWindow), G_OBJECT(window));
   gtk_container_add(GTK_CONTAINER(adjustment),hbox);
   gtk_container_add(GTK_CONTAINER(window),adjustment);
   gtk_widget_show_all(window);
}

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

void * getData(void * sockID)
{

	client_Socket = *((int *) sockID);	//gets the client socket value from the socket id integer pointer

	while(1)
	{

		char data[1024];	//gets a data stream of 1024 characters
		int read = recv(client_Socket,data,1024,0);	//takes the incoming data from this socket
		data[read] = '\0';	//puts a the whitespace at the end of teh data stream, the read is the returned value of  recv which is the number of characters read in 
		printf("%s\n",data); //prints the data stream that was made
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		gtk_text_buffer_insert(buffer, &iter, data, -1);
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
	}

}

int main( int argc, char *argv[] )
{
	int client_Socket = socket(PF_INET, SOCK_STREAM, 0);	//create a socket for the client
	
	struct hostent *server;
	struct sockaddr_in serverAddr;		//structs needed for the server
//startr of copied
	server = gethostbyname("zuma.eecs.uci.edu");
    	if (server == NULL) 
	{
        	fprintf(stderr,"ERROR, no such host\n");
        	return 0;
    	}
    	bzero((char *) &serverAddr, sizeof(serverAddr));

    
	bcopy((char *)server->h_addr_list[0],(char *)&serverAddr.sin_addr.s_addr,server->h_length);	//makes sure that the server si always the zuma.eecs thing at the certain portno

//end of copied




	serverAddr.sin_family = AF_INET;	//constant that you put in for everything
	serverAddr.sin_port = htons(3333);	//random port number hard coded in 

	if(argv[1] == NULL)
	{
		printf("/client your_name\n");
		return 0;
	}


	if(connect(client_Socket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1)	//connect will return negative one if the code does not work
	{
		printf("Connection failed\n");	
		printf("There maybe too many users online currently, try again at another time \n");
		return 0;
	}

	send(client_Socket, argv[1] ,1024,0);	//to send your name over to the other side

	printf("Connection established ............\n");
	printf("INTRUCTIONS\n\n");
	printf("in order to get list of users online, type USERS\n");
	printf("In order to send a message type SEND (recieving client's number) and then the message you want to send all on the same line\n\n"); 
	printf("For example, if you are sending and there are 2 other clients that are numbered client 1 and 2 respectively, you have to type:\n");
	printf("SEND 2 Hello\n");
	printf("This will send the message to the second client\n");
	

	pthread_t thread;	//makes a thread variable
	pthread_create(&thread, NULL, getData, (void *) &client_Socket ); //creates a thread to get the data 
	
	char name[] = " -";

	strcat(name, argv[1]);	//creates a name system so that it will have a name

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	GtkWidget *Chat_Window  = NULL;
	GtkWidget *Register_Window = NULL;
	GtkWidget *Login_Window = NULL;

	//GtkWidget *FriendList_Window=NULL;

	GtkWidget *AddUser_Window = NULL;
//	int ServSocketFD; /*socket file descriptor for service*/
	//int PortNo;	  /*port number*/

	Program = argv[0];
	gtk_init (&argc, &argv);
	
#ifdef DEBUG
	printf("%s: Starting...\n", Program);
#endif
/*
	if (argc < 2){
		fprintf(stderr, "Usage: %s port\n", Program);
		exit(10);
		} 
	PortNo = atoi(argv[1]); 
	if (PortNo<= 2000){	
		fprintf(stderr, "%s: invalid port number %d, should be >2000\n", Program, PortNo);	
		exit(10);
		}  
		*/
#ifdef DEBUG
	printf("%s: Creating Chat Window...\n", Program);
#endif	
	Create_ChatWindow();
	if (!Chat_Window){
		fprintf(stderr, "%s: Cannot create Chat Window\n", Program);
		} /*fi*/
#ifdef DEBUG
	printf("%s: Creating Register Window...\n", Program);
#endif
	Create_RegisterWindow();
	if (!Register_Window){
		fprintf(stderr, "%s: Cannot create Register Window\n", Program);
		} /*fi*/

#ifdef DEBUG
	printf("%s: Creating Login Window...\n", Program);
#endif
	Login_Window = Create_LoginWindow();
	if(!Login_Window){
		fprintf(stderr, "%s: Cannot create Login Window\n", Program);
		} /*fi*/
#ifdef DEBUG
	printf("%s: Creating Add User Window...\n", Program);
#endif
	Add_UserWindow();
	if(!AddUser_Window){
		fprintf(stderr,"%s: Cannot create Add User Window\n", Program);
		} /*fi*/
	
	FriendListWindow();
	gtk_main();
   return 0;
} /*end of main*/
