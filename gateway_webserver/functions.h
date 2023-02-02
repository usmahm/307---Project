//=======================================
//handler funtions - sends webpage code to the server
//=======================================
void handle_OnConnect()
{
  server.send(200,"text/html", webpageCode);
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

//=====================================================
//function process event: to receive new data from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);
}
