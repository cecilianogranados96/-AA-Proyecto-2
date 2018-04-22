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

int **laberinto,**spanningTree,*frontierR,*frontierC,n=-1,counter=-1;

void addAdjacent(int rowIndex,int columnIndex){
	if(laberinto[rowIndex][columnIndex]==0){
		n++;
		laberinto[rowIndex][columnIndex]=-1;
		frontierR[n]=rowIndex;
		frontierC[n]=columnIndex;
	}
}

void markAdjacent(int rowIndex,int columnIndex){
	if(rowIndex!=0){
		addAdjacent(rowIndex-1,columnIndex);
	}
	if(rowIndex!=g_width-1){
		addAdjacent(rowIndex+1,columnIndex);	
	}
	if(columnIndex!=0){
		addAdjacent(rowIndex,columnIndex-1);
	}
	if(columnIndex!=g_height-1){
		addAdjacent(rowIndex,columnIndex+1);
	}
}

void isAdjacent(int indexR,int indexC,int adjacentR[],int adjacentC[]){
	if((laberinto[indexR][indexC]==1)||(laberinto[indexR][indexC]==16)){
		counter++;
		adjacentR[counter]=indexR;
		adjacentC[counter]=indexC;
	}
}

void asignConection(){
	int k,adjacentR[4],adjacentC[4],adjacentToConnect,frontierCellR,frontierCellC;
	if(n==0){
		k=0;
	}else{
		k=rand()%n;
	}
	frontierCellR=frontierR[k],frontierCellC=frontierC[k];
	counter=-1;
	if(frontierCellR!=0){
		isAdjacent(frontierCellR-1,frontierCellC,adjacentR,adjacentC);
	}
	if(frontierCellR!=g_width-1){
		isAdjacent(frontierCellR+1,frontierC[k],adjacentR,adjacentC);	
	}
	if(frontierCellC!=0){
		isAdjacent(frontierCellR,frontierC[k]-1,adjacentR,adjacentC);
	}
	if(frontierCellC!=g_height-1){
		isAdjacent(frontierCellR,frontierC[k]+1,adjacentR,adjacentC);
	}
	if(counter==0){
		adjacentToConnect=0;
	}else{
		adjacentToConnect=rand()%counter;
	}
	if(adjacentR[adjacentToConnect]==frontierCellR-1){
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=2;
		spanningTree[frontierCellR][frontierCellC]+=8;
	}else if(adjacentR[adjacentToConnect]==frontierCellR+1){
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=8;
		spanningTree[frontierCellR][frontierCellC]+=2;
	}else if(adjacentC[adjacentToConnect]==frontierCellC+1){
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=4;
		spanningTree[frontierCellR][frontierCellC]+=1;
	} else{
		spanningTree[adjacentR[adjacentToConnect]][adjacentC[adjacentToConnect]]+=1;
		spanningTree[frontierCellR][frontierCellC]+=4;
	}
	laberinto[frontierCellR][frontierCellC]=1;
	markAdjacent(frontierCellR,frontierCellC);
	frontierR[k]=frontierR[n];
	frontierC[k]=frontierC[n];
	n--;
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
	cairo_set_line_width(cr, 1); 
    
    int i,j,randomR,randomC;
    
	frontierR=(int *)malloc(g_width*g_height*sizeof(int));
	frontierC=(int *)malloc(g_width*g_height*sizeof(int));
	spanningTree=(int **)malloc(g_width*sizeof(int *)); // OJO CON ESTO AL LEER
	laberinto=(int **)malloc(g_width*sizeof(int *));
	for (i = 0; i < g_width; i++){
		laberinto[i]=(int *)malloc(g_height*sizeof(int));
		spanningTree[i]=(int *)malloc(g_height*sizeof(int));
	}
  	for (i = 0; i < g_width; i++){
      		for (j = 0; j < g_height; j++){
			laberinto[i][j]=0;
			spanningTree[i][j]=0;
		}
	}
	randomR=rand()%g_width;
	randomC=rand()%g_height;
	laberinto[randomR][randomC]=16;
	markAdjacent(randomR,randomC);
	asignConection();
	while(n!=-1){
		asignConection();
	}

    
    /*
	//ARBOL DE EXPACION
	for (i = 0;i<g_width;i++){
 		for (j = 0;j<g_height;j++){
			printf("%d\t",spanningTree[i][j]);
		}
		printf("\n");
    }
    */
    
    
    char buf[1024];
	for(double x = p; x < -p; x += 32){						//Las imagenes son de 32x32
		for(double y = q; y < -q; y += 32){		
            //printf("C:%d F:%d ",columnas,filas);
    
                    
                    
            if ((columnas == 0 && filas == 0)) { //SACA ESQUINA SUPERIOR
                sprintf(buf, "data/%d.png", 7);
            }else{
                if (((columnas == (g_width-1)) &&  (filas == (g_height-1)))){ //SACA ESQUINA INFERIOR
                    sprintf(buf, "data/%d.png", 13);
                }else{
                    sprintf(buf, "data/%d.png", spanningTree[columnas][filas]); //EL RESTO ESCRIBE LO QUE TINENE EL ARBOL DE EXPANCION
                }
            }
            
            pared = cairo_image_surface_create_from_png(buf);
            cairo_set_source_surface(cr, pared, x, y);
            cairo_paint(cr);
            columnas++;
		}
        //printf("\n");
		filas++;
		columnas = 0;
	}
    
}
///---------------------------------------------------------------------
void leer (char nombre[1024]) {
	int i = 0, j = 0;
    char linea[1024];
    FILE *archivo = fopen(nombre, "r");
    
    while(fgets(linea, 1024, archivo)) {
        char * pch = strtok (linea," ,");
        while (pch != NULL){
            spanningTree[i][j] =  atoi(pch);
            pch = strtok (NULL, " ,"); 
            j++;
        } i++; j = 0;
    }
    fclose(archivo);
    
    //AQUI DEBERIA LLAMAR A ON DRAW    
}
void guardar (char nombre[1024]) {
	FILE* fichero;
	fichero = fopen(nombre, "w+");
    for(int i = 0; i < g_width; i++) {
        for(int j = 0; j < g_height; j++) {
            fprintf(fichero, "%d,", spanningTree[i][j]);       
        }
        fprintf(fichero, "\n");
	}
	fclose(fichero);
	printf("\nProceso completado");
}

