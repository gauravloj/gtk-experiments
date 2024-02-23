#include <gtk/gtk.h>

static void destroy(GtkWidget *, gpointer);
static gboolean delete_event(GtkWidget *, GdkEvent *, gpointer);

int main(int argc, char **argv) {

  GtkWidget *window, *label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // gtk_window_set_title(GTK_WINDOW(window), "Diab");
  // gtk_widget_set_size_request(window, 300, 100);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(delete_event),
                   NULL);

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
