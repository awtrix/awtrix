#include <Settings.h>
#include "FS.h"
#include "config.h"
#include <DisplayManager.h>

void AwtrixSettings::loadSPIFFS() {
    loadSettings();
    loadConfig();
}

void AwtrixSettings::loadSettings() {
     if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
    }

    File setFile = SPIFFS.open(settingsFile, "r");
    if (!setFile) {
        Serial.println("Settings file not found!");
    }

    size_t size = setFile.size();
    Serial.println(size);
    if (size > 2048) {
        Serial.println("Settings file size is too large");
    }
    Serial.println("Settings file loaded");
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    setFile.readBytes(buf.get(), size);
    setFile.close();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        Serial.println("Failed to parse settings file");
        ESP.restart();
        delay(1000);
    }

    SETTINGS_FOUND=1;

    SHOW_IP_ON_BOOT= json["SHOW_IP_ON_BOOT"];
    AUTO_BRIGHTNESS = json["AUTO_BRIGHTNESS"];
    BRIGHTNESS = json["BRIGHTNESS"];
    UTC_OFFSET = json["UTC_OFFSET"];
    BIG_TIME = json["BIG_TIME"];
    PET_MOOD = json["PET_MOOD"];
    TEXT_COLOR_R = json["TEXT_COLOR_R"];
    TEXT_COLOR_G = json["TEXT_COLOR_G"];
    TEXT_COLOR_B = json["TEXT_COLOR_B"];
    SCROLL_SPEED = json["SCROLL_SPEED"];
    AUTO_UPDATE = json["AUTO_UPDATE"];
    SOUND = json["SOUND"];

    TIME_ACTIVE = json["TIME_ACTIVE"];
    WEATHER_ACTIVE = json["WEATHER_ACTIVE"];
    GOL_ACTIVE = json["GOL_ACTIVE"];
    PET_ACTIVE = json["PET_ACTIVE"];
    FB_ACTIVE = json["FB_ACTIVE"];
    YT_ACTIVE = json["YT_ACTIVE"];
    DHT_ACTIVE = json["DHT_ACTIVE"];
    APP_DURATION = json["APP_DURATION"];
}




void AwtrixSettings::loadConfig() {
     if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
    }

    File confFile = SPIFFS.open(configFile, "r");
    if (!confFile) {
        Serial.println("Config File not found!");
       
    }

    size_t size = confFile.size();
    Serial.println(size);
    if (size > 2048) {
        Serial.println("Config file size is too large");
    }
    Serial.println("Config file loaded");
    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    confFile.readBytes(buf.get(), size);
    confFile.close();
    DynamicJsonBuffer jsonBuffer(bufferSize);
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        Serial.println("Failed to parse config file");
        ESP.restart();
        delay(1000);
    }



if (json.containsKey("WUNDERGROUND_API_KEY")){
    WUNDERGROUND_API_KEY = (char*)malloc(json["WUNDERGROUND_API_KEY"].measureLength()+1);
    WUNDERGROUND_API_KEY[0] = '\0';
    strcpy(WUNDERGROUND_API_KEY, (const char*)json["WUNDERGROUND_API_KEY"]);
}else{
    WEATHER_ACTIVE=0;
}

if (json.containsKey("WUNDERGROUND_LANGUAGE")){
    WUNDERGROUND_LANGUAGE = (char*)malloc(json["WUNDERGROUND_LANGUAGE"].measureLength()+1);
    WUNDERGROUND_LANGUAGE[0] = '\0';
    strcpy(WUNDERGROUND_LANGUAGE, (const char*)json["WUNDERGROUND_LANGUAGE"]);
}else{
    WEATHER_ACTIVE=0;
}

if (json.containsKey("WUNDERGROUND_ZMW_CODE")){
    WUNDERGROUND_ZMW_CODE = (char*)malloc(json["WUNDERGROUND_ZMW_CODE"].measureLength()+1);
    WUNDERGROUND_ZMW_CODE[0] = '\0';
    strcpy(WUNDERGROUND_ZMW_CODE, (const char*)json["WUNDERGROUND_ZMW_CODE"]);
}else{
    WEATHER_ACTIVE=0;
}

if (json.containsKey("YT_API_KEY")){
    YT_API_KEY = (char*)malloc(json["YT_API_KEY"].measureLength()+1);
    YT_API_KEY[0] = '\0';
    strcpy(YT_API_KEY, (const char*)json["YT_API_KEY"]);
}else{
    YT_ACTIVE=0;
}

if (json.containsKey("YT_CHANNEL_ID")){
    YT_CHANNEL_ID = (char*)malloc(json["YT_CHANNEL_ID"].measureLength()+1);
    YT_CHANNEL_ID[0] = '\0';
    strcpy(YT_CHANNEL_ID, (const char*)json["YT_CHANNEL_ID"]);
}else{
    YT_ACTIVE=0;
}

if (json.containsKey("FB_API_URL")){
    FB_API_URL = (char*)malloc(json["FB_API_URL"].measureLength()+1);
    FB_API_URL[0] = '\0';
    strcpy(FB_API_URL, (const char*)json["FB_API_URL"]);
}else{
    FB_ACTIVE=0;
}