void on_btnGenerar_clicked(){
	GtkWidget *lblCol, *lblFil, *spinCol, *spinFil, *caja, *dialog;
	
	dialog = gtk_dialog_new_with_buttons ("Elegir tamaño de la matriz", GTK_WINDOW(g_winPrincipal) , 
										  GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT, 
										  "_Aceptar" , GTK_RESPONSE_ACCEPT, 
										  "_Cancelar", GTK_RESPONSE_REJECT, NULL);
	
	caja = GTK_WIDGET(gtk_dialog_get_content_area(GTK_DIALOG(dialog)));
	lblFil = gtk_label_new("Filas: ");
	spinFil = gtk_spin_button_new_with_range (4	, 2048, 1); //OJO QUITAR EL 4 PARA PRODUCCION
	lblCol = gtk_label_new("Columnas: ");
	spinCol = gtk_spin_button_new_with_range (4, 2048, 1); //OJO QUITAR EL 4 PARA PRODUCCION
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
		gtk_widget_set_sensitive (btnResolver, TRUE);
		gtk_widget_set_sensitive (btnGrabar, TRUE);
	}
	
	gtk_widget_destroy (dialog);
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

void on_btnResolver_clicked(){
	GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(g_winPrincipal), 
												GTK_DIALOG_DESTROY_WITH_PARENT, 
												GTK_MESSAGE_INFO, GTK_BUTTONS_OK, 
												"No implementado");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

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

