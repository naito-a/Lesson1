#include <WiFi.h>
#include <WiFiClientSecure.h>

// 接続先のSSIDとパスワード
const char* ssid = "XXXX"; //無線ルーターのssidを入力
const char* password = "XXXX"; //無線ルーターのパスワードを入力

const int litsnsrPin = 3; //3:ConnectorA 4:ConnectorB
const float LUX_THRESHOLD = 100.0; // 100Lux以下で照明点灯判定
const unsigned long WAIT_TIME = 20000; // 20秒待機

// 状態管理変数
bool isWaitingForLight = false;
unsigned long waitStartTime = 0;
bool lightAlreadyNotified = false;

void setup() {
  Serial.begin(115200);
  pinMode(litsnsrPin, INPUT);
  Serial.println("照明点灯通知システム開始");
}

void loop() {
  // センサー値読み取り
  float litsnsr_ad = analogRead(litsnsrPin);
  float litsnsr_v = litsnsr_ad * 3.3 / 4096;
  float lux = 10000 * litsnsr_v / (3.3 - litsnsr_v) / 1000;
  
  Serial.print("現在の照度: ");
  Serial.print(lux);
  Serial.println(" Lux");
  
  // 照度判定とタイマー処理
  if (lux <= LUX_THRESHOLD) {
    if (!isWaitingForLight) {
      // 初回暗さ検出 - 待機開始
      isWaitingForLight = true;
      waitStartTime = millis();
      lightAlreadyNotified = false;
      Serial.println("暗さを検出しました。20秒待機開始...");
    } else {
      // 既に待機中 - 時間チェック
      unsigned long elapsedTime = millis() - waitStartTime;
      if (elapsedTime >= WAIT_TIME && !lightAlreadyNotified) {
        // 20秒経過 - 照明点灯通知送信
        Serial.println("20秒経過しました。照明点灯通知を送信します。");
        sendData();
        lightAlreadyNotified = true; // 重複送信防止
      }
    }
  } else {
    // 明るくなった場合 - 状態リセット
    if (isWaitingForLight) {
      Serial.println("明るくなりました。待機をリセットします。");
      isWaitingForLight = false;
      lightAlreadyNotified = false;
    }
  }
  
  delay(1000); // 1秒間隔で監視
}

//WiFiに接続
void connectWiFi(){
  Serial.print("ssid:");
  Serial.print(ssid);
  Serial.println(" に接続します。");
  WiFi.begin(ssid, password);
  Serial.print("WiFiに接続中");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("接続しました。");
  //IPアドレスの表示
  Serial.print("IPアドレス:");
  Serial.println(WiFi.localIP());
}
 
//測定データの送信
void sendData(){
  WiFiClientSecure sslclient;
  sslclient.setInsecure(); // SSL証明書の検証をスキップ
  const char* server = "script.google.com";
  String url = "https://script.google.com/macros/s/AKfycbxZP2h3I_MMInFlGqpo5ObX781aRBq1phgB5tzJXHAYSKBp6kp8x2CUmBbNxcUWyMsT1Q/exec";  //googlescript web appのurlを入力
  //測定値を準備
  float litsnsr_ad = analogRead(litsnsrPin); // Read analog data
  float litsnsr_v = litsnsr_ad * 3.3 / 4096; // Calculation of voltage value
  float lux = 10000 * litsnsr_v / (3.3 - litsnsr_v) / 1000; // Calculation of lux value
  Serial.print(lux);
  Serial.println(" Lux ");
  
  //wifiに接続
  connectWiFi();
  //測定値の表示
  Serial.println(lux);
  
  //urlの末尾に測定値を加筆（照明点灯通知として送信）
  url += "?1=" + String(lux, 1);      // B列: Lux値（小数点以下1桁）
  // C列（回答）とD列（備考）はAppSheetからの入力待ち
 
  // サーバーにアクセス
  Serial.println("サーバーに接続中...");
  //データの送信
  if (!sslclient.connect(server, 443)) {
    Serial.println("接続に失敗しました");
    Serial.println("");//改行
    return;
  }
  Serial.println("サーバーに接続しました");
  
  // 正しいHTTPリクエストヘッダーを送信
  sslclient.println("GET " + url + " HTTP/1.1");
  sslclient.println("Host: script.google.com");
  sslclient.println("Connection: close");
  sslclient.println();
  
  delay(1000); //私の環境ではここに待ち時間を入れないとデータが送れないことがある
  sslclient.stop();
  Serial.println("データ送信完了");
  Serial.println("");//改行
  //WiFiを切断
  WiFi.mode(WIFI_OFF);
}