if (json.containsKey("FINGERPRINT")){
    FINGERPRINT = (char*)malloc(json["FINGERPRINT"].measureLength()+1);
    FINGERPRINT[0] = '\0';
    strcpy(FINGERPRINT, (const char*)json["FINGERPRINT"]);
}else{
    FB_ACTIVE=0;
}

if (json.containsKey("MQTT_SERVER")){
    MQTT_SERVER = (char*)malloc(json["MQTT_SERVER"].measureLength()+1);
    MQTT_SERVER[0] = '\0';
    strcpy(MQTT_SERVER, (const char*)json["MQTT_SERVER"]);
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("MQTT_USERNAME")){
    MQTT_USERNAME = (char*)malloc(json["MQTT_USERNAME"].measureLength()+1);
    MQTT_USERNAME[0] = '\0';
    strcpy(MQTT_USERNAME, (const char*)json["MQTT_USERNAME"]);
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("MQTT_PASSWORD")){
    MQTT_PASSWORD = (char*)malloc(json["MQTT_PASSWORD"].measureLength()+1);
    MQTT_PASSWORD[0] = '\0';
    strcpy(MQTT_PASSWORD, (const char*)json["MQTT_PASSWORD"]);
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("MQTT_PORT")){
    MQTT_PORT = json["MQTT_PORT"];
}else{
    MQTT_ACTIVE=0;
}

if (json.containsKey("BLYNK_KEY")){
    BLYNK_KEY = (char*)malloc(json["BLYNK_KEY"].measureLength()+1);
    BLYNK_KEY[0] = '\0';
    strcpy(BLYNK_KEY, (const char*)json["BLYNK_KEY"]);
}else{
    BLYNK_ACTIVE=0;
}

}


const char AwtrixSettings::getSetting(String key){
    
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject& json = jsonBuffer.parseObject("");

    return json[key];
}

bool AwtrixSettings::saveSettings() {
     StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["SHOW_IP_ON_BOOT"] = SHOW_IP_ON_BOOT;
    json["AUTO_BRIGHTNESS"] = AUTO_BRIGHTNESS;
    json["BRIGHTNESS"] = BRIGHTNESS;
    json["UTC_OFFSET"] = UTC_OFFSET;
    json["BIG_TIME"] = BIG_TIME;
    json["PET_MOOD"] = PET_MOOD;
    json["TEXT_COLOR_R"] = TEXT_COLOR_R ;
    json["TEXT_COLOR_G"] = TEXT_COLOR_G ;
    json["TEXT_COLOR_B"] = TEXT_COLOR_B;
    json["SCROLL_SPEED"] = SCROLL_SPEED ;
    json["AUTO_UPDATE"] = AUTO_UPDATE ;
    json["SOUND"] = SOUND;
    json["TIME_ACTIVE"] = TIME_ACTIVE;
    json["WEATHER_ACTIVE"] = WEATHER_ACTIVE;
    json["GOL_ACTIVE"] = GOL_ACTIVE;
    json["PET_ACTIVE"] = PET_ACTIVE;
    json["FB_ACTIVE"] = FB_ACTIVE;
    json["YT_ACTIVE"] = YT_ACTIVE;
    json["DHT_ACTIVE"] = DHT_ACTIVE;
    json["MQTT_ACTIVE"] = MQTT_ACTIVE;
    json["BLYNK_ACTIVE"] = BLYNK_ACTIVE;
    json["APP_DURATION"] = APP_DURATION;


    File setFile = SPIFFS.open(settingsFile, "w");
    if (!setFile) {

        Serial.println("Failed to open Settings file for writing");
        return false;
    }

    json.printTo(setFile);
    setFile.close();
    Serial.println("Settings file saved");


    delay(500);
    return true;
}


void AwtrixSettings::parseSettings(String json) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
    }

    if (root.containsKey("BRIGHTNESS")) BRIGHTNESS = root["BRIGHTNESS"];
    if (root.containsKey("SHOW_IP_ON_BOOT")) SHOW_IP_ON_BOOT = root["SHOW_IP_ON_BOOT"];
    if (root.containsKey("AUTO_BRIGHTNESS")) AUTO_BRIGHTNESS = root["AUTO_BRIGHTNESS"];
    if (root.containsKey("UTC_OFFSET")) UTC_OFFSET = root["UTC_OFFSET"];
    if (root.containsKey("BIG_TIME"))    BIG_TIME = root["BIG_TIME"];
    if (root.containsKey("PET_MOOD"))  PET_MOOD = root["PET_MOOD"];
    if (root.containsKey("AUTO_UPDATE"))  AUTO_UPDATE = root["AUTO_UPDATE"];
    if (root.containsKey("TEXT_COLOR_R")) TEXT_COLOR_R = root["TEXT_COLOR_R"];
    if (root.containsKey("TEXT_COLOR_G")) TEXT_COLOR_G = root["TEXT_COLOR_G"];
    if (root.containsKey("TEXT_COLOR_B")) TEXT_COLOR_B = root["TEXT_COLOR_B"];
    if (root.containsKey("SCROLL_SPEED")) SCROLL_SPEED = root["SCROLL_SPEED"];
    saveSettings();
}
