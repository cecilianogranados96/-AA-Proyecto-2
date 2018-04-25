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
GtkWidget	*btnResolver;
GtkWidget	*btnGrabar;

gboolean activadoMC = 1;
gboolean activadoMS = 0;

int n = -1, contador = -1, c = 0; //TAMAÑO PARA ARCHIVO DE GUARDAR Y LEER
int g_filas, g_columnas;
int	g_zoomX = 0, g_zoomY = 0;
int g_movX = 0, g_movY = 0;

char **laberinto, **arbolExpansion;
char *filaFrontera, *columnaFrontera;

///---------------------------------------------------------------------
/// Zoom in/out
void mouse_scroll(GtkWidget *widget, GdkEventScroll *event, gpointer user_data){
	GdkScrollDirection dir = event->direction;
	if(activadoMS){
		if(dir == GDK_SCROLL_UP){			//ZOOM IN
			if(g_zoomX < g_columnas-1){
				g_zoomX += 1;
				g_movX = 0, g_movY = 0;
			}
			if(g_zoomY < g_filas-1){
				g_zoomY += 1;
				g_movX = 0, g_movY = 0;
			}
		}
		else if(dir == GDK_SCROLL_DOWN){	//ZOOM OUT
			if(g_zoomX > 0){
				g_zoomX -= 1;
				g_movX = 0, g_movY = 0;
			}
			if(g_zoomY > 0){
				g_zoomY -= 1;
				g_movX = 0, g_movY = 0;
			}
		}
		gtk_widget_queue_draw (g_areaPintado);
		activadoMS = 0;
	}
	else activadoMS = 1;
}


///---------------------------------------------------------------------
/// Moverse en matriz
void mouse_click(GtkWidget *widget, GdkEventButton *event, gpointer user_data){
	/*double centroX 		= gtk_widget_get_allocated_width(g_areaPintado)/2;
	double centroY 		= gtk_widget_get_allocated_height(g_areaPintado)/2;
	double clickX 		= event->x;
	double clickY		= event->y;
	
	int cantX 			= g_columnas-g_zoomX;
	int cantY 			= g_filas-g_zoomY; 
	
	if(activadoMC){
		printf("CantX: %d\tCantY: %d\n", g_movX, g_movY);
		if(event->button == GDK_BUTTON_PRIMARY){	//Moverse en columnas
			if(clickX <= centroX){
				printf("Izquierda\n");
				if(g_movX > 0)	g_movX--;
			}
			else{
				printf("Derecha\n");
				if(g_movX < g_columnas-cantX)	g_movX++;
			}
		}
		else if (event->button == GDK_BUTTON_SECONDARY){	//Moverse en filas
			if(clickY <= centroY){
				printf("Arriba\n");
				if(g_movY > 0)	g_movY--;
			}
			else{
				printf("Abajo\n");
				if(g_movY < g_filas-cantY) g_movY++;
			}
		}
		gtk_widget_queue_draw (g_areaPintado);
		activadoMC = 0;
	}
	else activadoMC = 1;*/
}


///---------------------------------------------------------------------
/// Botón Generar
void agregarAdyacente(int filaIndice,int columnaIndice){
	if(!laberinto[filaIndice][columnaIndice]){
		n++;
		laberinto[filaIndice][columnaIndice] =- 1;
		filaFrontera[n] = filaIndice;
		columnaFrontera[n] = columnaIndice;
	}
}

void marcarAdyacente(int filaIndice,int columnaIndice){
	if(filaIndice)
		agregarAdyacente(filaIndice-1, columnaIndice);
	if(filaIndice != g_filas-1)
		agregarAdyacente(filaIndice+1, columnaIndice);	
	if(columnaIndice)
		agregarAdyacente(filaIndice, columnaIndice-1);
	if(columnaIndice != g_columnas-1)
		agregarAdyacente(filaIndice, columnaIndice+1);
}

void esAdyacente(int filaIndice,int columnaIndice,int filaAdyacente[],int columnaAdyacente[]){
	if((laberinto[filaIndice][columnaIndice] == 1)||
	   (laberinto[filaIndice][columnaIndice] ==16)){
		contador++;
		filaAdyacente[contador] = filaIndice;
		columnaAdyacente[contador] = columnaIndice;
	}
}

