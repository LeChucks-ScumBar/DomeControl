// pin definitions
#define ENCODER1 2      // Encoder A
#define ENCODER2 3      // Encoder B
#define HOME_SENSOR 12

int encoderPinA = ENCODER1;
int encoderPinB = ENCODER2;
uint16_t encoderPos0 = 0;
unsigned long encoderPos1 = 0;
double encoderPos2 = 0;

uint16_t encoderPos00 = 10000;
unsigned long encoderPos11 = 10000;
double encoderPos22 = 10000;
int encoderPinALast = LOW;
int encoderPinANow = LOW;

char buf[100];

bool state = false;

void setup() {
  pinMode (encoderPinA, INPUT_PULLUP);
  pinMode (encoderPinB, INPUT_PULLUP);
   pinMode (HOME_SENSOR, INPUT_PULLUP);
  Serial.begin (115200);
}

void loop() {
  encoderPinANow = digitalRead(encoderPinA);
  if ((encoderPinALast == HIGH) && (encoderPinANow == LOW)) {
    if (digitalRead(encoderPinB) == HIGH) {
      encoderPos0++;
      encoderPos1++;
      encoderPos2 +=1;
    } else {
      encoderPos0--;
      encoderPos1--;
      encoderPos2+=1;
    }
    sprintf(buf, "Pos_u16: %d\tPos_U32: %d\tPos_float: %f.0", encoderPos0, encoderPos1,encoderPos2);
    Serial.println(buf);
    //Serial.println(encoderPos);
  }
  encoderPinALast = encoderPinANow;

      // store detected home position
    if (!digitalRead(HOME_SENSOR)) {
        if (state == true) {
 
 encoderPos00 = encoderPos0;
 encoderPos11 = encoderPos1;
encoderPos22 = encoderPos2;
            encoderPos0 = 0;
            encoderPos1 = 0;
            encoderPos2 = 0;
            state = false;
            Serial.println("home");
    sprintf(buf, "maxPos_u16: %d\tmaxPos_U32: %d\tmaxPos_float: %f.0", encoderPos00, encoderPos11,encoderPos22);
    Serial.println(buf);

        }
    }else if (digitalRead(HOME_SENSOR)) 
    {
      state = true;
    }

    
}