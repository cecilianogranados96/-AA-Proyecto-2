#include <math.h>
#include <stdio.h>
#include <gtk/gtk.h>

#define WIDTH   640
#define HEIGHT  480

#define ZOOM_X  100.0
#define ZOOM_Y  100.0


/// VARIABLES GLOBALES
GtkWidget   *g_winPrincipal;
GtkWidget 	*g_areaPintado;
cairo_t 		*cr;
cairo_surface_t *surface;

void piso(){
	
}

void pared(){
	
}

void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 1.0; 
    gdouble dy = 1.0; 			/* Pixels between each point */
    gdouble clip_x1 = 0.0, clip_x2 = 0.0; 
    gdouble clip_y1 = 0.0, clip_y2 = 0.0;
    GdkWindow *window = gtk_widget_get_window(widget);

    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (window, &da.x, &da.y, &da.width, &da.height);

    /* Draw on a black background */
    cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
    cairo_paint (cr);

    /* Change the transformation matrix */
    cairo_translate (cr, da.width / 2, da.height / 2);
    cairo_scale (cr, ZOOM_X, -ZOOM_Y);

    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    
    
	
	
    /* Draws x and y axis */
    /*cairo_set_line_width (cr, 0.01);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_rectangle (cr, clip_x1, clip_y1, 0.3, 0.3);			//Esquina inferior izquierda
    cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
    cairo_rectangle (cr, clip_x2-0.3, clip_y1, 0.3, 0.3);		//Esquina inferior derecha
    cairo_set_source_rgb (cr, 0.2, 0.4, 0.4);
    cairo_rectangle (cr, clip_x1, clip_y2-0.3, 0.3, 0.3); 		//Esquina superior izquierda
    cairo_set_source_rgb (cr, 0.2, 0.6, 0.6);
    cairo_rectangle (cr, clip_x2-0.3, clip_y2-0.3, 0.3, 0.3);	//Esquina superior derecha 
	cairo_stroke (cr);*/
	cairo_set_line_width (cr, 0.01);
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    int c = 1;
    int n = 100; 						
    double w = clip_x2*2/(n);
    double t = clip_y2*2/(n)+ 0.0001;
    double p = clip_x2;
    double q = clip_y2;
    printf("\nCon n = %d, hay un w = %f y un t = %f\n", n, w, t);
    printf("Clips x: %f, %f\n", clip_x1, clip_x2);
    printf("Clips y: %f, %f\n\n", clip_y1, clip_y2);
    for(double x = clip_x1; x <= p || c == 40; x += w){
		for(double y = clip_y1; y <= q || c == 40; y += t){
			printf("Posicion %d: %f = %f, %f = %f\n", c, x, p, y, q);
			cairo_rectangle (cr, x, y, w, t);
			c++;
		}
	}
	printf("Salio");
	cairo_stroke (cr);
    
    //cairo_move_to (cr, 0.0, clip_y1);
    //cairo_line_to (cr, 0.0, clip_y2);
    

    gtk_window_resize(GTK_WINDOW(g_winPrincipal), WIDTH, HEIGHT);
}

void on_btnGenerar_clicked(){
	
}

///Botón Leer

///Botón Salir
void on_winPrincipal_destroy () {
	gtk_main_quit();
}

/// Zoom in



/// Zoom out

///INTERFAZ
void crearInterfaz(){
	GtkBuilder  *builder;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Interfaz.glade", NULL);
	
	g_winPrincipal 	= GTK_WIDGET(gtk_builder_get_object(builder, "winPrincipal"));
	g_areaPintado 	= GTK_WIDGET(gtk_builder_get_object(builder, "areaPintado"));
	
	g_signal_connect (g_areaPintado, "draw", G_CALLBACK (on_draw), NULL);
	//gtk_widget_show(g_areaPintado);
	
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(builder);
    gtk_widget_show_all(g_winPrincipal);
    //gtk_widget_hide(g_areaPintado);             
    gtk_main();
}

///MAIN
int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);
	crearInterfaz();
	
	return 0;
}

