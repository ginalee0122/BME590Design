#define BUTTON_IN 3
#define LED 10
#define PWM_MAX 255

bool BUTTON_PUSHED = false;
int operating_mode = 0;
int PWM_OUT = 0;

// executed one-time at device startup
void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, FALLING);
}

void check_button_press() {
    if (BUTTON_PUSHED == true) {
      
        operating_mode = operating_mode + 1;
        if (operating_mode == 5) {
            operating_mode = 0;
        }
    }

    BUTTON_PUSHED = false;
}

void set_pwm_based_on_operating_mode() {
  switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
            Serial.println("case 0: off");
            delay(100);
            break;
        case 1:
            PWM_OUT = PWM_MAX;
            Serial.println("case 1: max");
            break;
        case 2:
            PWM_OUT = int(PWM_MAX/3);
            Serial.println("case 2: intermediate");
            break;
        case 3:
            PWM_OUT = int(PWM_MAX/8);
            Serial.println("case 3: dim");
            break;
        case 4:
            flash_the_light();
            Serial.println("case 4: flashing boom boom");
            break;
    }
}

void button_pushed() {
    BUTTON_PUSHED = true;
    Serial.println("button pressed!");
}

void flash_the_light() {
  for (int i=0; i<3; i++) {
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
    delay(300); 
  }
}

void shine_led() {
    analogWrite(LED, PWM_OUT);
}

void loop() {
  check_button_press();
  set_pwm_based_on_operating_mode();
  shine_led();
}
