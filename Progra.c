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

/**
 * Botón Generar 
 * Hay que cambiar esto para que actualize de acuerdo a una matriz o 
 * lista de datos.
 **/
void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data){
    int 			c = 1;
    double 			w, t, p, q;
    GdkWindow 		*window;
    GdkRectangle 	da;
    
    window = gtk_widget_get_window(widget);
	
    /* Determinamos el tamaño de la drawing area y la ponemos en el 
     * centro del widget.*/
    gdk_window_get_geometry (window, &da.x, &da.y, &da.width, &da.height);
	cairo_translate (cr, da.width / 2, da.height / 2);

	//Pintamos el fondo
    cairo_set_source_rgb (cr, 0, 0.6, 0);
	cairo_paint (cr);
	
	//Pintamos los rectangulos
    cairo_set_line_width (cr, 1);
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    
    p = (double)-(da.width)/2;		//Inicio de x
    q = (double)-(da.height)/2;		//Inicio de y
    w = (double)da.width/g_col;		//Ancho de cada cuadrito
    t = (double)da.height/g_fil;	//Largo de cada cuadrito
    
    printf("Matriz de %dx%d\n", g_col, g_fil);
    printf("\tAncho: %d\t\t\tLargo: %d\n", da.width, da.height);
    printf("\tInicio x: %f\t\tInicio y: %f\n", p, q);
    printf("\tAncho celda: %f\t\tLargo celda: %f\n\n", w, t);
    
    for(double x = p; x < -p; x += w){
		for(double y = q; y < -q; y += t){
			//printf("Posicion %d: %f = %f, %f = %f\n", c, x, -p, y, -q);
			cairo_rectangle (cr, x, y, w, t);
			c++;
		}
	}
	cairo_stroke (cr);
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

