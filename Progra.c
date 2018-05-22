#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define WIDTH   840
#define HEIGHT  700

/// VARIABLES GLOBALES
GtkWidget *g_winPrincipal, *g_areaPintado;
GtkWidget *g_btnResolver, *g_btnGrabar;

GtkWidget		*g_areaEscribir;
GtkTextBuffer	*g_buffer;
GtkTextIter 	end, start;

GtkTextTag *rojo;
GtkTextTag *verde;
GtkTextTag *amarillo;
GtkTextTag *azul;
GtkTextTag *naranja;
GtkTextTag *morado;

gboolean activadoMC = TRUE, activadoMS = FALSE;

gboolean ratAle = TRUE, manDer = TRUE;
gboolean manIzq = TRUE, Pledge = TRUE;
gboolean Tremaux= TRUE, Fattah = TRUE;

char buf[14], buf2[100];

int **resultadoIzquierda, **resultadoDerecha;
int **resultadoraton, **resultadopledge;

int **laberinto, **arbolExpansion;
int *filaFrontera, *columnaFrontera;

int n = -1, c = 0, visitadas = 0, contador = -1, cantZoom = 2;
int	g_zoomX = 0, g_zoomY = 0, g_movX = 0, g_movY = 0;

int g_filas, g_columnas, direccion, i, j;

