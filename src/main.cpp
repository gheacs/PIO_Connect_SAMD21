#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUZZER_PIN 10      // Define the buzzer pin
#define TEMP_THRESHOLD 30.0 // Temperature threshold in degrees Celsius

Adafruit_BME280 bme; // I2C
Adafruit_MPU6050 mpu;

float temperature_old = 0.0; // Variable to store the previous temperature reading

void setup() {
    Serial.begin(9600);
    pinMode(BUZZER_PIN, OUTPUT);

    if (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1);
    }

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.display();
    delay(2000);
    display.clearDisplay();

    // Initial read of temperature to set the starting point for the filter
    temperature_old = bme.readTemperature();
}

void loop() {
    float temperature_new = bme.readTemperature(); // Read new temperature
    // Apply the filter
    float temperature = 0.2 * temperature_new + 0.8 * temperature_old;
    temperature_old = temperature; // Update the old temperature value

    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Adjust accelerometer readings by applying the average offsets
    float accelX = a.acceleration.x + 1.857; // Adjust by adding the average offset
    float accelY = a.acceleration.y + 1.520; // Adjust by adding the average offset
    float accelZ = a.acceleration.z - 8.877; // Adjust by subtracting the average offset

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.println("BME280 Data:");
    display.print("Temp: ");
    display.print(temperature);
    display.println(" C");
    display.print("Humidity: ");
    display.print(humidity);
    display.println(" %");
    display.print("Pressure: ");
    display.print(pressure);
    display.println(" hPa");

    display.println("MPU6050 Data:");
    display.print("Accel X: ");
    display.print(accelX);
    display.println(" m/s^2");
    display.print("Accel Y: ");
    display.print(accelY);
    display.println(" m/s^2");
    display.print("Accel Z: ");
    display.print(accelZ);
    display.println(" m/s^2");
    display.display();

    if (temperature > TEMP_THRESHOLD) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }

    Serial.print("Time: ");
    Serial.print(millis());
    Serial.print(", Temp: ");
    Serial.print(temperature);
    Serial.print(", Humidity: ");
    Serial.print(humidity);
    Serial.print(", Pressure: ");
    Serial.print(pressure);
    Serial.print(", AccelX: ");
    Serial.print(accelX);
    Serial.print(", AccelY: ");
    Serial.print(accelY);
    Serial.print(", AccelZ: ");
    Serial.println(accelZ);

    delay(2000); // Update every 2 seconds
}
