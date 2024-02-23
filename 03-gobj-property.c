/*
In this exercise, you will expand on Exercise 2-1, but the title, height, and
width of the window should be set by using the functions provided by GObject.
Also, within the callback function, all operations involving the window title
and label text should be performed with the functions provided by GObject.
Additionally, you should monitor the window's title with the notify signal. When
the title is changed, you should notify the user in the terminal output.

Hint: You can use a function provided by GLib, g_message(), to output a message
to the terminal. This function follows the same formatting supported by
printf().
*/
#include <gtk/gtk.h>

static void destroy(GtkWidget *, gpointer);
static gboolean delete_event(GtkWidget *, GdkEvent *, gpointer);
static gboolean keypress_event(GtkWidget *, GdkEventKey *, gpointer);
static gboolean property_changed(GObject *button, GParamSpec *property,
                                 gpointer data);

int main(int argc, char **argv) {

  GtkWidget *window, *label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_object_set(window, "resizable", FALSE, "title", "Diab", "default-width",
               300, "default-height", 100, NULL);
  // gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  // gtk_window_set_title(GTK_WINDOW(window), "Diab");
  // gtk_widget_set_size_request(window, 300, 100);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event),
                   NULL);
  g_signal_connect(G_OBJECT(window), "notify::title",
                   G_CALLBACK(property_changed), NULL);

  g_signal_connect(G_OBJECT(window), "key-press-event",
                   G_CALLBACK(keypress_event), NULL);

  // label
  label = gtk_label_new("Noir");
  g_object_set(label, "selectable", TRUE, NULL);
  // gtk_label_set_selectable(GTK_LABEL(label), TRUE);

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
    const gchar *title = NULL;
    g_object_get(window, "title", &title, NULL);

    GtkWidget *label = gtk_bin_get_child(GTK_BIN(window));
    const short int is_diab = g_ascii_strcasecmp(title, "Diab") == 0;

    g_object_set(window, "title", is_diab ? "Noir" : "Diab", NULL);
    g_object_set(label, "label", is_diab ? "Diab" : "Noir", NULL);
  }
  return FALSE;
}

static gboolean property_changed(GObject *window, GParamSpec *property,
                                 gpointer data) {
  char *title;
  g_object_get(window, "title", &title, NULL);
  g_message("The title of the window has been changed to: %s", title);
  return FALSE;
}
