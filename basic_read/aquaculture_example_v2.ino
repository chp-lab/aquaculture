
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String uart_read()
{
  String buf_msg;
  int incoming_msg;
  while (Serial.available() > 0) {
    // read the incoming byte:
    incoming_msg = Serial.read();
    buf_msg = buf_msg + char(incoming_msg);
  }
  return buf_msg;
}

void loop() {
  // put your main code here, to run repeatedly:
  String tmp_msg = uart_read();
  Serial.println(tmp_msg);
  delay(100);
}
