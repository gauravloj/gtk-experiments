/* In this exercise, you will expand upon the code you wrote in Exercise 3-1.
Instead of using a GtkVBox to hold the notebook and horizontal box of buttons,
create a GtkVPaned widget.

In addition to this change, you should hide the GtkNotebook tabs, so the user is
not able to switch between pages without pressing buttons. In this case, you
will not be able to know when a page is being changed. Therefore, each button
that is in a GtkNotebook page should be contained by its own expander. The
expander labels will allow you to differentiate between notebook pages.
*/

#include <gtk/gtk.h>

static void destroy(GtkWidget *, gpointer);
static gboolean delete_event(GtkWidget *, GdkEvent *, gpointer);
static void previous_page(GtkWidget *, gpointer);
static void next_page(GtkWidget *, gpointer);

int main(int argc, char **argv) {

  GtkWidget *window, *vpane, *hpane, *notebook, *button, *label, *expander;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Multiple Containers");
  gtk_widget_set_size_request(window, 300, 100);

  // Create V pane for notebook and buttons
  vpane = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

  // create first component of the vpane
  notebook = gtk_notebook_new();
  char page_label[30];

  // add expander
  // Generate 4 notebook pages
  for (int i = 0; i < 4; i++) {
    sprintf(page_label, "Page %d", i + 1);
    expander = gtk_expander_new_with_mnemonic(page_label);

    sprintf(page_label, "Go to page %d", (i + 1) % 4 + 1);

    button = gtk_button_new_with_label(page_label);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(next_page),
                     notebook);

    gtk_container_add(GTK_CONTAINER(expander), button);
    gtk_expander_set_expanded(GTK_EXPANDER(expander), TRUE);

    label = gtk_label_new(page_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), expander, label);
  }

  // Hide tabs
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), FALSE);

  // Add notebook to vpane
  gtk_paned_add1(GTK_PANED(vpane), notebook);

  hpane = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

  // Create previous button to add to H box
  button = gtk_button_new_with_label("Previous");
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(previous_page),
                   notebook);

  gtk_paned_add1(GTK_PANED(hpane), button);

  // Create Close button to add to H box
  button = gtk_button_new_with_label("Close");
  g_signal_connect_swapped(G_OBJECT(button), "clicked",
                           G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_paned_add2(GTK_PANED(hpane), button);

  // Add H box to vpane
  gtk_paned_add2(GTK_PANED(vpane), hpane);

  g_signal_connect_swapped(G_OBJECT(window), "delete-event",
                           G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_container_add(GTK_CONTAINER(window), vpane);
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
