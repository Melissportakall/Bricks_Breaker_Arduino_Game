# 🕹️ Arduino Mega 2D Brick Breaker Arcade Machine

This project is an interactive 2D Brick Breaker arcade machine built on an **Arduino Mega** microcontroller. Developed as part of the **Kocaeli University Computer Engineering (PROLAB II)** curriculum, it demonstrates microcontroller programming, hardware integration, physics-based collision handling, ambient sensor integration, and dynamic game engine development.

The entire circuit layout, hardware integration, and software logic were designed and fully tested on the **Wokwi Simulation Engine**.

> 📸 **Visual Showcase:** You can inspect the complete circuit diagram, menu screens, gameplay mechanics, and LDR light-sensor dynamics in the image galleries below.

---

## 📋 Comprehensive Technical Requirements & Features

* **🕹️ Interactive Menu & Navigation System:** 
  * Features a start screen with "Start" and "Exit" options navigated via Up/Down pushbuttons and selected with a 3rd selection button.
  * Selecting "Start" initializes the game board with the ball placed on the paddle.
  * Selecting "Exit" displays *"Seçilen seçenek: Çıkış"* followed by *"Oyunumuza gösterdiğiniz ilgi için teşekkürler."* and closes the game interface.
* **📐 Dynamic Physics & Reflection Engine:** 
  * Ball trajectory and bounces against the top, left, and right wall boundaries follow realistic physical rules (no abnormal or trajectory-bug behaviors).
  * Smooth collision physics between the ball, bricks, and the moving paddle.
* **🎚️ Analog Paddle Controls:** 
  * Potentiometer-driven horizontal paddle movement with tuned input sensitivity for precise control.
* **❤️ Health System & Power-Up Mechanics:** 
  * Players start each game with 3 lives, visually tracked via 3 physical LEDs.
  * Losing the ball past the paddle deducts 1 life and resets the ball onto the paddle.
  * Destroying a brick has a **10% chance** to drop a collectible power-up object that moves straight down. Catching this object with the paddle restores **+1 life** (e.g., updating remaining lives from 2 to 3 instantly on the LEDs).
  * When all 3 lives are lost, the final score displays on the screen for **3 seconds** before automatically returning to the main menu.
* **☀️ LDR Ambient Light Sensor (Day/Night Mode):** 
  * Integrates a Photoresistor (LDR) to toggle background/brick themes dynamically based on light levels (e.g., black background with white bricks in ambient light, inverted when lighting changes).
* **🚀 Multi-Level Progression & Velocity Scaling:** 
  * Clearing all bricks triggers a **5-second interlude screen** before loading the next level.
  * Subsequent levels feature custom brick layouts while retaining the player's cumulative score.
  * Ball speed increases by **+20%** with each newly unlocked level.
* **📊 Dual 7-Segment Real-Time Scoreboard:** 
  * Real-time score output incremented by 1 for every broken brick and displayed on a 2-digit 7-segment display.

---

## ⚙️ Circuit Components & Hardware Architecture

| Component | Quantity | Description / Usage |
| :--- | :---: | :--- |
| **Arduino Mega 2560** | 1 | Primary processing unit running the game loop and managing I/O pins. |
| **TFT - LCD Display** | 1 | Graphical display rendering the main menu, game field, paddle, ball, and bricks. |
| **Potentiometer** | 1 | Analog controller regulating paddle movement across the horizontal axis. |
| **Pushbuttons** | 3 | Menu controls (Up, Down, and Select buttons). |
| **Photoresistor (LDR)** | 1 | Light sensor dynamically inverting background and brick visual styles. |
| **7-Segment Display** | 2 | Dual-digit scoreboard displaying current game points. |
| **LEDs & Resistors** | 3 | Physical visual indicators representing remaining player lives. |
| **Jumper Wires & Breadboard** | Multi | Circuit interconnectivity. |

---

## 🖼️ Circuit & Gameplay Screenshots

