// ==========================
// ENTRADAS DE SEÑAL
// ==========================
const int entrada555 = 2;
const int entradaFF  = 3;

// ==========================
// CANAL 1 : NE555
// ==========================
int lectura555 = LOW;
int lecturaAnterior555 = LOW;

unsigned long marcaFlanco555 = 0;
unsigned long periodo555 = 0;

unsigned long marcaCambio555 = 0;
unsigned long tiempoAlto555 = 0;
unsigned long tiempoBajo555 = 0;

// ==========================
// CANAL 2 : FLIP-FLOP
// ==========================
int lecturaFF = LOW;
int lecturaAnteriorFF = LOW;

unsigned long marcaFlancoFF = 0;
unsigned long periodoFF = 0;

unsigned long marcaCambioFF = 0;
unsigned long tiempoAltoFF = 0;
unsigned long tiempoBajoFF = 0;

// ==========================
// CONTROL DE REPORTE
// ==========================
unsigned long tiempoReporte = 0;

void setup() {
  pinMode(entrada555, INPUT);
  pinMode(entradaFF, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long ahora = millis();

  // ==========================
  // LECTURA CANAL 555
  // ==========================
  lectura555 = digitalRead(entrada555);

  if (lectura555 == HIGH && lecturaAnterior555 == LOW) {
    periodo555 = ahora - marcaFlanco555;
    marcaFlanco555 = ahora;
  }

  if (lectura555 != lecturaAnterior555) {
    if (lectura555 == HIGH) {
      tiempoBajo555 = ahora - marcaCambio555;
    } else {
      tiempoAlto555 = ahora - marcaCambio555;
    }
    marcaCambio555 = ahora;
  }

  lecturaAnterior555 = lectura555;

  // ==========================
  // LECTURA CANAL FLIP-FLOP
  // ==========================
  lecturaFF = digitalRead(entradaFF);

  if (lecturaFF == HIGH && lecturaAnteriorFF == LOW) {
    periodoFF = ahora - marcaFlancoFF;
    marcaFlancoFF = ahora;
  }

  if (lecturaFF != lecturaAnteriorFF) {
    if (lecturaFF == HIGH) {
      tiempoBajoFF = ahora - marcaCambioFF;
    } else {
      tiempoAltoFF = ahora - marcaCambioFF;
    }
    marcaCambioFF = ahora;
  }

  lecturaAnteriorFF = lecturaFF;

  // ==========================
  // CÁLCULOS
  // ==========================
  float frecuencia555 = 0;
  float duty555 = 0;
  float frecuenciaFF = 0;
  float dutyFF = 0;

  if (periodo555 > 0) {
    frecuencia555 = 1000.0 / periodo555;
  }

  if ((tiempoAlto555 + tiempoBajo555) > 0) {
    duty555 = (float)tiempoAlto555 / (tiempoAlto555 + tiempoBajo555) * 100.0;
  }

  if (periodoFF > 0) {
    frecuenciaFF = 1000.0 / periodoFF;
  }

  if ((tiempoAltoFF + tiempoBajoFF) > 0) {
    dutyFF = (float)tiempoAltoFF / (tiempoAltoFF + tiempoBajoFF) * 100.0;
  }

  // ==========================
  // REPORTE CADA 1 SEGUNDO
  // ==========================
  if (ahora - tiempoReporte >= 1000) {
    tiempoReporte = ahora;

    Serial.println("===== MEDICION DE SENALES =====");

    Serial.println("Canal 1 - 555");
    Serial.print("Periodo: ");
    Serial.print(periodo555);
    Serial.println(" ms");

    Serial.print("Frecuencia: ");
    Serial.print(frecuencia555);
    Serial.println(" Hz");

    Serial.print("Duty cycle: ");
    Serial.print(duty555);
    Serial.println(" %");

    Serial.println();

    Serial.println("Canal 2 - Flip-Flop");
    Serial.print("Periodo: ");
    Serial.print(periodoFF);
    Serial.println(" ms");

    Serial.print("Frecuencia: ");
    Serial.print(frecuenciaFF);
    Serial.println(" Hz");

    Serial.print("Duty cycle: ");
    Serial.print(dutyFF);
    Serial.println(" %");

    Serial.println("-----------------------------");
    Serial.println();
  }

  // ==========================
  // SERIAL PLOTTER
  // ==========================
  Serial.print(lectura555);
  Serial.print(",");
  Serial.println(lecturaFF);
}