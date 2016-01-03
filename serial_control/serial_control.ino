#define EDGE_LENGTH 4
#define PLANE_AREA EDGE_LENGTH * EDGE_LENGTH
#define PLANE_TIME 2000 // time each plane is displayed in microseconds

int LEDPin[] = {12, 13, A5, A4, 11, 10, 9, 8, 4, 5, 6, 7, 3, 2, 1, 0};
int PlanePin[] = {A0, A1, A2, A3};

int ReadIdx;
byte Pattern[PLANE_AREA];

void setup() {
  // set up LED pins as output
  for (int pin = 0; pin < PLANE_AREA; pin++) {
    pinMode( LEDPin[pin], OUTPUT );
  }
  // set up plane pins as outputs
  for (int pin = 0; pin < EDGE_LENGTH; pin++) {
    pinMode( PlanePin[pin], OUTPUT );
  }
  // set all plane pins to HIGH
  for (int pin = 0; pin < EDGE_LENGTH; pin++) {
    digitalWrite( PlanePin[pin], HIGH );
  }

  for (int i = 0; i < PLANE_AREA; i++) {
    Pattern[i] = 0;
  }

  ReadIdx = 0;

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    Pattern[ReadIdx] = Serial.read();
    ReadIdx++;
    if (ReadIdx >= PLANE_AREA) {
      ReadIdx = 0;
    }
  }

  int patidx = 0;
  for (int plane = 0; plane < EDGE_LENGTH; plane++) {
    // load current plane pattern data into ports
    int ledpin = 0;
    for (int ledrow = 0; ledrow < EDGE_LENGTH; ledrow++) {
      for (int ledcol = 0; ledcol < EDGE_LENGTH; ledcol++) {
        digitalWrite( LEDPin[ledpin], Pattern[patidx] & (1 << ledcol) );
        ledpin++;
      }
      patidx++;
    }
    digitalWrite( PlanePin[plane], LOW );
    delayMicroseconds( PLANE_TIME );
    digitalWrite( PlanePin[plane], HIGH );
  }
}
