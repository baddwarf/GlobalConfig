#include "Arduino.h"
#include <ArduinoJson.h>
//#include <FS.h> //--> deprecated
#include "LittleFS.h"
#include "globalconfig.h"

GlobalConfig::GlobalConfig() : _doc(256)
{

}

uint8_t GlobalConfig::loadConfigFromJSON()
{
    File cfgFile = LittleFS.open("/config.json", "r");
    if (!cfgFile)
    {
        Serial.println("[CONFIG] Unable to open config file");
        _status = GC_ERRNO_FILEREADFAILED;
        return(_status);
    }
    size_t size = cfgFile.size();
    Serial.print("[CONFIG] File size: ");
    Serial.println(size);
    DeserializationError error = deserializeJson(_doc, cfgFile);
    cfgFile.close();
    if (error)
    {
        Serial.println("[CONFIG] Unable to read config file");
        _status = GC_ERRNO_FILEREADFAILED;
        return(_status);
    }
    _status = GC_SUCCESS;
    return(GC_SUCCESS);
}

uint8_t GlobalConfig::loadConfigFromJSON(char* fileName)
{
    File cfgFile = LittleFS.open(fileName, "r");
    if (!cfgFile)
    {
        Serial.println("[CONFIG] Unable to open config file");
        _status = GC_ERRNO_FILEOPENFAILED;
        return(_status);
    }
    size_t size = cfgFile.size();
    Serial.print("[CONFIG] File size: ");
    Serial.println(size);
    DeserializationError error = deserializeJson(_doc, cfgFile);
    cfgFile.close();
    if (error)
    {
        Serial.println("[CONFIG] Unable to read config file");
        _status = GC_ERRNO_FILEREADFAILED;
        return(_status);
    }
    _status = GC_SUCCESS;
    return(GC_SUCCESS);
}

String GlobalConfig::listConfig()
{
    String ret = "";
    JsonObject root = _doc.as<JsonObject>();
    for (JsonPair kv : root) 
    {
        ret += kv.key().c_str();
        ret += " : " ;
        if (kv.value().is<char*>())
            ret += kv.value().as<char*>(); 
        else if (kv.value().is<int>())
            ret += String(kv.value().as<int>());
        else if (kv.value().is<bool>())
        {
            if (kv.value().as<bool>())
                ret += "true";
            else
                ret += "false";
        }
        else if (kv.value().is<JsonArray>())
            ret += "Array";
        else if (kv.value().is<JsonObject>())
            ret += "JSON Object";
        ret += "\r\n";
    }
    return (ret);
}

uint8_t GlobalConfig::saveConfigToJSON()
{
    File cfgFile = LittleFS.open("/config.json", "w");
    if (!cfgFile)
    {
        Serial.println("[CONFIG] Unable to open config file for writing");
        _status = GC_ERRNO_FILEOPENFAILED;
        return(_status);
    }
    if (serializeJson(_doc, cfgFile) == 0)
    {
        Serial.println("[CONFIG] Unable to write config file");
    }
    cfgFile.close();
}

uint8_t GlobalConfig::saveConfigToJSON(char* fileName)
{
    // open file
    File cfgFile = LittleFS.open(fileName, "w");
    if (!cfgFile)
    {
        Serial.println("[CONFIG] Unable to open config file for writing");
        _status = GC_ERRNO_FILEOPENFAILED;
        return(_status);
    }
    // serialize
    if (serializeJson(_doc, cfgFile) == 0)
    {
        Serial.println("[CONFIG] Unable to write config file");
    }
    // file close
    cfgFile.close();
    // list SPIFFS

}

JsonVariant GlobalConfig::getCfg(char* key)  
{
    JsonVariant result = _doc[key];
    return (result);
}

JsonVariant& GlobalConfig::operator[](char *key)
{
    JsonVariant result = _doc[key];
    return (result);
}

DynamicJsonDocument GlobalConfig::getJSONConfig()
{
    return(_doc);
}

void GlobalConfig::resetConfig()
{
    _doc["configured"] = false;
    _doc["wifissid"] = "";
    _doc["wifipwd"] = "";
}

void GlobalConfig::setCfg(char* key, char* value)
{
    _doc[key] = value;
}

void GlobalConfig::setCfg(char* key, int value)
{
    _doc[key] = value;
}

void GlobalConfig::setCfg(char* key, bool value)
{
    _doc[key] = value;
}

bool GlobalConfig::isSuccess()
{
    if (_status)
        return (true);
    else
        return (false);
}