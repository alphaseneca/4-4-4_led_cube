#include <Arduino.h>

// Shift Register Pin Definitions
const int DATA_PIN = D0;  // Serial data input
const int LATCH_PIN = D4; // Storage register clock (RCLK)
const int CLOCK_PIN = D3; // Shift register clock (SRCLK)

// Layer Pin Definitions
const int LAYERS[4] = {D5, D6, D7, D1};

// Animation Timing and Control
const int DEFAULT_DELAY = 150;
const int NUM_LAYERS = 4;
const int NUM_COLUMNS = 16;

// Random Seed Initialization
const int RANDOM_SEED_PIN = A0;

// Animation Function Prototypes
void initializeCube();
void clearCube();
void sendToShiftRegister(uint16_t data);
void setLayer(int layer, bool state);
void setAllLayers(bool state);

// Complex Animation Prototypes
void rainAnimation();
void pulsatingCubeEffect();
void explosionEffect();
void snakeTrailAnimation();
void propeller();
void dataStreamEffect();
void fractalGrowthEffect();
void diagonalRectangle();
void spiralInAndOut();
void colorWaveEffect();
void heartbeatEffect();
void randomLEDChaseEffect();

void setup()
{
  // Initialize Serial Communication
  Serial.begin(115200);

  // Seed Random Number Generator
  randomSeed(analogRead(RANDOM_SEED_PIN));

  // Configure Shift Register Pins
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  // Configure Layer Pins
  for (int i = 0; i < NUM_LAYERS; i++)
  {
    pinMode(LAYERS[i], OUTPUT);
    digitalWrite(LAYERS[i], HIGH); // Ensure layers start OFF
  }

  // Initial Cube Initialization
  initializeCube();
}

void loop()
{
  // Sequence of Advanced Animations
  rainAnimation();
  pulsatingCubeEffect();
  explosionEffect();
  snakeTrailAnimation();
  propeller();
  dataStreamEffect();
  diagonalRectangle();
  spiralInAndOut();
  colorWaveEffect();
  heartbeatEffect();
  randomLEDChaseEffect();
}

// Low-Level Cube Control Functions
void initializeCube()
{
  clearCube();
  delay(500);
}

void clearCube()
{
  sendToShiftRegister(0x0000);
  setAllLayers(false);
}

void sendToShiftRegister(uint16_t data)
{
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, (data >> 8) & 0xFF); // High Byte
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data & 0xFF);        // Low Byte
  digitalWrite(LATCH_PIN, HIGH);
}

void setLayer(int layer, bool state)
{
  if (layer >= 0 && layer < NUM_LAYERS)
  {
    digitalWrite(LAYERS[layer], !state); // Inverted logic for active LOW
  }
}

void setAllLayers(bool state)
{
  for (int i = 0; i < NUM_LAYERS; i++)
  {
    setLayer(i, state);
  }
}

// Advanced Animation: Rain Effect
void rainAnimation()
{
  Serial.println("Starting Rain Animation...");
  clearCube();
  int dropCount = 20;

  for (int i = 0; i < dropCount; i++)
  {
    int layer = random(NUM_LAYERS);
    int column = random(NUM_COLUMNS);

    setLayer(layer, true);
    sendToShiftRegister(1 << column); // Light up one LED in the selected layer
    delay(100);

    setLayer(layer, false);
  }
}

// Advanced Animation: Pulsating Cube
void pulsatingCubeEffect()
{
  Serial.println("Starting Pulsating Cube Effect...");
  for (int intensity = 0; intensity < 3; intensity++)
  {
    uint16_t fullPattern = 0xFFFF; // All LEDs ON

    for (int layer = 0; layer < NUM_LAYERS; layer++)
    {
      setLayer(layer, true);
      sendToShiftRegister(fullPattern);
      delay(100);
      setLayer(layer, false);
    }

    delay(200);
  }
}

// Advanced Animation: Explosion Effect
void explosionEffect()
{
  Serial.println("Starting Explosion Effect...");
  clearCube();

  for (int wave = 0; wave < 3; wave++)
  {
    uint16_t pattern = 0;

    for (int col = 0; col < NUM_COLUMNS; col++)
    {
      if (abs(col - NUM_COLUMNS / 2) < (wave + 1))
      {
        pattern |= (1 << col); // Activate columns based on wave
      }
    }

    for (int layer = 0; layer < NUM_LAYERS; layer++)
    {
      setLayer(layer, true);
      sendToShiftRegister(pattern);
      delay(100);
      setLayer(layer, false);
    }
  }
}

// Advanced Animation: Snake Trail
void snakeTrailAnimation()
{
  Serial.println("Starting Snake Trail Animation...");
  clearCube();
  int snakeLength = 4;
  int layer = random(NUM_LAYERS);
  int currentPos = 0;

  for (int move = 0; move < 20; move++)
  {
    uint16_t pattern = 0;

    // Create snake movement
    for (int i = 0; i < snakeLength; i++)
    {
      pattern |= (1 << ((currentPos + i) % NUM_COLUMNS)); // Activate LEDs in a snake pattern
    }

    setLayer(layer, true);
    sendToShiftRegister(pattern);
    delay(150);
    setLayer(layer, false);

    currentPos = (currentPos + 1) % NUM_COLUMNS; // Move the snake
  }
}
// Animation: Propeller
void propeller()
{
  Serial.println("Starting Propeller Animation...");
  clearCube();
  int x = 90;
  for (int layer = 0; layer < NUM_LAYERS; layer++)
  {
    setLayer(layer, true); // Turn on the current layer
    for (int i = 0; i < NUM_COLUMNS; i++)
    {
      uint16_t pattern = 0;
      pattern |= (1 << i); // Activate one LED in the current layer
      sendToShiftRegister(pattern);
      delay(x);
    }
    setLayer(layer, false); // Turn off the current layer
  }
}