void asignarConexion(){
	int k, adyacenteAConectar; 
	int posFronteraF, posFronteraC;
	int filaAdyacente[4], columnaAdyacente[4];
	
	if(!n) k = 0;
	else k = rand()%n;
		
	posFronteraF = filaFrontera[k];
	posFronteraC = columnaFrontera[k];
	contador = -1;
	
	if(posFronteraF)
		esAdyacente(posFronteraF-1, posFronteraC, filaAdyacente, columnaAdyacente);
	if(posFronteraF != g_filas-1)
		esAdyacente(posFronteraF+1, columnaFrontera[k], filaAdyacente, columnaAdyacente);
	if(posFronteraC)
		esAdyacente(posFronteraF, columnaFrontera[k]-1, filaAdyacente, columnaAdyacente);
	if(posFronteraC != g_columnas-1)
		esAdyacente(posFronteraF, columnaFrontera[k]+1, filaAdyacente, columnaAdyacente);
	if(!contador) adyacenteAConectar = 0;
	
	else adyacenteAConectar=rand()%contador;
	
	if(filaAdyacente[adyacenteAConectar] == posFronteraF-1){
		arbolExpansion[filaAdyacente[adyacenteAConectar]][columnaAdyacente[adyacenteAConectar]] += 2;
		arbolExpansion[posFronteraF][posFronteraC] += 8;
	}
	else if(filaAdyacente[adyacenteAConectar] == posFronteraF+1){
		arbolExpansion[filaAdyacente[adyacenteAConectar]][columnaAdyacente[adyacenteAConectar]] += 8;
		arbolExpansion[posFronteraF][posFronteraC] += 2;
	}
	else if(columnaAdyacente[adyacenteAConectar] == posFronteraC+1){
		arbolExpansion[filaAdyacente[adyacenteAConectar]][columnaAdyacente[adyacenteAConectar]] += 4;
		arbolExpansion[posFronteraF][posFronteraC] += 1;
	} 
	else{
		arbolExpansion[filaAdyacente[adyacenteAConectar]][columnaAdyacente[adyacenteAConectar]] += 1;
		arbolExpansion[posFronteraF][posFronteraC] += 4;
	}
	
	laberinto[posFronteraF][posFronteraC] = 1;
	marcarAdyacente(posFronteraF,posFronteraC);
	filaFrontera[k] = filaFrontera[n];
	columnaFrontera[k] = columnaFrontera[n];
	n--;
}

void generarLaberinto(){
	int i, j, randomR, randomC;
    
    columnaFrontera	= (char *)malloc(g_filas*g_columnas*sizeof(char));
	filaFrontera	= (char *)malloc(g_filas*g_columnas*sizeof(char));
	arbolExpansion	= (char **)malloc(g_filas*sizeof(char *));
	laberinto	 	= (char **)malloc(g_filas*sizeof(char *));
	
	for (i = 0; i < g_filas; i++){
		laberinto[i]		= (char *)malloc(g_columnas*sizeof(char));
		arbolExpansion[i]	= (char *)malloc(g_columnas*sizeof(char));
	}
  	
  	for (i = 0; i < g_filas; i++)
      	for (j = 0; j < g_columnas; j++){
			laberinto[i][j]	= 0;
			arbolExpansion[i][j] = 0;
		}
	
	randomR	= rand()%g_filas;
	randomC	= rand()%g_columnas;
	laberinto[randomR][randomC] = 16;
	
	marcarAdyacente(randomR,randomC);
	
	asignarConexion();
	
	while(n != -1)
		asignarConexion();


	//ARBOL DE EXPANSION
	for (i = 0;i < g_filas;i++){
 		for (j = 0;j < g_columnas;j++)
			printf("%d\t",arbolExpansion[i][j]);
		printf("\n");
    }

}

void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data){
	float w, t, p, q;
	float x_scaling, y_scaling;
	float tex_width, tex_height;
	int filas = 0 + g_movY, columnas = 0 + g_movY;
	
	GdkRectangle da;
	GdkWindow *window;
	cairo_surface_t *celda;
	
	window = gtk_widget_get_window(widget);
	celda = cairo_image_surface_create_from_png("data/1.png");
	tex_width 	= cairo_image_surface_get_width(celda);
	tex_height 	= cairo_image_surface_get_height(celda);
	gdk_window_get_geometry(window, &da.x, &da.y, &da.width, &da.height);	// Determinamos el tamaño de la drawing area y la ponemos en el 
	cairo_translate (cr, da.width / 2, da.height / 2);						// centro del widget.
	
	p = (float)16*(g_columnas-g_zoomX);			//Inicio de x
	q = (float)16*(g_filas-g_zoomY);			//Inicio de y
	
	w = (float)da.width/(g_columnas-g_zoomX);	//Ancho de cada cuadrito
	t = (float)da.height/(g_filas-g_zoomY);		//Largo de cada cuadrito
	x_scaling = w / tex_width;
	y_scaling = t / tex_height;
	cairo_scale (cr, x_scaling, y_scaling);
	
	cairo_set_source_rgba(cr, 0, 0, 0, 0);
	cairo_set_line_width(cr, 0);
    
    char buf[2048];
	for(int x = -p; x < p; x += 32){						//Las imagenes son de 32x32
		for(int y = -q; y < q; y += 32){
			sprintf(buf, "data/%d.png", arbolExpansion[filas][columnas]);
			celda = cairo_image_surface_create_from_png(buf);
            cairo_set_source_surface(cr, celda, x, y);
            cairo_paint(cr);
            
			if ((columnas - g_movY) == 0 && (filas - g_movX)== 0) 				//SACA ESQUINA SUPERIOR
                sprintf(buf, "data/entrada.png");
            if (columnas - g_movY == (g_columnas-1) && filas - g_movX == (g_filas-1)) //SACA ESQUINA INFERIOR
                sprintf(buf, "data/salida.png");
            celda = cairo_image_surface_create_from_png(buf);
            cairo_set_source_surface(cr, celda, x, y);
            cairo_paint(cr);
            filas++;
		}
		filas = 0 + g_movY;
		columnas++;
	}
}

