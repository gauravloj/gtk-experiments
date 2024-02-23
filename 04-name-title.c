/*
Exercise 2-1. Using Events and Properties

This exercise will expand on the first two examples in this chapter by creating
a GtkWindow that has the ability to destroy itself. You should set your first
name as the title of the window. A selectable GtkLabel with your last name as
its default text string should be added as the child of the window.

Other properties of this window are that it should not be resizable and the
minimum size should be 300 pixels by 100 pixels. Functions to perform these
tasks can be found in this chapter.

Next, by looking at the API documentation, connect the key-press-event signal to
the window. In the skey-press-event callback function, switch the window title
and the label text. For example, the first time the callback function is called,
the window title should be set to your last name and the label text to your
first.

You may also find this function useful:

gint g_ascii_strcasecmp (const gchar *str1, const gchar *str2);
When the two strings in g_ascii_strcasesmp() are the same, 0 is returned. If
str1 is less than str2, a negative number is returned. Otherwise, a positive
number is returned.
*/

#include <gtk/gtk.h>

static void destroy(GtkWidget *, gpointer);
static gboolean delete_event(GtkWidget *, GdkEvent *, gpointer);
static gboolean keypress_event(GtkWidget *, GdkEventKey *, gpointer);

int main(int argc, char **argv) {

  GtkWidget *window, *label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  gtk_window_set_title(GTK_WINDOW(window), "Diab");
  gtk_widget_set_size_request(window, 300, 100);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event),
                   NULL);
  g_signal_connect(G_OBJECT(window), "key-press-event",
                   G_CALLBACK(keypress_event), NULL);

  // label
  label = gtk_label_new("Noir");
  gtk_label_set_selectable(GTK_LABEL(label), TRUE);

  // Add label to window
  gtk_container_add(GTK_CONTAINER(window), label);
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}

static void destroy(GtkWidget *window, gpointer data) { gtk_main_quit(); };

static gboolean delete_event(GtkWidget *window, GdkEvent *event,
                             gpointer data) {
  return FALSE;
}
static gboolean keypress_event(GtkWidget *window, GdkEventKey *eventkey,
                               gpointer data) {
  if (eventkey->keyval == GDK_KEY_s) {
    const gchar *title = gtk_window_get_title(GTK_WINDOW(window));
    if (g_ascii_strcasecmp(title, "Diab") == 0) {
      gtk_window_set_title(GTK_WINDOW(window), "Noir");
      gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(window))), "Diab");
    } else {
      gtk_window_set_title(GTK_WINDOW(window), "Diab");
      gtk_label_set_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(window))), "Noir");
    }
    return TRUE;
  }
  return FALSE;
}