// Advanced Animation: Data Stream
void dataStreamEffect()
{
  Serial.println("Starting Data Stream Effect...");
  for (int layer = 0; layer < NUM_LAYERS; layer++)
  {
    for (int stream = 0; stream < 5; stream++)
    {
      uint16_t pattern = random(0xFFFF); // Random pattern for the layer

      setLayer(layer, true);
      sendToShiftRegister(pattern);
      delay(100);
      setLayer(layer, false);
    }
  }
}

// Advanced Animation: Fractal Growth
void fractalGrowthEffect()
{
  Serial.println("Starting Fractal Growth Effect...");
  clearCube();

  for (int stage = 0; stage < 4; stage++)
  {
    uint16_t pattern = 0;

    for (int col = 0; col < NUM_COLUMNS; col++)
    {
      if (col % (stage + 1) == 0)
      {
        pattern |= (1 << col); // Activate columns based on stage
      }
    }

    for (int layer = 0; layer < NUM_LAYERS; layer++)
    {
      setLayer(layer, true);
      sendToShiftRegister(pattern);
      delay(400); // Increased delay for longer effect
      setLayer(layer, false);
    }
  }
}

// Animation: Diagonal Rectangle
void diagonalRectangle()
{
  Serial.println("Starting Diagonal Rectangle Animation...");
  clearCube();
  int x = 500; // Increased delay for longer effect
  for (int i = 0; i < 2; i++)
  {
    for (int layer = 0; layer < NUM_LAYERS; layer++)
    {
      uint16_t pattern = 0;

      // Create a diagonal pattern
      for (int col = 0; col < NUM_COLUMNS; col++)
      {
        if (col % 4 == layer)
        {                        // Activate every 4th column based on the layer
          pattern |= (1 << col); // Set the corresponding bit for the column
        }
      }

      setLayer(layer, true);        // Turn on the current layer
      sendToShiftRegister(pattern); // Send the pattern to the shift register
      delay(x);                     // Wait for a while to visualize the effect
      setLayer(layer, false);       // Turn off the current layer
    }
  }
}

// Animation: Spiral In and Out
void spiralInAndOut()
{
  Serial.println("Starting Spiral In and Out Animation...");
  clearCube();
  int x = 60; // Delay between each LED activation

  // Spiral in clockwise
  for (int layer = 0; layer < NUM_LAYERS; layer++)
  {
    setLayer(layer, true); // Activate the layer
    for (int i = 0; i < NUM_COLUMNS; i++)
    {
      uint16_t pattern = 0;
      pattern |= (1 << i); // Activate the LEDs in a spiral pattern
      sendToShiftRegister(pattern);
      delay(x);
    }
    setLayer(layer, false); // Turn off the layer
  }

  // Spiral out counter-clockwise
  for (int layer = NUM_LAYERS - 1; layer >= 0; layer--)
  {
    setLayer(layer, true); // Activate the layer
    for (int i = NUM_COLUMNS - 1; i >= 0; i--)
    {
      uint16_t pattern = 0;
      pattern |= (1 << i); // Activate the LEDs in a spiral pattern
      sendToShiftRegister(pattern);
      delay(x);
    }
    setLayer(layer, false); // Turn off the layer
  }
}

// Animation: Color Wave Effect
void colorWaveEffect()
{
  Serial.println("Starting Color Wave Effect...");
  clearCube();
  for (int wave = 0; wave < 4; wave++)
  {
    uint16_t pattern = 0;
    for (int col = 0; col < NUM_COLUMNS; col++)
    {
      if (col % 2 == wave % 2)
      {
        pattern |= (1 << col); // Activate alternating columns
      }
    }
    for (int layer = 0; layer < NUM_LAYERS; layer++)
    {
      setLayer(layer, true);
      sendToShiftRegister(pattern);
      delay(200);
      setLayer(layer, false);
    }
  }
}

// Animation: Heartbeat Effect
void heartbeatEffect()
{
  Serial.println("Starting Heartbeat Effect...");
  clearCube();
  for (int pulse = 0; pulse < 3; pulse++)
  {
    uint16_t pattern = 0xFFFF; // All LEDs ON
    for (int layer = 0; layer < NUM_LAYERS; layer++)
    {
      setLayer(layer, true);
      sendToShiftRegister(pattern);
      delay(300);
      setLayer(layer, false);
    }
    clearCube();
    delay(300);
  }
}

// Animation: Random LED Chase Effect
void randomLEDChaseEffect()
{
  Serial.println("Starting Random LED Chase Effect...");
  clearCube();
  for (int chase = 0; chase < 20; chase++)
  {
    uint16_t pattern = 0;
    int randomColumn = random(NUM_COLUMNS);
    pattern |= (1 << randomColumn);     // Light up a random LED
    setLayer(random(NUM_LAYERS), true); // Random layer
    sendToShiftRegister(pattern);
    delay(100);
    clearCube();
  }
}