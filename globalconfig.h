#ifndef globalconfig_h
#define globalconfig_h

#include "Arduino.h"
#include <ArduinoJson.h>
//#include <FS.h> //--> deprecated
#include "LittleFS.h"

#define SUCCESS 0
#define ERRNO_FILEOPENFAILED  1
#define ERRNO_FILEREADFAILED  2

class GlobalConfig
{
  private:
    DynamicJsonDocument _doc;

  public:
    GlobalConfig();
    uint8_t loadConfigFromJSON();
    uint8_t loadConfigFromJSON(char* fileName);
    uint8_t saveConfigToJSON();
    uint8_t saveConfigToJSON(char* fileName);
    void resetCOnfig();
    String listConfig();
    JsonVariant getCfg(char* key); 
    void setCfg(char* key, char* value);
    void setCfg(char* key, int value);
    void setCfg(char* key, bool value);
};

#endif