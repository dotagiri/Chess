#ifndef GTK_H
#define GTK_H


static void enter_callback(GtkWidget *widget, GtkWidget *entry);

void hide(GtkWidget *Widget);

void LoginButton(GtkWidget *button, gpointer data);

void RegistrationButton(GtkWidget *button, gpointer data);

void AddUserButton(GtkWidget *button, gpointer data);

void add_Friend(GtkWidget *widget, gpointer name);

void delete_Friend(GtkWidget *widget, gpointer name);

void init_list(GtkWidget *list);

void Create_ChatWindow();

void Create_RegisterWindow();

void mainMenu();

GtkWidget *Create_LoginWindow();

void  Add_UserWindow();

void FriendListWindow();

void FatalError(const char *ErrorMsg);

void destroyWindow(GtkWidget *window);

#endif

