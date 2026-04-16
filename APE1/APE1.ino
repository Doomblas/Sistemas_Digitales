const int LED_PIN = 13;

byte estadoLed = 0;
byte contador = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("Operaciones Bitwise");

  byte a = 5;
  byte b = 3;

  Serial.print("AND: "); Serial.println(a & b, BIN);
  Serial.print("OR : "); Serial.println(a | b, BIN);
  Serial.print("XOR: "); Serial.println(a ^ b, BIN);
  Serial.print("NOT: "); Serial.println((byte)(~a), BIN);
  Serial.print("SHL: "); Serial.println(a << 1, BIN);
  Serial.print("SHR: "); Serial.println(a >> 1, BIN);

  // Inicialización
  estadoLed = estadoLed | (1 << 0);
}

void loop() {

  // XOR → alternar LED
  estadoLed = estadoLed ^ 0b00000001;

  if ((estadoLed & 1) == 1) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);

  // Contador
  contador = (contador + 1) % 8;

  // Shift dinámico
  Serial.println(1 << contador, BIN);

  delay(500);
}