#include <math.h>
#include <stdio.h>
#include <gtk/gtk.h>

#define WIDTH   640
#define HEIGHT  500

float ZOOM_X = 100.0;
float ZOOM_Y = 100.0;


/// VARIABLES GLOBALES
GtkWidget   *g_winPrincipal;
GtkWidget 	*g_areaPintado;
int 		g_col;
int			g_fil;

cairo_t 	*g_cr;

void piso(){
	
}

void pared(){
	
}


/// Botón Generar
void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data){
    g_cr = cr;
    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 1.0; 
    gdouble dy = 1.0; 			/* Pixels between each point */
    gdouble clip_x1 = 0.0, clip_x2 = 0.0; 
    gdouble clip_y1 = 0.0, clip_y2 = 0.0;
    GdkWindow *window = gtk_widget_get_window(widget);

    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (window, &da.x, &da.y, &da.width, &da.height);

    /* Change the transformation matrix */
    cairo_translate (cr, da.width / 2, da.height / 2);
    cairo_scale (cr, ZOOM_X, -ZOOM_Y);

    /* Determine the data points to calculate (ie. those in the clipping zone) */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    
    cairo_set_source_rgb (cr, 0, 0.6, 0);
	cairo_paint (cr);
    
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
    //+(0.01*(g_col+1))
    //+(0.01*(g_fil+1))
    double w = (clip_x2*2)/g_col;
    double t = (clip_y2*2)/g_fil;
    double p = clip_x2;
    double q = clip_y2 + 0.001;
    
    printf("\nMatriz de %d filas y %d columnas, hay un w = %f y un t = %f\n", g_col, g_fil, w, t);
    printf("Clips x: %f, %f\n", clip_x1, clip_x2);
    printf("Clips y: %f, %f\n\n", clip_y1, clip_y2);
    
    for(double x = clip_x1; x <= p || c == 40; x += w){
		for(double y = clip_y1; y <= q || c == 40; y += t){
			printf("Posicion %d: %f = %f, %f = %f\n", c, x, p, y, q);
			cairo_rectangle (cr, x, y, w, t);							//Podemos guardar en una matriz la información de donde está cada cosa
			c++;
		}
	}
	cairo_stroke (cr);
	
	cairo_set_line_width (cr, 0.01);
	cairo_set_source_rgb (cr, 0, 0.6, 0.6);
	cairo_rectangle (cr, clip_x1, clip_y1, w, t);
	cairo_fill (cr);
    
    gtk_window_resize(GTK_WINDOW(g_winPrincipal), WIDTH, HEIGHT);
}

void on_btnGenerar_clicked(){
	GtkWidget *lblCol, *lblFil, *spinCol, *spinFil, *caja, *dialog;
	
	dialog = gtk_dialog_new_with_buttons ("Elegir tamaño de la matriz", GTK_WINDOW(g_winPrincipal) , 
										  GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT, 
										  "_Aceptar" , GTK_RESPONSE_ACCEPT, 
										  "_Cancelar", GTK_RESPONSE_REJECT, NULL);
	
	caja = GTK_WIDGET(gtk_dialog_get_content_area(GTK_DIALOG(dialog)));
	lblFil = gtk_label_new("Filas: ");
	spinFil = gtk_spin_button_new_with_range (0, 2048, 1);
	lblCol = gtk_label_new("Columnas: ");
	spinCol = gtk_spin_button_new_with_range (0, 2048, 1);
	gtk_container_add(GTK_CONTAINER(caja), lblFil);
	gtk_container_add(GTK_CONTAINER(caja), spinFil);
	gtk_container_add(GTK_CONTAINER(caja), lblCol);
	gtk_container_add(GTK_CONTAINER(caja), spinCol);
	gtk_widget_show_all(dialog);
	
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		g_fil = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinFil));
		g_col = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinCol));
		g_signal_connect (g_areaPintado, "draw", G_CALLBACK (on_draw), NULL);
	}
	
	gtk_widget_destroy (dialog);
}