void on_btnGenerar_clicked(){
	GtkWidget *lblCol, *lblFil, *spinCol, *spinFil, *caja, *dialog;
	
	dialog = gtk_dialog_new_with_buttons ("Elegir tamaño de la matriz", GTK_WINDOW(g_winPrincipal) , 
										  GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT, 
										  "_Aceptar" , GTK_RESPONSE_ACCEPT, 
										  "_Cancelar", GTK_RESPONSE_REJECT, NULL);
	caja = GTK_WIDGET(gtk_dialog_get_content_area(GTK_DIALOG(dialog)));
	
	lblCol = gtk_label_new("Columnas: ");
	lblFil = gtk_label_new("Filas: ");
	spinCol = gtk_spin_button_new_with_range (2	, 2048, 1);
	spinFil = gtk_spin_button_new_with_range (2, 2048, 1);
	
	gtk_container_add(GTK_CONTAINER(caja), lblFil);
	gtk_container_add(GTK_CONTAINER(caja), spinFil);
	gtk_container_add(GTK_CONTAINER(caja), lblCol);
	gtk_container_add(GTK_CONTAINER(caja), spinCol);
	gtk_widget_show_all(dialog);
	
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		gtk_widget_add_events(g_winPrincipal, GDK_SCROLL_MASK);
		gtk_widget_add_events(g_winPrincipal, GDK_BUTTON_PRESS_MASK);
		g_signal_connect(g_winPrincipal, "scroll-event", G_CALLBACK(mouse_scroll), NULL);
		g_signal_connect(g_winPrincipal, "button-press-event", G_CALLBACK(mouse_click), NULL);
		
		gtk_widget_set_sensitive (btnResolver, TRUE);
		gtk_widget_set_sensitive (btnGrabar, TRUE);
		
		g_zoomX = g_zoomY = 0;
		
		g_columnas 	= gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinCol));
		g_filas  	= gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinFil));
		
		g_signal_connect(g_areaPintado, "draw", G_CALLBACK (on_draw), NULL);
		generarLaberinto();
		
	}

	gtk_widget_destroy (dialog);
}


///---------------------------------------------------------------------
/// Botón leer
void leer (char nombre[1024]) {
	int i = 0, j = 0;
    char linea[1024];
    FILE *archivo = fopen(nombre, "r");
    
    while(fgets(linea, 1024, archivo)) {
        char * pch = strtok (linea," ,");
        while (pch != NULL){
            arbolExpansion[i][j] =  atoi(pch);
            pch = strtok (NULL, " ,"); 
            j++;
        } i++; j = 0;
    }
    fclose(archivo);
    
    gtk_widget_queue_draw (g_areaPintado);
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
/// Botón Guardar
void guardar (char nombre[1024]) {
	FILE* fichero;
	fichero = fopen(nombre, "w+");
    for(int i = 0; i < g_filas; i++) {
        for(int j = 0; j < g_columnas; j++) {
            fprintf(fichero, "%d,", arbolExpansion[i][j]);       
        }
        fprintf(fichero, "\n");
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
		guardar(filename);
	}
	gtk_widget_destroy (dialog);
}


///---------------------------------------------------------------------
/// Botón Resolver
void on_btnResolver_clicked(){
	GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(g_winPrincipal), 
												GTK_DIALOG_DESTROY_WITH_PARENT, 
												GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
												"No implementado");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}


///---------------------------------------------------------------------
/// Botón Salir
void on_winPrincipal_destroy (){
	gtk_main_quit();
}

///---------------------------------------------------------------------
/// Interfaz
void crearInterfaz(){
	GtkBuilder  *builder;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Interfaz.glade", NULL);
	
	g_winPrincipal 	= GTK_WIDGET(gtk_builder_get_object(builder, "winPrincipal"));
	g_areaPintado 	= GTK_WIDGET(gtk_builder_get_object(builder, "areaPintado"));
	btnResolver 	= GTK_WIDGET(gtk_builder_get_object(builder, "btnResolver"));
	btnGrabar 		= GTK_WIDGET(gtk_builder_get_object(builder, "btnGrabar"));
	
	gtk_widget_set_sensitive (btnGrabar, FALSE);
	gtk_widget_set_sensitive (btnResolver, FALSE);
	
	gtk_window_set_position(GTK_WINDOW(g_winPrincipal), GTK_WIN_POS_CENTER);
	gtk_window_resize(GTK_WINDOW(g_winPrincipal), WIDTH, HEIGHT);
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show_all(g_winPrincipal);
	g_object_unref(builder);
    gtk_main();   
}

int main(int argc, char **argv){
	srand(time(NULL));
	gtk_init(&argc, &argv);
	crearInterfaz();
	return 0;
}

