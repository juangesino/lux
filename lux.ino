// Define pin variables.
int relay = D0;
// Add a physical button
int button = D2;
// Add a status light
int led = D7;

// This stores the current state of the light.
bool light = false;

void setup()
{
  // Setup pin modes.
  pinMode(relay, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  // Define a function to toggle the relay.
  Particle.function("relay", relayToggle);
  // Start with lights off.
  digitalWrite(relay, HIGH);
  digitalWrite(led, LOW);
  // Add a cloud variable to get the current status.
  Particle.variable("lightState", light);
}

// Define the loop function.
void loop() {
  // Add the button logic.
  int buttonState;
  buttonState = digitalRead(button);
  if(buttonState == LOW && light) {
    lightsOff();
  } else if (buttonState == LOW && !light) {
    lightsOn();
  }
  delay(250);
}

// Cloud exposed function to operate the relay.
// A command variable can be passed.
// If no variable is given, the function will toggle.
// If the command is 'on' or 'off' it will turn on/off accordingly
int relayToggle(String command) {
  if (command == "on") {
    lightsOn();
    return 1;
  } else if (command == "off") {
    lightsOff();
    return 0;
  } else {
    if(light) {
      lightsOff();
      return 0;
    } else {
      lightsOn();
      return 1;
    }
  }
}

// Function to turn the lights off.
void lightsOff() {
  digitalWrite(relay, HIGH);
  digitalWrite(led, LOW);
  light = false;
}

// Function to turn the lights on.
void lightsOn() {
  digitalWrite(relay, LOW);
  digitalWrite(led, HIGH);
  light = true;
}

// This function returns the current state.
bool getLightState() {
  return light;
}
