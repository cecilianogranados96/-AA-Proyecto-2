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
int 		g_width;
int			g_height;
int         c = 0; //TAMAÑO PARA ARCHIVO DE GUARDAR Y LEER

int **laberinto, **arbolExpansion;
int *filaFrontera, *columnaFrontera;
int n=-1, contador=-1;

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
	if(filaIndice != g_width-1)
		agregarAdyacente(filaIndice+1, columnaIndice);	
	if(columnaIndice)
		agregarAdyacente(filaIndice, columnaIndice-1);
	if(columnaIndice != g_height-1)
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
	int k,adyacenteAConectar,posFronteraF,posFronteraC;
	int filaAdyacente[4],columnaAdyacente[4];
	
	if(!n) k = 0;
	else k = rand()%n;
		
	posFronteraF = filaFrontera[k];
	posFronteraC = columnaFrontera[k];
	contador = -1;
	
	if(posFronteraF)
		esAdyacente(posFronteraF-1, posFronteraC, filaAdyacente, columnaAdyacente);
	if(posFronteraF != g_width-1)
		esAdyacente(posFronteraF+1, columnaFrontera[k], filaAdyacente, columnaAdyacente);
	if(posFronteraC)
		esAdyacente(posFronteraF, columnaFrontera[k]-1, filaAdyacente, columnaAdyacente);
	if(posFronteraC != g_height-1)
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
	int i,j,randomR,randomC;
    
    columnaFrontera	= (int *)malloc(g_width*g_height*sizeof(int));
	filaFrontera	= (int *)malloc(g_width*g_height*sizeof(int));
	arbolExpansion	= (int **)malloc(g_width*sizeof(int *));
	laberinto	 	= (int **)malloc(g_width*sizeof(int *));
	
	for (i = 0; i < g_width; i++){
		laberinto[i]	= (int *)malloc(g_height*sizeof(int));
		arbolExpansion[i]	= (int *)malloc(g_height*sizeof(int));
	}
  	
  	for (i = 0; i < g_width; i++){
      	for (j = 0; j < g_height; j++){
			laberinto[i][j]	= 0;
			arbolExpansion[i][j] = 0;
		}
	}
	
	randomR	= rand()%g_width;
	randomC	= rand()%g_height;
	laberinto[randomR][randomC] = 16;
	
	marcarAdyacente(randomR,randomC);
	
	asignarConexion();
	
	while(n != -1)
		asignarConexion();


	//ARBOL DE EXPANCION
	for (i = 0;i < g_width;i++){
 		for (j = 0;j < g_height;j++)
			printf("%d\t",arbolExpansion[i][j]);
		printf("\n");
    }

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
	tex_width 	= cairo_image_surface_get_width (piso);
	tex_height 	= cairo_image_surface_get_height (piso);
	gdk_window_get_geometry (window, &da.x, &da.y, &da.width, &da.height);	// Determinamos el tamaño de la drawing area y la ponemos en el 
	cairo_translate (cr, da.width / 2, da.height / 2);						// centro del widget.
	
	q = (float)16*g_width;		//Inicio de x
	p = (float)16*g_height;		//Inicio de y
	w = (float)da.width/g_width;	//Ancho de cada cuadrito
	t = (float)da.height/g_height;	//Largo de cada cuadrito
	x_scaling = (w / tex_width);
	y_scaling = (t / tex_height);
	cairo_scale (cr, x_scaling, y_scaling);
	cairo_set_line_width(cr, 0); 
    
    
    char buf[2048];
    
	for(double x = -p; x < p; x += 32){						//Las imagenes son de 32x32
		for(double y = -q; y < q; y += 32){
			//printf("R: %d y C: %d\n",filas, columnas);
			if ((columnas == 0 && filas == 0)) 				//SACA ESQUINA SUPERIOR
                sprintf(buf, "data/%d.png", 7);
            else if(columnas == (g_width-1) && filas == (g_height-1)) //SACA ESQUINA INFERIOR
                sprintf(buf, "data/%d.png", 13);
            else
                sprintf(buf, "data/%d.png", arbolExpansion[filas][columnas]); //EL RESTO ESCRIBE LO QUE TINENE EL ARBOL DE EXPANSION
            printf("\nfilas: %d columnas: %d\n", filas, columnas);
            pared = cairo_image_surface_create_from_png(buf);
            printf("x: %f y: %f\t", x, y);
            cairo_set_source_surface(cr, pared, x, y);
            cairo_paint(cr);
            filas++;
		}
		printf("\n");
		filas = 0;
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
	
	lblFil = gtk_label_new("Columnas: ");
	lblCol = gtk_label_new("Filas: ");
	spinFil = gtk_spin_button_new_with_range (1	, 2048, 1);
	spinCol = gtk_spin_button_new_with_range (1, 2048, 1);
	
	gtk_container_add(GTK_CONTAINER(caja), lblFil);
	gtk_container_add(GTK_CONTAINER(caja), spinFil);
	gtk_container_add(GTK_CONTAINER(caja), lblCol);
	gtk_container_add(GTK_CONTAINER(caja), spinCol);
	gtk_widget_show_all(dialog);
	
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		gtk_widget_set_sensitive (btnResolver, TRUE);
		gtk_widget_set_sensitive (btnGrabar, TRUE);
		g_height = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinFil));
		g_width  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spinCol));
		
		g_signal_connect(g_areaPintado, "draw", G_CALLBACK (on_draw), NULL);
		//
		generarLaberinto();
		//
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
    
    //AQUI DEBERIA LLAMAR A ON DRAW    
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
    for(int i = 0; i < g_width; i++) {
        for(int j = 0; j < g_height; j++) {
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
/// Zoom in
void on_btnZoomIn_clicked(){
	printf("ZoomIn\n");
	gtk_widget_queue_draw (g_areaPintado);
    //cairo_scale(g_areaPintado, 0.7, 0.7);
    
}


///---------------------------------------------------------------------
/// Zoom out
void on_btnZoomOut_clicked(){
	printf("ZoomOut\n");
	gtk_widget_queue_draw (g_areaPintado);
}


///---------------------------------------------------------------------
/// Interfaz
void crearInterfaz(){
	GtkBuilder  *builder;
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "Interfaz.glade", NULL);
	
	g_winPrincipal 	= GTK_WIDGET(gtk_builder_get_object(builder, "winPrincipal"));
	g_areaPintado 	= GTK_WIDGET(gtk_builder_get_object(builder, "areaPintado"));
	btnResolver = GTK_WIDGET(gtk_builder_get_object(builder, "btnResolver"));
	btnGrabar = GTK_WIDGET(gtk_builder_get_object(builder, "btnGrabar"));
	
	gtk_widget_set_sensitive (btnResolver, FALSE);
	gtk_widget_set_sensitive (btnGrabar, FALSE);
	
	gtk_window_set_position(GTK_WINDOW(g_winPrincipal), GTK_WIN_POS_CENTER);
	gtk_window_resize(GTK_WINDOW(g_winPrincipal), WIDTH, HEIGHT);
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show_all(g_winPrincipal);
	g_object_unref(builder);
    gtk_main();   
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	gtk_init(&argc, &argv);
	crearInterfaz();
	return 0;
}

