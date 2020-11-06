#define EC_WAKE_PIN 13
#define PH_WAKE_PIN 15
#define SENSOR_RISE_TIME 2000

int incoming_msg;
int ec_wake_pin = 13;
int ph_wake_pin = 15;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ec_wake_pin, OUTPUT);
  pinMode(ph_wake_pin, OUTPUT);
  digitalWrite(ec_wake_pin, LOW);
  digitalWrite(ph_wake_pin, LOW);
}

String uart_read()
{
  String buf_msg;
  while (Serial.available() > 0) {
    // read the incoming byte:
    incoming_msg = Serial.read();
    buf_msg = buf_msg + char(incoming_msg);
  }
  return buf_msg;
}

float ec_read()
{
  digitalWrite(ec_wake_pin, HIGH);
  digitalWrite(ph_wake_pin, LOW);
  delay(SENSOR_RISE_TIME);
  String ec_msg = uart_read();
  float ec_value = 0.00;
  int num_try = 0;
  
  while((ec_msg.length() == 0) || (ec_value == 0.00))
  {
    ec_msg = uart_read();
    ec_value = ec_msg.toFloat();
    num_try = num_try + 1;
    delay(100);
  }

//  Serial.println("ec num try=" + String(num_try));
  digitalWrite(ec_wake_pin, LOW);
  digitalWrite(ph_wake_pin, LOW);
  return ec_value;
}

float ph_read()
{
  digitalWrite(ec_wake_pin, LOW);
  digitalWrite(ph_wake_pin, HIGH);
  delay(SENSOR_RISE_TIME);
  String ph_msg = uart_read();
  float ph_value = 0.00;
  int num_try = 0;
  
  while((ph_msg.length() == 0) || (ph_value == 0.00))
  {
    ph_msg = uart_read();
    ph_value = ph_msg.toFloat();
    num_try = num_try + 1;
    delay(200);
  }

//  Serial.println("ph num try=" + String(num_try));
  digitalWrite(ec_wake_pin, LOW);
  digitalWrite(ph_wake_pin, LOW);
  return ph_value;   
}

void loop() {
  float ec = ec_read();
  float ph = ph_read();
  Serial.println("EC: " + String(ec));
  Serial.println("PH: " + String(ph));
  delay(200);
}
