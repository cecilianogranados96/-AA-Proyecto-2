#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#define WIDTH   640
#define HEIGHT  500

/// VARIABLES GLOBALES
GtkWidget   *g_winPrincipal;
GtkWidget 	*g_areaPintado;
int 		g_width;
int			g_height;
char        *maze;
int         c = 0; //TAMAÑO PARA ARCHIVO DE GUARDAR Y LEER


///---------------------------------------------------------------------
///Botón Generar
void CarveMaze(char *maze, int x, int y) {
	srand(time(NULL));
	int x1, y1, x2, y2;
	int dir, count;
	int dx, dy;
	
	count = 0;
	dir = rand() % 4;
	
	while(count < 4) {
		dx = dy = 0;
		switch(dir) {
			case 0:  dx = 1;  break;
			case 1:  dy = 1;  break;
			case 2:  dx = -1; break;
			default: dy = -1; break;
		}
		
		x1 = x  + dx; 	x2 = x1 + dx;
		y1 = y  + dy;	y2 = y1 + dy;
		
		if (x2 > 0 && y2 > 0 && x2 < g_width && y2 < g_height && 
			maze[y1 * g_width + x1] == 1 && maze[y2 * g_width + x2] == 1) {
				maze[y1 * g_width + x1] = 0;
				gtk_widget_queue_draw (g_areaPintado);
				maze[y2 * g_width + x2] = 0;
				gtk_widget_queue_draw (g_areaPintado);
				x = x2; y = y2;
				dir = rand() % 4;
				count = 0;
		}
		else {
			dir = (dir + 1) % 4;
			count++;
		}
	}
}

void GenerateMaze(char *maze) {
	int x, y;
	
	for(x = 0; x < g_width * g_height; x++) {
		maze[x] = 1;
		gtk_widget_queue_draw (g_areaPintado);
	}
	maze[1 * g_width + 1] = 0;
	gtk_widget_queue_draw (g_areaPintado);
	for(y = 1; y < g_height; y += 2) {
		for(x = 1; x < g_width; x += 2) {
			CarveMaze(maze, x, y);
		}
	}
	maze[0 * g_width + 1] = 0;
	gtk_widget_queue_draw (g_areaPintado);
	maze[(g_height - 1) * g_width + (g_width - 2)] = 0;
	gtk_widget_queue_draw (g_areaPintado);
}

void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data){
	GdkRectangle da;
	GdkWindow *window;
	cairo_surface_t *piso, *pared;
	
	
	float w, t, p, q;
	float x_scaling, y_scaling;
	float tex_width, tex_height;
	int filas = 0, columnas = 0;
	
	
	window = gtk_widget_get_window(widget);
	
	piso = cairo_image_surface_create_from_png ("data/piso.png");
	pared = cairo_image_surface_create_from_png("data/pared.png");
	tex_width 	= cairo_image_surface_get_width (piso);					//Las dos son del mismo tamaño así que ambas imagenes sirven
	tex_height 	= cairo_image_surface_get_height (piso);
	
	
	gdk_window_get_geometry (window, &da.x, &da.y, &da.width, &da.height);	// Determinamos el tamaño de la drawing area y la ponemos en el 
	cairo_translate (cr, da.width / 2, da.height / 2);						// centro del widget.

	p = (float)-(16*g_width);		//Inicio de x
	q = (float)-(16*g_height);		//Inicio de y
	w = (float)da.width/g_width;	//Ancho de cada cuadrito
	t = (float)da.height/g_height;	//Largo de cada cuadrito
	
	x_scaling = w / tex_width;
	y_scaling = t / tex_height;
	
	cairo_scale (cr, x_scaling, y_scaling);
	
	//MOSTAR MAZE
	for(double x = p; x < -p; x += 32){						//Las imagenes son de 32x32
		for(double y = q; y < -q; y += 32){					//Así que por eso se suma 32 para ir a la siguiente
			if (maze[(columnas*g_height)+filas] == 1)
				cairo_set_source_surface(cr, pared, x, y);
			else
				cairo_set_source_surface(cr, piso, x, y);
			cairo_paint(cr);
			//printf("%d ", maze[(filas*g_height)+columnas]);
			columnas++;
		}
		filas++;
		columnas = 0;
		//printf("\n");
	}
    //printf("\n");
}

