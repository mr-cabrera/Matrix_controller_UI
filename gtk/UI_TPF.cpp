#include<gtk/gtk.h>
#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdint.h>
#include "rs232.h"

int pasos = 50; // Var Global con la cantodad de pasos que se realizan con cada pulsacion
using namespace std;

typedef struct Motores {   //Definimos de la estructura para guardar los datos de los sensores
	int fila_0;
	int fila_1;
	int fila_2;
	int fila_3;
	int fila_4;
	int fila_5;
	int fila_6;
	int fila_7;
}Motores;

union UDato {  //Definimos una union para poder mandar los datos byte a byte
  Motores datos;
  unsigned char  a[sizeof(Motores)];
} Datos;







int cport_nr=24,       // ttyACM0
bdrate=9600;       //9600 baud   
char mode[]={'8', 'N', '1', 0};

void chequeo_port(){
	
	if(RS232_OpenComport(cport_nr, bdrate, mode, 0)) {
    	cout<<"Erro no se puede abrir el puerto\n";
	}
}

void enviar_letra(char letra){
	
	RS232_SendByte(cport_nr, letra);	
}


void Enviar_Struct(){
	int cantidadBytes= RS232_SendBuf(cport_nr, Datos.a, sizeof(Motores));  //Leemos la cantidad de bytes enviados
	cout<<"Los bytes enviados fueron:"<<cantidadBytes<<endl;	// Imprimimos la cantidad de bytes recibidos para saber si es que se recibieron o no

}




int button_data[8][8];


void button_clicked(GtkWidget *button, gpointer data)
{

  int row = GPOINTER_TO_INT(data) / 8;
  int col = GPOINTER_TO_INT(data) % 8;


  button_data[row][col] ^= 1;

 Datos.datos.fila_0 = button_data[0][0]*128 + button_data[0][1]*64 + button_data[0][2]*32 + button_data[0][3]*16 + button_data[0][4]*8 + button_data[0][5]*4 + button_data[0][6]*2 + button_data[0][7]*1; 
 Datos.datos.fila_1 = button_data[1][0]*128 + button_data[1][1]*64 + button_data[1][2]*32 + button_data[1][3]*16 + button_data[1][4]*8 + button_data[1][5]*4 + button_data[1][6]*2 + button_data[1][7]*1; 
 Datos.datos.fila_2 = button_data[2][0]*128 + button_data[2][1]*64 + button_data[2][2]*32 + button_data[2][3]*16 + button_data[2][4]*8 + button_data[2][5]*4 + button_data[2][6]*2 + button_data[2][7]*1; 
 Datos.datos.fila_3 = button_data[3][0]*128 + button_data[3][1]*64 + button_data[3][2]*32 + button_data[3][3]*16 + button_data[3][4]*8 + button_data[3][5]*4 + button_data[3][6]*2 + button_data[3][7]*1; 
 Datos.datos.fila_4 = button_data[4][0]*128 + button_data[4][1]*64 + button_data[4][2]*32 + button_data[4][3]*16 + button_data[4][4]*8 + button_data[4][5]*4 + button_data[4][6]*2 + button_data[4][7]*1; 
 Datos.datos.fila_5 = button_data[5][0]*128 + button_data[5][1]*64 + button_data[5][2]*32 + button_data[5][3]*16 + button_data[5][4]*8 + button_data[5][5]*4 + button_data[5][6]*2 + button_data[5][7]*1; 
 Datos.datos.fila_6 = button_data[6][0]*128 + button_data[6][1]*64 + button_data[6][2]*32 + button_data[6][3]*16 + button_data[6][4]*8 + button_data[6][5]*4 + button_data[6][6]*2 + button_data[6][7]*1; 
 Datos.datos.fila_7 = button_data[7][0]*128 + button_data[7][1]*64 + button_data[7][2]*32 + button_data[7][3]*16 + button_data[7][4]*8 + button_data[7][5]*4 + button_data[7][6]*2 + button_data[7][7]*1; 
  




std::cout<<sizeof(Motores)<<std::endl;
	
 std::cout<<Datos.datos.fila_0<<std::endl;
 std::cout<<Datos.datos.fila_1<<std::endl;
 std::cout<<Datos.datos.fila_2<<std::endl;
 std::cout<<Datos.datos.fila_3<<std::endl;
 std::cout<<Datos.datos.fila_4<<std::endl;
 std::cout<<Datos.datos.fila_5<<std::endl;
 std::cout<<Datos.datos.fila_6<<std::endl;
 std::cout<<Datos.datos.fila_7<<std::endl;


  
  enviar_letra('a');
  usleep(200000); 
  Enviar_Struct();

}

int main(int argc, char *argv[])
{
  chequeo_port(); // Chequea la conecion con el puerto, en esta caso con el Arduino 

  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Matriz de botones");
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  int button_index = 0;
  for (int i = 0; i < 8; i++)
  {
    GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    for (int j = 0; j < 8; j++)
    {
      GtkWidget *button = gtk_toggle_button_new();
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
      gtk_button_set_label(GTK_BUTTON(button), "...");
      g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(button_index));
      gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);

      button_index++;
    }
  }

  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
