/*
One important characteristic of containers is that each container can hold other
containers. To really drive this point home, in this example, you will use a
large number of containers. The main window will show a GtkNotebook and two
buttons along the bottom.

The notebook should have four pages. Each notebook page should hold a GtkButton
that moves to the next page (The GtkButton on the last page should wrap around
to the first page.)

Create two buttons along the bottom of the window. The first should move to the
previous page in the GtkNotebook, wrapping to the last page if necessary. The
second button should close the window and exit the application when clicked.

*/

#include <gtk/gtk.h>

static void destroy(GtkWidget *, gpointer);
static gboolean delete_event(GtkWidget *, GdkEvent *, gpointer);
static void previous_page(GtkWidget *, gpointer);
static void next_page(GtkWidget *, gpointer);

int main(int argc, char **argv) {

  GtkWidget *window, *vbox, *hbox, *notebook, *button, *label;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Multiple Containers");
  gtk_widget_set_size_request(window, 300, 100);

  // Create V box for notebook and buttons
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  // create first component of the vbox
  notebook = gtk_notebook_new();
  char page_label[30];

  // Generate 4 notebook pages
  for (int i = 0; i < 4; i++) {
    sprintf(page_label, "Page %d", i + 1);
    label = gtk_label_new(page_label);

    sprintf(page_label, "Go to page %d", (i + 1) % 4 + 1);

    button = gtk_button_new_with_label(page_label);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(next_page),
                     notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), button, label);
  }

  // Add notebook to vbox
  gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 5);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  // Create previous button to add to H box
  button = gtk_button_new_with_label("Previous");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(previous_page),
                   notebook);

  gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 5);

  // Create Close button to add to H box
  button = gtk_button_new_with_label("Close");
  g_signal_connect_swapped(G_OBJECT(button), "clicked",
                           G_CALLBACK(gtk_main_quit), G_OBJECT(window));
  g_signal_connect_swapped(G_OBJECT(window), "delete-event",
                           G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 5);

  // Add H box to vbox
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 5);

  // label
  label = gtk_label_new("Noir");
  gtk_label_set_selectable(GTK_LABEL(label), TRUE);

  // Add label to window
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}

static void destroy(GtkWidget *window, gpointer data) { gtk_main_quit(); };

static gboolean delete_event(GtkWidget *window, GdkEvent *event,
                             gpointer data) {
  return FALSE;
}

static void previous_page(GtkWidget *button, gpointer notebook) {
  gint page = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
  page = (page + 3) % 4;
  gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), page);
}

static void next_page(GtkWidget *button, gpointer notebook) {
  gint page = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
  page = (page + 1) % 4;
  gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), page);
}
