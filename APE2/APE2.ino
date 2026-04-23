const int LED_PINS[] = {2, 3, 4, 5, 6, 7};
const int BOTON_PIN = 8;
const int TOTAL_LEDS = 6;

int patronActual = 0;
int ultimoEstadoSwitch = LOW;
unsigned long ultimoTiempoCambio = 0;
const unsigned long debounceDelay = 80;

void setup() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  pinMode(BOTON_PIN, INPUT);
  randomSeed(analogRead(A0));
}

void loop() {
  leerSwitch();

  switch (patronActual) {
    case 0:
      patronSecuencia();
      break;
    case 1:
      patronPersecucion();
      break;
    case 2:
      patronParpadeo();
      break;
    case 3:
      patronAleatorio();
      break;
    case 4:
      patronOnda();
      break;
  }
}

void leerSwitch() {
  int estadoActual = digitalRead(BOTON_PIN);

  if (estadoActual != ultimoEstadoSwitch) {
    if (millis() - ultimoTiempoCambio > debounceDelay) {
      patronActual++;
      if (patronActual > 4) {
        patronActual = 0;
      }
      apagarTodos();
      ultimoTiempoCambio = millis();
    }
  }

  ultimoEstadoSwitch = estadoActual;
}

void apagarTodos() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}

void patronSecuencia() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(150);
    digitalWrite(LED_PINS[i], LOW);
  }
}

void patronPersecucion() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    apagarTodos();
    digitalWrite(LED_PINS[i], HIGH);
    delay(120);
  }

  for (int i = TOTAL_LEDS - 2; i > 0; i--) {
    apagarTodos();
    digitalWrite(LED_PINS[i], HIGH);
    delay(120);
  }
}

void patronParpadeo() {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < TOTAL_LEDS; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
    delay(200);

    for (int i = 0; i < TOTAL_LEDS; i++) {
      digitalWrite(LED_PINS[i], LOW);
    }
    delay(200);
  }
}

void patronAleatorio() {
  apagarTodos();
  int led = random(0, TOTAL_LEDS);
  digitalWrite(LED_PINS[led], HIGH);
  delay(200);
  digitalWrite(LED_PINS[led], LOW);
}

void patronOnda() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
  }

  for (int i = 0; i < TOTAL_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
    delay(100);
  }
}