void on_btnGenerar_clicked(){
	GtkWidget *lblCol, *lblFil, *spinCol, *spinFil, *caja, *dialog;
	
	dialog = gtk_dialog_new_with_buttons ("Elegir tamaño de la matriz", GTK_WINDOW(g_winPrincipal) , 
										  GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT, 
										  "_Aceptar" , GTK_RESPONSE_ACCEPT, 
										  "_Cancelar", GTK_RESPONSE_REJECT, NULL);
	
	caja = GTK_WIDGET(gtk_dialog_get_content_area(GTK_DIALOG(dialog)));
	lblFil = gtk_label_new("Filas: ");
	spinFil = gtk_spin_button_new_with_range (1	, 2048, 1); //OJO QUITAR EL 4 PARA PRODUCCION
	lblCol = gtk_label_new("Columnas: ");
	spinCol = gtk_spin_button_new_with_range (1, 2048, 1); //OJO QUITAR EL 4 PARA PRODUCCION
	gtk_container_add(GTK_CONTAINER(caja), lblFil);
	gtk_container_add(GTK_CONTAINER(caja), spinFil);
	gtk_container_add(GTK_CONTAINER(caja), lblCol);
	gtk_container_add(GTK_CONTAINER(caja), spinCol);
	gtk_widget_show_all(dialog);
	
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		g_height = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinFil));
		g_width = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinCol));
		g_signal_connect (g_areaPintado, "draw", G_CALLBACK (on_draw), NULL);
		maze = (char*)malloc(g_width * g_height * sizeof(char));
		GenerateMaze(maze);
	}
	
	gtk_widget_destroy (dialog);
}


///---------------------------------------------------------------------
///Botón Leer
void leer (char nombre[1024]) {
    /*char cadena1 [1024]; 
    FILE* fichero;
    fichero = fopen(nombre, "rt");
    fgets (cadena1, 1024, fichero);     
    char * pch = strtok (cadena1," ,");
    

   int pos = 0;
        while (pch != NULL){
            //maze[pos] = atoi(pch);
            printf("%d", atoi(pch));
            pch = strtok (NULL, " ,"); 
            pos++;
        }
    

    
    fclose(fichero);
    
    G_CALLBACK (on_draw);*/
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


///---------------------------------------------------------------------
///Boton Guardar
void guardar (char nombre[1024]) {
	FILE* fichero;
	fichero = fopen(nombre, "w+");
    for(int x = 0; x < (g_width * g_height); x++){
		fprintf(fichero, "%d,", maze[x]);
    }
	fclose(fichero);
	printf("\nProceso completado");
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


///---------------------------------------------------------------------
///Botón Resolver
void on_btnResolver_clicked(){
	GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(g_winPrincipal), 
												GTK_DIALOG_DESTROY_WITH_PARENT, 
												GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
												"No implementado");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}


///---------------------------------------------------------------------
///Botón Salir
void on_winPrincipal_destroy (){
	gtk_main_quit();
}


///---------------------------------------------------------------------
/// Zoom in
void on_btnZoomIn_clicked(){
	printf("ZoomIn\n");
	gtk_widget_queue_draw (g_areaPintado);
}


///---------------------------------------------------------------------
/// Zoom out
void on_btnZoomOut_clicked(){
	printf("ZoomOut\n");
	gtk_widget_queue_draw (g_areaPintado);
}


///---------------------------------------------------------------------
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
	srand(time(NULL));
	gtk_init(&argc, &argv);
	crearInterfaz();
	return 0;
}

