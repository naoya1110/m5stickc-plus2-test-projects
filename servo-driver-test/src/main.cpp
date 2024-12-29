// 参考
// M5StickC Plus2の基本的な使い方 https://logikara.blog/m5stickc-plus2-init/
// シリアルプリントのボーレート設定 https://qiita.com/inouetai/items/a4f8b134be7cc40bc42e
// VSCodeのシリアルモニタ https://qiita.com/ELIXIR/items/6ca7cee9accceba37216

#include <M5StickCPlus2.h>

// サーボ用ライブラリのインクルード
// 以下からZIPをダウンロードして解凍したフォルダをlibに入れておく
// https://github.com/m5stack/M5Unit-8Servo/tree/main
#include "M5_UNIT_8SERVO.h" // サーボ用ライブラリのインクルード


// メモリ描画領域表示（スプライト）のインスタンスを作成(必要に応じて複数作成)
M5Canvas canvas(&M5.Lcd);  // &M5.Lcd を &StickCP2.Display と書いても同じ
M5_UNIT_8SERVO unit_8servo; // サーボ用ライブラリのインスタンスを作成

// 端子割り当て
#define LED 19  // 本体LED

// 初期設定 -----------------------------------------
void setup() {
    auto cfg = M5.config();  // 本体初期化
    M5.begin(cfg);
    
    Serial.begin(115200);    // シリアル通信速度設定
    Serial.println("M5StickC Plus2 servo test");

    // M5 Unit 8SERVOの初期化（デフォルトI2Cピンとアドレスを使用）
    while (!unit_8servo.begin(&Wire, 32, 33, M5_UNIT_8SERVO_DEFAULT_ADDR)) {
        Serial.println("Cannot initialize M5 Unit 8SERVO.");
        delay(100);
    }

    // 出力設定
    pinMode(LED, OUTPUT);    // 本体LED赤
    digitalWrite(LED, LOW);  // 本体LED初期値OFF（LOW）

    // G36とG25は同時使用不可。使っていない方は以下のようにフローティング入力にする
    gpio_pulldown_dis(GPIO_NUM_25);
    gpio_pullup_dis(GPIO_NUM_25);

    // ベース画面の初期設定
    M5.Lcd.fillScreen(BLACK); // 背景色
    M5.Lcd.setRotation(1);  // 画面向き設定（USB位置基準 0：下/ 1：右/ 2：上/ 3：左）
    M5.Lcd.setTextSize(1);  // 文字サイズ（整数倍率）

    canvas.setTextWrap(false);  // 改行をしない（画面をはみ出す時自動改行する場合はtrue。書かないとtrue）
    canvas.createSprite(M5.Lcd.width(), M5.Lcd.height()); // canvasサイズ（メモリ描画領域）設定（画面サイズに設定）
}

// メイン -----------------------------------------
void loop() {
  M5.update();  //本体ボタン状態更新

    canvas.setFont(&fonts::Font4);        // 画面描画のフォント設定

    unit_8servo.setServoPulse(0, 1000);     // Ch0のサーボを1000usに設定
    canvas.setTextColor(ORANGE, BLACK);     // 文字色指定(文字色, 背景)
    Serial.println("Servo Ch0 1000us");     // シリアルモニタに表示
    
    digitalWrite(LED, HIGH);                // 本体LED点灯
    canvas.fillScreen(BLACK);               // 画面初期化
    canvas.setCursor(15, 60);               // 画面の座標設定(x, y)
    canvas.print("Ch0 1000us");             // 画面の文字表示
    canvas.pushSprite(&M5.Lcd, 0, 0);       // (0, 0)座標に一括表示実行
    delay(1000);

    unit_8servo.setServoPulse(0, 2000);     // Ch0のサーボを2000usに設定
    Serial.println("Servo Ch0 2000us");     // シリアルモニタに表示
    digitalWrite(LED, LOW);                 // 本体LED消灯
    canvas.fillScreen(BLACK);               // 画面初期化
    canvas.setTextColor(CYAN, BLACK);       // 文字色指定(文字色, 背景)
    canvas.setCursor(15, 60);               // 画面の座標設定(x, y)
    canvas.print("Ch0 2000us");             // 画面の文字表示
    canvas.pushSprite(&M5.Lcd, 0, 0);       // (0, 0)座標に一括表示実行
    delay(1000);
}