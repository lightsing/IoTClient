#ifndef X_UTIL_H_   /* Include guard */
#define X_UTIL_H_

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <Hash.h>

#include "config.h"

struct Response{
  bool success = false;
  String content = "";
};

String appendHashToString(String content, String authString);
Response sendToHost(String content);

#define ACCESS_DENINED "Access Denined"

Response regDevice(String name);

struct PollContent{
  String accessToken = "";
  String lastStatus = "";
  String optional = "";
  String toString(){
    return accessToken + " " +
           lastStatus  + " " +
           optional;
  }
};

struct PollResponse{
  Response response;
  bool changeStatus = false;
  String newStatus = "";
};
PollResponse pollUpdate(PollContent poolContent);

#endif