<p float="left">
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/457ef37f-cdc3-4dc1-8467-7e9342065db9" width="48%" alt="Circuit Diagram" />
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/a573fde7-67e0-4738-b6c8-0f5d10a9a201" width="48%" alt="Start Menu" />
</p>

<p float="left">
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/7cb9bf73-de53-407f-a87d-e390d9c89ebe" width="48%" alt="Gameplay Mechanics" />
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/390009a1-4fa4-4565-a93f-96ca91ca2c32" width="48%" alt="Power-up and LED Score" />
</p>

<p float="left">
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/ad45803c-e489-41a8-9be1-574e3e986e12" width="48%" alt="LDR Sensor Light Effect" />
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/cbf5938e-a8e2-4d03-bd04-c42de2617c8b" width="48%" alt="Game Over Screen" />
</p>

---

## 🎮 Live Simulation & Demonstration

You can test the circuit connections, review the source code, and play the game directly in your browser:

👉 **[Play the Project on Wokwi Live Simulation](https://wokwi.com/projects/395800244052998145)**

---

<br />

# Arduino Mega Tabanlı 2D Tuğla Kırma Oyun Makinesi

Bu proje, **Arduino Mega** mikrodenetleyicisi üzerinde geliştirilmiş etkileşimli bir 2D Tuğla Kırma (Brick Breaker) oyun makinesidir. **Kocaeli Üniversitesi Bilgisayar Mühendisliği (PROLAB II)** eğitimi kapsamında **Arduino ve mikrodenetleyici mimarilerini öğrenme** sürecinde; donanım entegrasyonu, fizik tabanlı çarpışma algoritmaları, sensör kontrolü ve zamanlı oyun döngüsü geliştirmek amacıyla hazırlanmıştır.

Devre şeması, kod mimarisi ve tüm donanım bağlantıları **Wokwi Simülasyon Ortamı** üzerinde tasarlanmış ve tam fonksiyonel olarak doğrulanmıştır.

> 📸 **Görsel İnceleme:** Kurulu devre şemasını, menü ekranlarını, oyun mekaniklerini ve LDR ışık sensörü tepkilerini aşağıdaki görsel galerilerinden yan yana inceleyebilirsiniz.

---

## 📋 Detaylı Proje İsterleri ve Sistem Özellikleri

* **🕹️ İnteraktif Menü ve Gezinme Sistemi:** 
  * Açılış ekranında "Başlat" ve "Çıkış" seçenekleri yer alır. Kullanıcı aşağı/yukarı tuşlarıyla gezinip 3. bir butonla seçim yapabilir.
  * "Başlat" seçildiğinde oyun ekranı açılır, top palet üzerinde sabit vaziyette bekler ve palet hareket ettirildiği anda oyun başlar.
  * "Çıkış" seçildiğinde ekranda *"Seçilen seçenek: Çıkış"* ve ardından *"Oyunumuza gösterdiğiniz ilgi için teşekkürler."* mesajı gösterilerek sistem kapanır.
* **📐 Fizik Kurallarına Uygun Çarpışma Mekanizması:** 
  * Topun sol, sağ ve üst duvarlara, tuğlalara ve hareketli palete çarpma açıları tam fizik kuralları çerçevesinde kodlanmıştır (absürt top hareketleri engellenmiştir).
* **🎚️ Potansiyometre İle Palet Kontrolü:** 
  * Paletin sağ/sol eksendeki hassas kontrolü potansiyometreden alınan analog veri ile sağlanmaktadır.
* **❤️ Can Sistemi ve Düşen Obje (Power-up) Mekanizması:** 
  * Her oyuncu oyuna 3 can ile başlar ve kalan canlar 3 adet fiziksel LED ile gösterilir. Top paletten kaçıp aşağı düştüğünde 1 can eksilir ve top tekrar palet üzerinde başlar.
  * Kırılan her tuğladan **%10 şans ile** sabit hızla aşağı düşen bir obje belirir. Palet ile bu obje yakalandığında oyuncunun canı +1 artar ve aynı anlı olarak LED'lere yansır (örneğin 2 canı olan oyuncunun yanan LED sayısı 3'e yükselir).
  * Oyuncunun 3 canı bittiğinde ekranda son skor **3 saniye** boyunca gösterilir ve ardından otomatik olarak ana menüye dönülür.
