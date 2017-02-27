#include "util.h"

String appendHashToString(String content, String authString) {
  return content + ":" + sha1(content + token + authString) + "\n";
}

Response sendToHost(String content) {
  WiFiClientSecure client;
  Response response;
  if (!client.connect(host, port)) {
    response.success = false;
    response.content = "connection failed";
  } else if (client.verify(fingerprint, "IoT Center")) {
    String authString = client.readStringUntil('\n');
    client.print(appendHashToString(content, authString));
    response.success = true;
    response.content = client.readStringUntil('\n');
  } else {
    response.success = false;
    response.content = "certificate doesn't match";
  }
  Serial.println(response.success ? "Success" : "Fail");
  Serial.println(response.content);
  return response;
}

/* Reg Device
   Command: "REG [Device Name]"
   Response:
      Reg success:          "[Access TOKEN]"
      Access Denined:       "Access Denined"
   Comment:
      Device Name can contain spaces.
*/
Response regDevice(String name) {
  Response response = sendToHost("REG " + name);
  if (!response.success || (response.content == ACCESS_DENINED)) {
    response.success = false;
  }
  return response;
}

/* Poll Update
   Command: "POLL [Device Name] [Access TOKEN] [Last status] [Optional Content]"
   Response:
      Pool success:          "[New Status]"
      Access Denined:        "Access Denined"
   Comment:
      Poll new command from server.
*/
Response pollUpdate(PoolContent poolContent) {
  Response response = sendToHost("POLL " + poolContent.toString());
  if (!response.success || (response.content == ACCESS_DENINED)) {
    response.success = false;
  }
  return response;
}