///---------------------------------------------------------------------
/// Zoom in/out
void mouse_scroll(GtkWidget *widget, GdkEventScroll *event, gpointer user_data){
	GdkScrollDirection dir = event->direction;
	if(activadoMS){
		if(dir == GDK_SCROLL_UP){			//ZOOM IN
			if(g_zoomX < g_columnas-cantZoom){
				g_zoomX += cantZoom;
				g_movX = 0, g_movY = 0;
			}
			if(g_zoomY < g_filas-cantZoom){
				g_zoomY += cantZoom;
				g_movX = 0, g_movY = 0;
			}
		}
		else if(dir == GDK_SCROLL_DOWN){	//ZOOM OUT
			if(g_zoomX > 0){
				g_zoomX -= cantZoom;
				g_movX = 0, g_movY = 0;
			}
			if(g_zoomY > 0){
				g_zoomY -= cantZoom;
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
	double centroX 		= gtk_widget_get_allocated_width(g_areaPintado)/2;
	double centroY 		= gtk_widget_get_allocated_height(g_areaPintado)/2;
	double clickX 		= event->x;
	double clickY		= event->y;
	
	if(activadoMC){
		//printf("g_movX: %d\tg_movy: %d\n", g_movX, g_movY);
		if(event->button == GDK_BUTTON_PRIMARY){			//Moverse en columnas
			if(clickX <= centroX){
				//printf("Izquierda\n");
				if(g_movX > 0)	g_movX--;
			}
			else{
				//printf("Derecha\n");
				if(g_movX < g_columnas-(g_columnas-g_zoomX))	g_movX++;
			}
		}
		else if (event->button == GDK_BUTTON_SECONDARY){	//Moverse en filas
			if(clickY <= centroY){
				//printf("Arriba\n");
				if(g_movY > 0)	g_movY--;
			}
			else{
				//printf("Abajo\n");
				if(g_movY < g_filas-(g_filas-g_zoomY)) g_movY++;
			}
		}
		gtk_widget_queue_draw (g_areaPintado);
		activadoMC = 0;
	}
	else activadoMC = 1;
}


///---------------------------------------------------------------------
/// Botón Generar
void agregarAdyacente(int filaIndice,int columnaIndice){
	if(!laberinto[filaIndice][columnaIndice]){
		n++;
		laberinto[filaIndice][columnaIndice] -= 1;
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
	
	marcarAdyacente(posFronteraF,posFronteraC);
	laberinto[posFronteraF][posFronteraC] = 1;
	columnaFrontera[k] = columnaFrontera[n];
	filaFrontera[k] = filaFrontera[n];
	n--;
}

void generarLaberinto(){
	int i, j, randomR, randomC;
	
	columnaFrontera	= (int *)malloc(g_filas*g_columnas*sizeof(int));
	filaFrontera	= (int *)malloc(g_filas*g_columnas*sizeof(int));
	arbolExpansion	= (int **)malloc(g_filas*sizeof(int *));
	laberinto	 	= (int **)malloc(g_filas*sizeof(int *));
	
	for (i = 0; i < g_filas; i++){
		laberinto[i]		= (int *)malloc(g_columnas*sizeof(int));
		arbolExpansion[i]	= (int *)malloc(g_columnas*sizeof(int));
	}
		
	for (i = 0; i < g_filas; i++)
		for (j = 0; j < g_columnas; j++){
			laberinto[i][j]	= 0;
			arbolExpansion[i][j] = 0;
		}
	
	if(g_columnas == 1 && g_filas == 1){
		if(rand()%2)
			arbolExpansion[0][0] = 5;
		else
			arbolExpansion[0][0] = 10;
	}
	
	else{	
		randomR	= rand()%g_filas;
		randomC	= rand()%g_columnas;
		laberinto[randomR][randomC] = 16;
		
		marcarAdyacente(randomR,randomC);
		
		asignarConexion();
		
		while(n != -1)
			asignarConexion();
	}
}

void on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data){
	float w, t, p, q;
	float x_scaling, y_scaling;
	float tex_width, tex_height;
	int filas = g_movY, columnas = g_movX;
	char buf[2048];
	
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
	
	cairo_set_line_width(cr, 1);
	
	if(g_columnas == 1 && g_filas == 1){
		sprintf(buf, "data/%d.png", arbolExpansion[filas][columnas]);
		celda = cairo_image_surface_create_from_png(buf);
		cairo_set_source_surface(cr, celda, -p, -q);
		cairo_paint(cr);
	}
	
	else if(g_columnas-g_zoomX > 400 && g_filas-g_zoomY > 400)
		cairo_paint(cr);
		
	else{
		for(int x = -p; x < p; x += 32){						//Las imagenes son de 32x32
			for(int y = -q; y < q; y += 32){
				sprintf(buf, "data/%d.png", arbolExpansion[filas][columnas]);
				celda = cairo_image_surface_create_from_png(buf);
				cairo_set_source_surface(cr, celda, x, y);
				cairo_paint(cr);
				if (!columnas && !filas){ //SACA ESQUINA SUPERIOR
					sprintf(buf, "data/entrada.png");
					celda = cairo_image_surface_create_from_png(buf);
					cairo_set_source_surface(cr, celda, x, y);
					cairo_paint(cr);
				}
				if (columnas == (g_columnas-1) && filas == (g_filas-1)){ //SACA ESQUINA INFERIOR
					sprintf(buf, "data/salida.png");
					celda = cairo_image_surface_create_from_png(buf);
					cairo_set_source_surface(cr, celda, x, y);
					cairo_paint(cr);
				}
				filas++;
			}
			filas = g_movY;
			columnas++;
		}
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
	spinCol = gtk_spin_button_new_with_range (1	, 2048, 1);
	spinFil = gtk_spin_button_new_with_range (1, 2048, 1);
	
	gtk_container_add(GTK_CONTAINER(caja), lblFil);
	gtk_container_add(GTK_CONTAINER(caja), spinFil);
	gtk_container_add(GTK_CONTAINER(caja), lblCol);
	gtk_container_add(GTK_CONTAINER(caja), spinCol);
	
	gtk_widget_show_all(dialog);
	
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		gtk_text_buffer_get_bounds (g_buffer, &start, &end);
		gtk_text_buffer_delete(g_buffer, &start, &end);
		
		gtk_widget_add_events(g_winPrincipal, GDK_SCROLL_MASK);
		gtk_widget_add_events(g_winPrincipal, GDK_BUTTON_PRESS_MASK);
		
		g_signal_connect(g_winPrincipal, "scroll-event", G_CALLBACK(mouse_scroll), NULL);
		g_signal_connect(g_winPrincipal, "button-press-event", G_CALLBACK(mouse_click), NULL);
		
		gtk_widget_set_sensitive (g_btnResolver, TRUE);
		gtk_widget_set_sensitive (g_btnGrabar, TRUE);
		
		g_zoomX = g_zoomY = 0;
		g_movX = g_movY = 0;
		
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
    
	fgets(linea, 1024, archivo);
    g_filas = atoi(linea);
    
    
    fgets(linea, 1024, archivo);	
    g_columnas = atoi(linea);

    
	//printf("entra\n");
	gtk_widget_set_sensitive (g_btnResolver, TRUE);
	gtk_widget_set_sensitive (g_btnGrabar, TRUE);
    g_signal_connect(g_areaPintado, "draw", G_CALLBACK (on_draw), NULL);
	generarLaberinto();

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
	fprintf(fichero, "%d\n", g_filas);
    fprintf(fichero, "%d\n", g_columnas);
    
	
    for(int i = 0; i < g_filas; i++) {
        for(int j = 0; j < g_columnas; j++) {
            fprintf(fichero, "%d,", arbolExpansion[i][j]);       
        }
        fprintf(fichero, "\n");
	}
	fclose(fichero);
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
int inicializarRespuestas(){
	resultadoIzquierda	= (int **)malloc((g_filas)*sizeof(int *));
	resultadoDerecha 	= (int **)malloc((g_filas)*sizeof(int *));
	resultadopledge		= (int **)malloc((g_filas)*sizeof(int *));
	resultadoraton		= (int **)malloc((g_filas)*sizeof(int *));

	for (i = 0; i < g_filas; i++){
		resultadoIzquierda[i]= (int *)malloc((g_columnas)*sizeof(int));   
		resultadoDerecha[i]	 = (int *)malloc((g_columnas)*sizeof(int));
		resultadopledge[i]	 = (int *)malloc((g_columnas)*sizeof(int));
		resultadoraton[i]	 = (int *)malloc((g_columnas)*sizeof(int));
    }

	for (i = 0; i < g_filas; i++)
      	for (j = 0; j < g_columnas; j++){
			resultadoIzquierda[i][j]= 0;
			resultadoDerecha[i][j] 	= 0;
			resultadopledge[i][j] 	= 0;
			resultadoraton[i][j] 	= 0;
        }
	
	return 1;
}

gboolean avanzar(int direccion, int direccionAnterior,int i, int j){
	if((direccionAnterior += 2)%4 == direccion)
		return FALSE;
	else if((direccion == 0) && (arbolExpansion[i][j]&1))
		return TRUE;
	else if((direccion == 1) && ((arbolExpansion[i][j]>>1)&1))
		return TRUE;
	else if((direccion == 2) && ((arbolExpansion[i][j]>>2)&1))
		return TRUE;
	else if((direccion == 3) && ((arbolExpansion[i][j]>>3)&1))
		return TRUE;
	return FALSE;
}

void raton(){
	int pXInicio = 0, pYInicio = 0, numPos = 0, direccion = 0;
	int cambioDireccion, direccionRandom;
	arbolExpansion[0][0] -= 4;
	
	while((pXInicio < g_filas-1) || (pYInicio < g_columnas-1)){
		cambioDireccion = 0;
		if(arbolExpansion[pXInicio][pYInicio] == 1)
			direccion = 0;
		else if(arbolExpansion[pXInicio][pYInicio] == 2)
			direccion = 1;
		else if(arbolExpansion[pXInicio][pYInicio] == 4)
			direccion = 2;
		else if(arbolExpansion[pXInicio][pYInicio] == 8)
			direccion = 3;
		else
			while(!cambioDireccion){
				direccionRandom = rand()%4;
				if(avanzar(direccionRandom,direccion,pXInicio,pYInicio)){
					cambioDireccion = 1;
					direccion = direccionRandom;
				}
			}
		if(direccion == 0){
			visitadas++;
			pYInicio++;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		else if(direccion == 1){
			visitadas++;
			pXInicio++;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		else if(direccion == 2){
			visitadas++;
			if(pYInicio > 0)
				pYInicio--;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		else{
			visitadas++;
			if(pXInicio > 0)
				pXInicio--;
            resultadoraton[pXInicio][pYInicio]++; //OJO
		}
		numPos++;
	}
	arbolExpansion[0][0] += 4;
	visitadas++;
}

gboolean preguntaSur(int pNum){
	if((pNum == 2) || (pNum == 3) || (pNum == 6) || (pNum == 7) || (pNum == 10) || (pNum == 11) || (pNum == 14) || (pNum == 15))
		return TRUE;
	return FALSE;
}

gboolean preguntaEste(int pNum){
	if((pNum == 1) || (pNum == 3) || (pNum == 5) || (pNum == 7) || (pNum == 9) || (pNum == 11) || (pNum == 13) || (pNum == 15))
		return TRUE;
	return FALSE;
}

gboolean preguntaNorte(int pNum){
	if((pNum == 8) || (pNum == 9) || (pNum == 10) || (pNum == 11) || (pNum == 12) || (pNum == 13) || (pNum == 14) || (pNum == 15))
		return TRUE;
	return FALSE;
}

gboolean preguntaOeste(int pNum){
	if((pNum == 4) || (pNum == 5) || (pNum == 6) || (pNum == 7) || (pNum == 12) || (pNum == 13) || (pNum == 14) || (pNum == 15))
		return TRUE;
	return FALSE;
}

void resuelveDerecha(){		/// REGLA DERECHA
	int pXInicio = 0, pYInicio = 0;
	int numPos = 0, i = 0;
	
	resultadoDerecha[pXInicio][pYInicio] = 1;
	direccion = 0;
	
	while(!(pXInicio == (g_columnas-1) && pYInicio == (g_filas-1))){ 
		i++;
		numPos = arbolExpansion[pXInicio][pYInicio];
		
		if(direccion == 3){
			if(preguntaEste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pYInicio++;
				direccion = 0;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else if(preguntaNorte(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pXInicio--;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else direccion = 2;
		}
		else if(direccion == 2){
			if(preguntaNorte(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pXInicio--;
				direccion = 3;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else if(preguntaOeste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pYInicio--;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else direccion = 1;
		}
		else if(direccion == 1){
			if(preguntaOeste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pYInicio--;
				direccion = 2;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else if(preguntaSur(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pXInicio++;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else direccion = 0;
		}
		else if(direccion == 0){
			if(preguntaSur(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pXInicio++;
				direccion = 1;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else if(preguntaEste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
				visitadas++;
				pYInicio++;
				resultadoDerecha[pXInicio][pYInicio]++;
			}
			else direccion = 3;
		}
	}
	visitadas++;
}

void resuelveIzquierda(){	/// REGLA IZQUIERDA
	int pXInicio = 0, pYInicio = 0;
	int numPos = 0, i = 0;

	resultadoIzquierda[pXInicio][pYInicio] = 1;
	direccion = 0;

	while(!(pXInicio == (g_columnas-1) && pYInicio == (g_filas-1))){ 
		i++;
		numPos = arbolExpansion[pXInicio][pYInicio];
		if(direccion == 3){
			if(preguntaOeste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pYInicio--;
				direccion = 2;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else if(preguntaNorte(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pXInicio--;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else direccion = 1;
		}
		else if(direccion == 2){
			if(preguntaSur(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pXInicio++;
				direccion = 1;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else if(preguntaOeste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pYInicio--;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else direccion = 0;
		}
		else if(direccion == 1){
			if(preguntaEste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pYInicio++;
				direccion = 0;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else if(preguntaSur(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pXInicio++;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else direccion = 3;
		}
		else if(direccion == 0){
			if(preguntaNorte(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pXInicio--;
				direccion = 3;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else if(preguntaEste(numPos)){
				/*sprintf(buf, "(%d, %d)->", pXInicio, pYInicio);
				gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
				visitadas++;
				pYInicio++;
				resultadoIzquierda[pXInicio][pYInicio]++;
			}
			else direccion = 2;
		}
	}
	visitadas++;
}

void pledge(){
    int pXInicio = 0, pYInicio = 0, pCounter = 0, numPos = 0;
	arbolExpansion[0][0] -= 4;
	while((pXInicio < g_filas-1) || (pYInicio < g_columnas-1)){
		if(pCounter != 0){
			if(pCounter%4 == 1){
				if(arbolExpansion[pXInicio][pYInicio]&1){
					pCounter--;
					pYInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else if((arbolExpansion[pXInicio][pYInicio]>>1)&1){
					pXInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else
					pCounter++;
			}
			else if(pCounter%4 == 0){
				if((arbolExpansion[pXInicio][pYInicio]>>3)&1){
					pCounter--;
					pXInicio--;
					resultadopledge[pXInicio][pYInicio]++; //OJO
					visitadas++;
				}
				else if(arbolExpansion[pXInicio][pYInicio]&1){
					pYInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else
					pCounter++;
			}
			else if(pCounter%4 == 3){
				if((arbolExpansion[pXInicio][pYInicio]>>2)&1){
					pCounter--;
					pYInicio--;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else if((arbolExpansion[pXInicio][pYInicio]>>3)&1){
					pXInicio--;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else
					pCounter++;
			}
			else{
				if((arbolExpansion[pXInicio][pYInicio]>>1)&1){
					pCounter--;
					pXInicio++;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else if((arbolExpansion[pXInicio][pYInicio]>>2)&1){
					pYInicio--;
                    resultadopledge[pXInicio][pYInicio]++; //OJO
                    visitadas++;
				}
				else
					pCounter++;
			}
		}
		else{
			if(!(arbolExpansion[pXInicio][pYInicio]&1)){
				pCounter++;
                resultadopledge[pXInicio][pYInicio]++; //OJO
                visitadas++;
			}
			else{
				pYInicio++;
                resultadopledge[pXInicio][pYInicio]++; //OJO
                visitadas++;
			}
		}
		numPos++;
	}
	arbolExpansion[0][0]+=4;
	visitadas++;
}

void on_draw2(GtkWidget *widget, cairo_t *cr, gpointer user_data){
	int mult = 0, a;
	float w, t, p, q, alpha;
	float x_scaling, y_scaling;
	int filas = g_movY, columnas = g_movX;
	
	GdkRectangle da;
	GdkWindow *window;
	
	window = gtk_widget_get_window(widget);
	gdk_window_get_geometry(window, &da.x, &da.y, &da.width, &da.height);	// Determinamos el tamaño de la drawing area y la ponemos en el 
	cairo_translate (cr, da.width / 2, da.height / 2);						// centro del widget.
		
	p = (float)16*(g_columnas-g_zoomX);			//Inicio de x
	q = (float)16*(g_filas-g_zoomY);			//Inicio de y
	
	w = (float)da.width/(g_columnas-g_zoomX);	//Ancho de cada cuadrito
	t = (float)da.height/(g_filas-g_zoomY);		//Largo de cada cuadrito
	
	x_scaling = w / 32;
	y_scaling = t / 32;
	cairo_scale (cr, x_scaling, y_scaling);
	
	a = ratAle + manDer + manIzq + Pledge + Tremaux + Fattah;
	for(int x = -p; x < p; x += 32){						//Las imagenes son de 32x32
		for(int y = -q; y < q; y += 32){
			if(ratAle){
				alpha = 0.20+((float)(resultadoDerecha[filas][columnas])/10)*1.5;
				cairo_set_source_rgba(cr, 0.901, 0.098, 0.294, alpha);	//Rojo
				if(resultadoraton[filas][columnas]){
					cairo_rectangle(cr, (x+8)+((16/a)*mult), y+8, 16/a, 16);
					cairo_fill(cr);
					mult++;
				}
			}
			if(manDer){
				alpha = 0.20+((float)(resultadoDerecha[filas][columnas])/10)*2.5;
				cairo_set_source_rgba(cr, 0.235, 0.705, 0.294, alpha);	//Verde
				if(resultadoDerecha[filas][columnas]){
					cairo_rectangle(cr, (x+8)+((16/a)*mult), y+8, 16/a, 16);
					cairo_fill(cr);
					mult++;
				}
			}
			if(manIzq){
				alpha = 0.20+((float)(resultadoIzquierda[filas][columnas])/10)*2.5;
				cairo_set_source_rgba(cr, 1.000, 0.882, 0.098, alpha);	//Amarillo
				if(resultadoIzquierda[filas][columnas]){
					cairo_rectangle(cr, (x+8)+((16/a)*mult), y+8, 16/a, 16);
					cairo_fill(cr);
					mult++;
				}
			}
			if(Pledge){
				alpha = 0.20+((float)(resultadoDerecha[filas][columnas])/10)*2.5;
				cairo_set_source_rgb(cr, 0.000, 0.509, 0.784);	//Azul
				if(resultadopledge[filas][columnas]){
					cairo_rectangle(cr, (x+8)+((16/a)*mult), y+8, 16/a, 16);
					cairo_fill(cr);
					mult++;
				}
			}
			if(Tremaux){
				cairo_set_source_rgb(cr, 0.960, 0.509, 0.188);	//Naranja
				mult++;
			}
			if(Fattah){
				cairo_set_source_rgb(cr, 0.568, 0.117, 0.705);	//Morado
				mult++;
			}
			filas++;
			mult = 0;
		}
		filas = g_movY;
		columnas++;
	}
}

void on_btnResolver_clicked(){
	GtkWidget *label, *btnRatonAleatorio, *btnReglaDerecha, 
			  *btnReglaIzquierda, *btnPledge, *btnTremaux, 
			  *btnFattah, *caja, *dialog;
	dialog = gtk_dialog_new_with_buttons ("Elegir algoritmos para resolver", GTK_WINDOW(g_winPrincipal) , 
										  GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT, 
										  "_Ejecutar" , GTK_RESPONSE_ACCEPT, 
										  "_Cancelar", GTK_RESPONSE_REJECT, NULL);
	
	caja = GTK_WIDGET(gtk_dialog_get_content_area(GTK_DIALOG(dialog)));
	
	label 				= gtk_label_new("Seleccione los algoritmos que quiera ver:\n");
	btnRatonAleatorio	= gtk_check_button_new_with_label("Ratón aleatorio");
	btnReglaDerecha		= gtk_check_button_new_with_label("Regla de la mano derecha");
	btnReglaIzquierda	= gtk_check_button_new_with_label("Regla de la mano izquierda");
	btnPledge			= gtk_check_button_new_with_label("Algoritmo de Pledge");
	btnTremaux			= gtk_check_button_new_with_label("Algoritmo de Trémaux");
	btnFattah			= gtk_check_button_new_with_label("Algoritmo de Fattah");
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btnRatonAleatorio), TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btnReglaDerecha), TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btnReglaIzquierda), TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btnPledge), TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btnTremaux), TRUE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btnFattah), TRUE);
	
	gtk_container_add(GTK_CONTAINER(caja), label);
	gtk_container_add(GTK_CONTAINER(caja), btnRatonAleatorio);
	gtk_container_add(GTK_CONTAINER(caja), btnReglaDerecha);
	gtk_container_add(GTK_CONTAINER(caja), btnReglaIzquierda);
	gtk_container_add(GTK_CONTAINER(caja), btnPledge);
	gtk_container_add(GTK_CONTAINER(caja), btnTremaux);
	gtk_container_add(GTK_CONTAINER(caja), btnFattah);
	
	gtk_widget_show_all(dialog);
	
	int respuesta = gtk_dialog_run (GTK_DIALOG (dialog));
	if (respuesta == GTK_RESPONSE_ACCEPT) {
		inicializarRespuestas();
		ratAle 	= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btnRatonAleatorio));
		manDer 	= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btnReglaDerecha));
		manIzq 	= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btnReglaIzquierda));
		Pledge 	= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btnPledge));
		Tremaux = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btnTremaux));
		Fattah 	= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(btnFattah));
		
		gtk_text_buffer_get_bounds (g_buffer, &start, &end);
		gtk_text_buffer_delete(g_buffer, &start, &end);
		if(ratAle){
			gtk_text_buffer_insert_with_tags(g_buffer, &end,"Ratón aleatorio:\n", -1, rojo, NULL);
			raton();
			sprintf(buf2, "Casillas vistadas: %d\n\n", visitadas);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf2, -1, rojo, NULL);
			visitadas = 0;
		}
		if(manDer){
			gtk_text_buffer_insert_with_tags(g_buffer, &end,"Regla de la mano derecha:\n", -1, verde, NULL);
			resuelveDerecha();
			/*sprintf(buf, "(%d, %d)\n", g_filas-1, g_columnas-1);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, verde, NULL);*/
			sprintf(buf2, "Casillas vistadas: %d\n\n", visitadas);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf2, -1, verde, NULL);
			visitadas = 0;
		}
		if(manIzq){
			gtk_text_buffer_insert_with_tags(g_buffer, &end,"Regla de la mano izquierda:\n", -1, amarillo, NULL);
			resuelveIzquierda();
			/*sprintf(buf, "(%d, %d)\n", g_filas-1, g_columnas-1);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf, -1, amarillo, NULL);*/
			sprintf(buf2, "Casillas vistadas: %d\n\n", visitadas);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf2, -1, amarillo, NULL);
			visitadas = 0;
		}
		if(Pledge){
			gtk_text_buffer_insert_with_tags(g_buffer, &end,"Algoritmo de Pledge:\n", -1, azul, NULL);
			pledge();
			sprintf(buf2, "Casillas vistadas: %d\n\n", visitadas);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf2, -1, azul, NULL);
			visitadas = 0;
		}
		if(Tremaux){
			gtk_text_buffer_insert_with_tags(g_buffer, &end,"Algoritmo de Trémaux:\n", -1, naranja, NULL);
			sprintf(buf2, "Casillas vistadas: %d\n\n", visitadas);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf2, -1, naranja, NULL);
			visitadas = 0;
		}
		if(Fattah){
			gtk_text_buffer_insert_with_tags(g_buffer, &end,"Algoritmo de Fattah:\n", -1, morado, NULL);
			sprintf(buf2, "Casillas vistadas: %d\n\n", visitadas);
			gtk_text_buffer_insert_with_tags(g_buffer, &end, buf2, -1, morado, NULL);
			visitadas = 0;
		}
		
		g_signal_connect(g_areaPintado, "draw", G_CALLBACK (on_draw2), NULL);
	}
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
	g_areaEscribir	= GTK_WIDGET(gtk_builder_get_object(builder, "areaEscribir"));
	g_areaPintado 	= GTK_WIDGET(gtk_builder_get_object(builder, "areaPintado"));
	g_btnResolver 	= GTK_WIDGET(gtk_builder_get_object(builder, "btnResolver"));
	g_btnGrabar 	= GTK_WIDGET(gtk_builder_get_object(builder, "btnGrabar"));
	g_buffer 		= gtk_text_view_get_buffer (GTK_TEXT_VIEW (g_areaEscribir));
	
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (g_areaEscribir), TRUE);
	
	rojo 	 = gtk_text_buffer_create_tag (g_buffer, "rojo", "foreground", "#e6194b", NULL);
	verde 	 = gtk_text_buffer_create_tag (g_buffer, "verde", "foreground", "#3cb44b", NULL);
	amarillo = gtk_text_buffer_create_tag (g_buffer, "amarillo", "foreground", "#ffe119", NULL);
	azul	 = gtk_text_buffer_create_tag (g_buffer, "azul", "foreground", "#0082c8", NULL);
	naranja	 = gtk_text_buffer_create_tag (g_buffer, "naranja", "foreground", "#f58231", NULL);
	morado	 = gtk_text_buffer_create_tag (g_buffer, "morado", "foreground", "#911eb4", NULL);
									
	gtk_widget_set_sensitive (g_btnResolver, FALSE);
	gtk_widget_set_sensitive (g_btnGrabar, FALSE);
	
	gtk_window_set_position(GTK_WINDOW(g_winPrincipal), GTK_WIN_POS_CENTER);
	gtk_window_resize(GTK_WINDOW(g_winPrincipal), WIDTH, HEIGHT);
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show_all(g_winPrincipal);
	g_object_unref(builder);
    gtk_main();   
}


///---------------------------------------------------------------------
/// Main
int main(int argc, char **argv){
	srand(time(NULL));
	gtk_init(&argc, &argv);
	crearInterfaz();
	return 0;
}

