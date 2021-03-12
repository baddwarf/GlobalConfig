#ifndef globalconfig_h
#define globalconfig_h

#include "Arduino.h"
#include <ArduinoJson.h>
//#include <FS.h> //--> deprecated
#include "LittleFS.h"

#define GC_SUCCESS 0
#define GC_ERRNO_FILEOPENFAILED  1
#define GC_ERRNO_FILEREADFAILED  2
#define GC_ERRNO_FILEWRITEFAILED 3

class GlobalConfig
{
  private:
    DynamicJsonDocument _doc;
    uint8_t _status;

  public:
    GlobalConfig();
    uint8_t loadConfigFromJSON();
    uint8_t loadConfigFromJSON(char* fileName);
    uint8_t saveConfigToJSON();
    uint8_t saveConfigToJSON(char* fileName);
    void resetConfig();
    String listConfig(); // TODO : Rename
    JsonVariant getCfg(char* key); // TODO : Replace by operator
    JsonVariant &operator[](char *key);
    DynamicJsonDocument getJSONConfig();
    void setCfg(char* key, char* value);
    void setCfg(char* key, int value);
    void setCfg(char* key, bool value);
    bool isSuccess();
};

#endif