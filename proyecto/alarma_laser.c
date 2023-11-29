 /*
 * Proyecto
 * Curso: Laboratorio de Microcontroladores
 * Nombre: Carlos A. Caravaca Mora; B61512
 * Ciclo: II
 * Ano: 2023
 * Descripcion: Alarma con modulo laser
*/

// variables para los pines de cada componente
int buzzer = 6;   //D6
int laser = 2;    //D2
int fotoresistencia = A6;   //A6
int estado_fotore = 2;
int estado;

void setup(){
  // se inicializan como entrada o salidad
  pinMode(buzzer, OUTPUT);
  pinMode(laser, OUTPUT);
  pinMode(fotoresistencia, INPUT);
  Serial.begin(9600); // Inicia la comunicación serial
}
void loop(){
  // lectura de la fotoresistencia
  estado_fotore = analogRead(fotoresistencia);
  Serial.println("Lectura de fotoresistencia: " + String(estado_fotore));
  digitalWrite(laser,HIGH);

  if (estado_fotore > 400){
    // interrupcion de laser
    estado = 1;
  }else{
    // no interrupcion de laser
    estado = 2;
  }
  switch (estado) {
    case 1:{
      unsigned char i;
      int x = 1;
      while(x < 10)
      {
        //salida de frecuencia uno
        for(i=0;i<80;i++)
        {
          digitalWrite(buzzer,HIGH);
          delay(1);//wait for 1ms
          digitalWrite(buzzer,LOW);
          delay(1);//wait for 1ms
        }
        //salida de frecuencia dos
        for(i=0;i<100;i++)
        {
          digitalWrite(buzzer,HIGH);
          delay(2);//wait for 2ms
          digitalWrite(buzzer,LOW);
          delay(2);//wait for 2ms
        }
        x++;
      } 
    }
        break;
    case 2:
        // no hace nada, se sale y continua el bucle
        break;
    default:
        break;
  }
}
