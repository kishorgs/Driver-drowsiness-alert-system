#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Your_Blynk_template_ID"
#define BLYNK_TEMPLATE_NAME "Your_Blynk_template_Name"
#define BLYNK_AUTH_TOKEN "Your_Blynk_auth_token"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define RELAY_PIN 5

#define SENSE A0

#define BUZZER_PIN 12

char ssid[] = "Your wifi name";
char pass[] = "Your wifi password";

BlynkTimer timer;

bool relayActivated = false;

void setup()
{
    Serial.begin(9600);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(SENSE, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    timer.setInterval(1000L, checkBlynk);
}

void checkBlynk()
{
}

BLYNK_WRITE(V0)
{
    int relayState = param.asInt();

    if (relayState == 1)
    {
        digitalWrite(RELAY_PIN, LOW);
        relayActivated = true;
    }
    else
    {
        digitalWrite(RELAY_PIN, HIGH);
        relayActivated = false;
    }
}

void loop()
{
    Blynk.run();
    timer.run();

    if (relayActivated)
    {
        int sensorValue = analogRead(SENSE);
        Serial.println(sensorValue);

        if (sensorValue <= 50)
        {
            digitalWrite(RELAY_PIN, LOW);
            digitalWrite(BUZZER_PIN, LOW);
        }
        else
        {
            digitalWrite(RELAY_PIN, HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
        }
    }
}
