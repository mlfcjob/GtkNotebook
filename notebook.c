#include "notebook.h"

static int count = 0;

static void on_drag_data_received(GtkWidget *widget, GdkDragContext *context, 
				                  gint x, gint y, GtkSelectionData *data,
								  guint info, guint time, gpointer user_data)
{
printf("########################## on drag data .\n");
    GtkWidget *notebook;
	GtkWidget **child;

	notebook = gtk_drag_get_source_widget(context);
	child = (void*) gtk_selection_data_get_data(data);

	gtk_notebook_detach_tab(GTK_NOTEBOOK(notebook), *child);
}

static void remove_page(GtkWidget *widget, gpointer data)
{
    gtk_notebook_remove_page(GTK_NOTEBOOK(data), -1);
}

static void detach_tab(GtkWidget *widget, gpointer data)
{
	GtkWidget *label = gtk_label_new("detach_tab");
    gtk_notebook_detach_tab(GTK_NOTEBOOK(data), label);
    
	if (count++ % 2 == 0) {
	    printf("#################### switch to prev page. \n");
        gtk_notebook_prev_page(GTK_NOTEBOOK(data));
	} else {
	    printf("###################  switch to next page.\n");
        gtk_notebook_next_page(GTK_NOTEBOOK(data));
	}
}

int main(int argc, char *argv[])
{
    /* 1. init gtk env */
    gtk_init(&argc, &argv);

	/* 2. create a gtk window */
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window, 800, 600);

	/* 3. create a notebook */
	GtkWidget *notebook  = gtk_notebook_new();
	gtk_container_add(GTK_CONTAINER(window), notebook);

    /* 4. set notebook pos */
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);  // GTK_POS_LEFT / BOTTOM / RIGHT

	/* 5. create a horizontal layout */
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    
    /* 6. create  first label gtk_notebook_append_page */	
	GtkWidget *label = gtk_label_new("vm one");

	GtkWidget *draw = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(hbox), draw);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox, label);

	/* 7. gtk_noetebook_append_page_menu */
	GtkWidget *hbox_01 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, TRUE);
	GtkWidget *label1 = gtk_label_new("vm two");
	GtkWidget *button = gtk_button_new_with_label("append page menu");

	GtkWidget *menu_label = gtk_label_new("menu vm two");

	gtk_container_add(GTK_CONTAINER(hbox_01), button);

	gtk_notebook_append_page_menu(GTK_NOTEBOOK(notebook), hbox_01, label1, menu_label);

	gtk_notebook_prepend_page(GTK_NOTEBOOK(notebook), hbox_01, NULL);
	//gtk_notebook_prepend_page_menu(GTK_NOTEBOOK(notebook), hbox_01, NULL, NULL);

	/* 8 gtk_notebook_remove_page */
	GtkWidget *remove_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, TRUE);
    GtkWidget *remove_label = gtk_label_new("remove");

	GtkWidget *remove_button = gtk_button_new_with_label("remove page");
	g_signal_connect(remove_button, "clicked", G_CALLBACK(remove_page), notebook);

	gtk_container_add(GTK_CONTAINER(remove_hbox), remove_button);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), remove_hbox, remove_label);

    /* 9 gtk_notebook_detach_tab */
	GtkWidget *detach_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, TRUE);
	GtkWidget *detach_button = gtk_button_new_with_label("detach tab");
	GtkWidget *detach_label = gtk_label_new("detach");

	gtk_container_add(GTK_CONTAINER(detach_hbox), detach_button);

	g_signal_connect(detach_button, "clicked", G_CALLBACK(detach_tab), notebook);

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), detach_hbox, detach_label);

    gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook), detach_hbox, TRUE);
	gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(notebook), detach_hbox, TRUE);

	g_signal_connect(detach_button, "drag-data-recived", G_CALLBACK(on_drag_data_received), NULL);
    printf("current page index: %d. \n", gtk_notebook_page_num(GTK_NOTEBOOK(notebook), detach_hbox));


	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_RIGHT);
	gtk_notebook_popup_enable(GTK_NOTEBOOK(notebook));
	gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);

	gtk_main();

    return 0;
}
