#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "user_config.h"

const char* wifissid = wifi_ssid;
const char* wifipassword = wifi_password;
const char* mqttserver = mqtt_server;

WiFiClient espClient;
PubSubClient client(espClient);
char RelayState = '0';

void initWiFi() 
{
    delay(10);
    Serial.println("------WI-FI Connecting------");
    Serial.print("Connection to: ");
    Serial.println(wifissid);
    Serial.println("wait");
    reconectWiFi();
}

void reconnectMQTT() 
{
    while (!client.connected()) 
    {
        Serial.print("Reconnecting: ");
        Serial.println(mqttserver);
        String clientId = MQTT_Client;
        clientId += String(random(0xffff), HEX);
   
        if (client.connect(MQTT_Client, mqtt_username, mqtt_password)) 
        {
            Serial.println("connected!");
            client.subscribe(mqtt_command);
            client.publish(mqtt_lwt, "Online");
        } 
        else 
        {
            Serial.println("Reconnecting");
            Serial.println("Trying again in 2 seconds");
            delay(2000);
        }
    }
}

void reconectWiFi() 
{
    if (WiFi.status() == WL_CONNECTED)
        return;
        
    WiFi.begin(wifissid, wifipassword); 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected ");
    Serial.print(wifissid);
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
    char On[4]   = {0xA0, 0x01, 0x01, 0xA2};
    char Off[4]  = {0xA0, 0x01, 0x00, 0xA1};
    
    for(int i = 0; i < length; i++) 
      {
        char c = (char)payload[i];
        msg += c;
      }
      
    if (msg.equals("L"))
    {
        for(int a = 0; a < 4; a ++)
           {
              Serial.write (On[a]);
              RelayState = '1';
           }
    }
    
    if (msg.equals("D"))
    {
        for(int a = 0; a < 4; a ++)
          {
            Serial.write (Off[a]); 
            RelayState = '0';
          }
    }   
}

void SendStateToMQTT(void)
{
    if (RelayState == '0')
    {
      client.publish(mqtt_state, OFFLINE);
    }
 
    else if (RelayState == '1')
    {
      client.publish(mqtt_state, ONLINE);
    }
}

void checkingWiFiandMQTT(void)
{
    if (!client.connected()) 
        reconnectMQTT(); 
        reconectWiFi(); 
}

void setup() {
  client.setServer(mqttserver, 1883);
  client.setCallback(mqtt_callback);
  WiFi.begin(wifissid, wifipassword);   
  Serial.begin(9600);
  initWiFi();  
}                                                                                                                                                                                                                                                                                                                                   

void loop() 
{
  checkingWiFiandMQTT();
  SendStateToMQTT();
  client.loop();
}