* **☀️ LDR Sensörü İle Gece/Gündüz Modu (Tema Değişimi):** 
  * Fotorezistör (Işık sensörü) kullanılarak ortam ışığına göre arka plan ve tuğla renkleri otomatik tersine çevrilir (örneğin ortam ışığı açıldığında arka plan siyah, tuğlalar beyaz olur).
* **🚀 Çok Seviyeli Bölüm Yapısı ve Hız Artışı:** 
  * Ekrandaki tüm tuğlalar bittiğinde **5 saniyelik ara ekran** girer ve yeni bölüm başlar.
  * Yeni bölümde tuğla dizaynı değişir, skor kaldığı yerden devam eder ve topun hızı her seviye geçildiğinde bir önceki tura göre **%20 oranında artar**.
* **📊 2-Digit 7-Segment Dijital Skor Göstergesi:** 
  * Kırılan her tuğlada skor 1 puan artar ve 2 basamaklı Seven-Segment Display üzerinden anlık olarak takip edilebilir.

---

## ⚙️ Devre Bileşenleri ve Donanım Listesi

| Bileşen | Adet | Açıklama / Kullanım Amacı |
| :--- | :---: | :--- |
| **Arduino Mega 2560** | 1 | Ana işlemci kartı; I/O pinleri ve oyun mantığının yönetimi. |
| **TFT - LCD Display** | 1 | Ana menü, oyun alanı, palet, top ve tuğla grafiklerinin çizdirildiği ekran. |
| **Potansiyometre** | 1 | Paletin sağ/sol hareketini sağlayan analog kontrol elemanı. |
| **Pushbutton (Buton)** | 3 | Menü seçenekleri arasında gezinme ve seçim onaylama butonları. |
| **Fotorezistör (LDR)** | 1 | Ortam ışığına bağlı görünüm ve tema değişimi sağlayan ışık sensörü. |
| **7-Segment Display** | 2 | Oyun skorunu 2 basamaklı olarak anlık gösteren dijital ekran. |
| **LED ve Dirençler** | 3 | Kalan can sayısını fiziksel olarak gösteren ışıklı göstergeler. |
| **Jumper Kablolar** | Çoklu | Devre elemanları arasındaki hat bağlantıları. |

---

## 🖼️ Devre ve Çalışma Ekranı Görselleri

<p float="left">
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/457ef37f-cdc3-4dc1-8467-7e9342065db9" width="48%" alt="Devre Şeması" />
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/a573fde7-67e0-4738-b6c8-0f5d10a9a201" width="48%" alt="Başlangıç Menüsü" />
</p>

<p float="left">
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/7cb9bf73-de53-407f-a87d-e390d9c89ebe" width="48%" alt="Oyun Mekaniği" />
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/390009a1-4fa4-4565-a93f-96ca91ca2c32" width="48%" alt="Düşen Can Efekti ve LED Skor" />
</p>

<p float="left">
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/ad45803c-e489-41a8-9be1-574e3e986e12" width="48%" alt="LDR Sensör Efekti" />
  <img src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/cbf5938e-a8e2-4d03-bd04-c42de2617c8b" width="48%" alt="Oyun Sonu Ekranı" />
</p>

---

## 🎮 Canlı Wokwi Simülasyonu ve Kodlar

Projenin kurulu devresini, kaynak kodlarını ve simülasyonunu tarayıcınız üzerinden incelemek ve oyunu oynamak için bağlantıyı kullanabilirsiniz:

👉 **[Wokwi Üzerinde Simülasyonu Çalıştır ve Oyna](https://wokwi.com/projects/395800244052998145)**
