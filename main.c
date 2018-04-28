#include <stdlib.h>
#include <gtk/gtk.h>

static void NavigateHome(GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Navigate to home page.");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void NavigateSettings(GtkWidget *wid, GtkWidget *win) {
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Navigate to settings.");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

int main (int argc, char *argv[])
{
  GtkWidget *button = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;

  // Initialize GTK+
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  // Create the main window
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 8);
  gtk_window_set_default_size(GTK_WINDOW(win), 250, 300);
  gtk_window_set_title (GTK_WINDOW (win), "Crypto Tracker");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  // Create a vertical box with buttons
  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  // home button
  button = gtk_button_new_with_label ("Home");
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (NavigateHome), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  // settings button
  button = gtk_button_new_with_label("Settings");
  g_signal_connect (button, "clicked", G_CALLBACK(NavigateSettings), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  // quit button
  button = gtk_button_new_with_label("Quit");
  g_signal_connect(button, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

  // Enter the main loop
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