///Botón Leer
void leer (char nombre[1024]) {
	/*int i = 0, j = 0;
    char linea[1024];
    FILE *archivo = fopen(nombre, "r");
    
    while(fgets(linea, 1024, archivo)) {
        char * pch = strtok (linea," ,");
        while (pch != NULL){
            g_matriz[i][j] =  atoi(pch);
            pch = strtok (NULL, " ,"); 
            j++;
        } i++; j = 0;
    }
    fclose(archivo);
    actualizar_matriz();*/
}

void on_btnLeer_clicked(){
	GtkWidget *dialog = gtk_file_chooser_dialog_new("Leer Archivo", GTK_WINDOW(g_winPrincipal), 
													GTK_FILE_CHOOSER_ACTION_OPEN, 
													"_Cancelar", GTK_RESPONSE_CANCEL, 
													"_Abrir"   , GTK_RESPONSE_ACCEPT, NULL);
	int respuesta = gtk_dialog_run(GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT){
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		char *filename = gtk_file_chooser_get_filename (chooser);
		leer(filename);
	}
	gtk_widget_destroy (dialog);
}

///Boton Guardar
void guardar (char nombre[1024]/*,int g_matriz[9][9]*/) {
 	/*int  i, j;
 	char buffer[1024], cadena[1024];
 	FILE *archivo = fopen (nombre, "w+");
    
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
         sprintf(buffer, "%d,", g_matriz[i][j]);
         strcat(cadena, buffer);
        }
        strcat(cadena, "\n");
	}
    fwrite(cadena, sizeof(char), sizeof(cadena), archivo);
    fclose (archivo); */
}

void on_btnGrabar_clicked(){
	GtkWidget *dialog = gtk_file_chooser_dialog_new ("Grabar Archivo", GTK_WINDOW(g_winPrincipal), 
													 GTK_FILE_CHOOSER_ACTION_SAVE, 
													 "_Cancelar", GTK_RESPONSE_CANCEL, 
													 "_Grabar"  , GTK_RESPONSE_ACCEPT, NULL);
	GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		char *filename = gtk_file_chooser_get_filename (chooser);
		guardar(filename/*, g_matriz*/);
	}
	gtk_widget_destroy (dialog);
}

///Botón Resolver
void on_btnResolver_clicked(){
	GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(g_winPrincipal), 
												GTK_DIALOG_DESTROY_WITH_PARENT, 
												GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
												"No implementado");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

///Botón Salir
void on_winPrincipal_destroy (){
	gtk_main_quit();
}

/// Zoom in
void on_btnZoomIn_clicked(){
	ZOOM_X += 100;
	ZOOM_Y += 100;
	printf("ZoomIn\n");
	gtk_widget_queue_draw (g_areaPintado);
}

/// Zoom out
void on_btnZoomOut_clicked(){
	if(ZOOM_X-100 != 0){
		ZOOM_X -= 100;
		ZOOM_Y -= 100;
		printf("ZoomOut\n");
		gtk_widget_queue_draw (g_areaPintado);
	}
}


///INTERFAZ
void crearInterfaz(){
	GtkBuilder  *builder;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Interfaz.glade", NULL);
	
	g_winPrincipal 	= GTK_WIDGET(gtk_builder_get_object(builder, "winPrincipal"));
	g_areaPintado 	= GTK_WIDGET(gtk_builder_get_object(builder, "areaPintado"));
	
	gtk_window_set_position(GTK_WINDOW(g_winPrincipal), GTK_WIN_POS_CENTER);
	gtk_window_resize(GTK_WINDOW(g_winPrincipal), WIDTH, HEIGHT);
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show_all(g_winPrincipal);
	g_object_unref(builder);
    gtk_main();
}

///MAIN
int main(int argc, char **argv)
{
	gtk_init(&argc, &argv);
	crearInterfaz();
	
	return 0;
}

