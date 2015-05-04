/**
 * @example TCPClientMultiple.ino
 * @brief The TCPClientMultiple demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.02
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "ESP8266.h"
#include "SoftwareSerial.h"

#define SSID        "tifa"
#define PASSWORD    "01005381961"
#define HOST_NAME   "192.168.4.1"
#define HOST_PORT   (8090)

SoftwareSerial myserial(7,8);

ESP8266 wifi(myserial);

void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

     if (wifi.kick()) {
        Serial.print(" ok\r\n");
    } else {
        Serial.print(" err\r\n");
    }

    if (wifi.setOprToStation()) {
        Serial.print("to station ok\r\n");
    } else {
        Serial.print("to station err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP: ");       
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
    
    Serial.print("setup end\r\n");
}

void loop(void)
{
    uint8_t mode[1] = {0};
    uint8_t buffer[128] = {0};
    static uint8_t mux_id = 0;
    
    if (wifi.createTCP(mux_id, HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ");
        Serial.print(mux_id);
        Serial.println(" ok");
    } else {
        Serial.print("create tcp ");
        Serial.print(mux_id);
        Serial.println(" err");
    }

    while(1)
    {
    char *hello = "Hello,this is client!";
    if (wifi.send(mux_id, (const uint8_t*)hello, strlen(hello))) {
        Serial.println("send ok");
    } else {
        Serial.println("send err");
    }
    
 uint32_t len = wifi.recv(mux_id, buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        
        for(uint32_t i = 0; i < len; i++) {
            Serial.print(buffer[i]);
        }
        Serial.print("]\r\n");
    }
 
   
    if(buffer[0]==0)
    {
      Serial.print("Sleep mode: 1 second\n");
    delay(1000);
    
  }
  else{
    Serial.print("Sleep mode: 5 second\n");
    delay(5000);
  }
   
    }

}

