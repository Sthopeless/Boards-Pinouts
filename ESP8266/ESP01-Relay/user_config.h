/************************* WIFI CONFIGURATION **********************************/
#define wifi_ssid "ssid"
#define wifi_password "password"
/************************* MQTT BROKER CONFIGURATION ***************************/
#define MQTT_Client "ESP01-Relay"
#define mqtt_server "mqtt.broker.ip"
#define mqtt_username "username"
#define mqtt_password "password"
#define mqtt_port 1883
/************************* MQTT TOPICS CONFIGURATION ***************************/
#define mqtt_command "/"  MQTT_Client "/command/"
#define mqtt_state "/"  MQTT_Client "/state/"
#define mqtt_lwt "/" MQTT_Client "/LWT/"

#define ONLINE "ON"
#define OFFLINE "OFF"
