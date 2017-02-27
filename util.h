#ifndef X_UTIL_H_   /* Include guard */
#define X_UTIL_H_

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <Hash.h>

#include "config.h"

struct Response{
  bool success;
  String content;
};

String appendHashToString(String content, String authString);
Response sendToHost(String content);

Response regDevice(String name);
#define ACCESS_DENINED "Access Denined"
#endif
