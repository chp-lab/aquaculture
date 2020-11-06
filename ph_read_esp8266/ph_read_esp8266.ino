#include <SoftwareSerial.h>
#define EC_WAKE_PIN D5
#define PH_WAKE_PIN D6
#define SENSOR_RISE_TIME 2000
#define S_RX D2
#define S_TX D3


int ec_wake_pin = EC_WAKE_PIN;
int ph_wake_pin = PH_WAKE_PIN;

SoftwareSerial NodeSerial(S_RX, S_TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NodeSerial.begin(9600);
  
  pinMode(ec_wake_pin, OUTPUT);
  pinMode(ph_wake_pin, OUTPUT);
  digitalWrite(ec_wake_pin, LOW);
  digitalWrite(ph_wake_pin, LOW);
}

//String uart_read()
//{
//  String buf_msg;
//  int incoming_msg;
//  while (Serial.available() > 0) {
//    // read the incoming byte:
//    incoming_msg = Serial.read();
//    buf_msg = buf_msg + char(incoming_msg);
//  }
//  return buf_msg;
//}

String node_serial_read()
{
  String buf_msg;
  int incoming_msg;
  while (NodeSerial.available() > 0)
  {
    incoming_msg = NodeSerial.read();
    buf_msg = buf_msg + char(incoming_msg);
  }
  return buf_msg;
}

float ec_read()
{
  digitalWrite(ec_wake_pin, HIGH);
  digitalWrite(ph_wake_pin, LOW);
  delay(SENSOR_RISE_TIME);
  String ec_msg = node_serial_read();
  float ec_value = 0.00;
  int num_try = 0;
  
  while((ec_msg.length() == 0) || (ec_value == 0.00))
  {
    ec_msg = node_serial_read();
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
  String ph_msg = node_serial_read();
  float ph_value = 0.00;
  int num_try = 0;
  
  while((ph_msg.length() == 0) || (ph_value == 0.00))
  {
    ph_msg = node_serial_read();
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
  String tmp_msg = "{\"ec\":" + String(ec) + ",\"ph\":" + String(ph) + "}";
  Serial.println(tmp_msg);
  delay(200);
}
