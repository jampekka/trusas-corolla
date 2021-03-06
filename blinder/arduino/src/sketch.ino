int control_pin = 12;
boolean control_mode = false;
unsigned long blind_at = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(control_pin, OUTPUT);
	set_unblind();
	Serial.println("pong");
	Serial.flush();

}

void set_blind() {
	digitalWrite(control_pin, LOW);
}

void set_unblind() {
	digitalWrite(control_pin, HIGH);
}

void lift_blinder() {
	if(blind_at != 0) {
		return;
	}

	set_unblind();
	blind_at = millis() + 300;
}

void handle_command(char command) {
	Serial.print("Handling command ");
	Serial.println(command);
	switch(command) {
		case 'b':
			Serial.println("Blind mode");
			Serial.flush();
			control_mode = false;
			blind_at = 0;
			set_blind();
			break;
		case 'u':
			Serial.println("Unblind mode");
			Serial.flush();
			control_mode = false;
			blind_at = 0;
			set_unblind();
			break;
		case 'c':
			Serial.println("Control mode");
			Serial.flush();
			control_mode = true;
			blind_at = 0;
			set_blind();
			break;
		case 'l':
			if(control_mode) {
				Serial.println("Lifting");
				Serial.flush();
				lift_blinder();
			}
			break;

		case 'p':
			Serial.println("pong");
			Serial.flush();
			break;

	}
	Serial.flush();

}

void serialEvent() {
	while(Serial.available()) {
		handle_command(Serial.read());
	}
}

unsigned long last_pong = 0;

void loop()
{
	unsigned long time = millis();
	if(control_mode && blind_at > 0) {
		if(time > blind_at) {
			blind_at = 0;
			set_blind();
		}
	}
	
	if(time - last_pong > 5000) {
		Serial.println("pong");
		Serial.print("control_mode: ");
		Serial.print(control_mode);
		Serial.print(" blind_at: ");
		Serial.print(blind_at);
		Serial.print(" time: ");
		Serial.println(time);
		Serial.flush();
		last_pong = time;
	}
}
