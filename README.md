KOCAELİ ÜNİVERSİTESİ PROLAB PROJE 2

╰┈➤Bu projenin amacı, çeşitli araçlar kullanarak mikrodenetleyici tabanlı bir oyun makinesi
geliştirmektir.

 İSTERLER
 
 • İlk açılacak ekranda “Başlat” ve “Çıkış” seçeneklerV olacak. Kullanıcı bunlara aşağı ve
yukarı tuşlarıyla gelerek 3.bir tuş ile menüde bulunan seçeneklerden birini
seçebilecektir.
 
 • “Başlat” tuşuyla oyun ekranı açılacak ve oyun başlayacaktır.”Çıkış” seçeneğinde ise
“Oyunumuza gösterdiğiniz ilgi için teşekkürler” yazısı yazacaktır.

• Oyun başladıktan sonra kullanıcının kontrol ettiği palet potansiyometre ile sağ ve sol
hareketleri yaptırılacaktır. Bunun hassasiyet ayarı öğrencilere bırakılmıştır.

• Palet ile yönlendirme yapılan top çarptığı tuğlaları kıracak ve yön değiştirecektir. Ayrıca
top platformun sağ, sol ve platformun bitişinin üst tarafındaki duvara çarpıncada yön
değiştirmelidir. Yön değiştirmeler fizik kuralları çerçevesinde olmalıdır.(Absürt top
hareketleri olmamalıdır.)

• Her tuğla kırıldığında seven segment displayda gösterilecek skor puanı 1 artmalıdır.

• Her kullanıcı oyuna başladığında 3 canı vardır. Bu canlar led ile gösterilmelidir. Top,
palet ile kurtarılamayıp aşağı düştüğünde oyuncunun 1 canı gVder. Daha sonra tekrar
top paletVn üstünde olarak oyun başlar.

• Her tuğla kırıldığında yüzde 10 şans ile bir obje düşürecektVr. Bu obje kırıldığı tuğladan
sabit olarak aşağı yöne doğru hareket edecektir. Oyuncu bu objeyi alırsa can sayısı 1
artacaktır. Bu eşzamanlı olarak led ile gösterilecektir.(Kullanıcının 2 canı varsa aldığı
canla beraber 3 canı led ile gösterilecektir.)

• Oyuncunun 3 canı bittiğinde ekranda son olarak 3 sanVye skor puanı belirerek tekrar
ana menüye geri döner.

• Yukarıdaki örnek ekranda olduğu gibi oyunun arka planı siyah, tuğlalar beyaz olacaktır.
Bu 2 objenin rengi ışık sensörüne göre tam tersine değişebilecektir. (Işık açılınca
arkaplan siyah, tuğlalar beyaz olacaktır.)

• Oyundaki tüm tuğlalar bitince 5 saniye ara ekran girecek ve daha sonra diğer bölüm
başlayacaktır. Bu bölümdeki tuğla dizaynının aynı olmaması beklenmektedir. Skorun
kaldığı yerden devam etmesi beklenmektedir. Ayrıca her bölüm geçildiğinde topun hızı
bir önceki tura göre yüzde 20 artacaktır.

╰┈➤ Oyunumuz projedeki isterleri tümüyle karşılamaktadır.

⚙️🛠GEREKLİ UYGULAMALAR⚙️🛠

╰┈➤Biz bu projeyi yaparken Wokwi Simülasyonunu kullandık.
Wokwide aynı anda hem kod yazabilmek hem de devreyi bağlayabilmek mümkün.Bu özelliğini beğendiğimizden biz Wokwiyi tercih ettik.Proteus ve Arduino ile de yapılabilir.

🚨DEVRE KISMI🚨

╰┈➤Devre elemanlarımız: Arduino Mega Kart,2 Seven Segment Display,Fotorezistör(Tuğlaların ve arkaplanın rengini değiştirebilmek için),TFT - LCD Display ekran, 3 Pushbutton(menüde seçenek seçebilmek için),3 led ve direnç (can sayısını gösterebilmek için),Potansiyometre(paletin hareketi için) ve bir sürü jumper kablo.

Devre elemanları kullanımı ve örnekleri wokwide çok güzel açıklanmış.Dokümanlarından okuyabilirsiniz ve örnekler üzerinden devreye elemanların nasıl bağlanacağını görebilirsiniz.

Devrenin gerekli bağlantılarını yaptıktan sonra son hali bu şekilde gözüküyor:

<img width="597" alt="Ekran Resmi 2024-04-21 22 07 00" src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/457ef37f-cdc3-4dc1-8467-7e9342065db9">

🎮🕹️👾💻 OYUNUN BAŞLANGIÇ EKRANI VE ÇALIŞMASI 🎮🕹️👾💻

<img width="572" alt="Ekran Resmi 2024-04-21 22 11 05" src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/a573fde7-67e0-4738-b6c8-0f5d10a9a201">





╰┈➤ Oyun başladığında karşımıza menü geliyor.Menüyü butonlar ile kontrol ediyoruz.Başlat seçersek oyun başlatıldı yazısını görüp top paletin üzerinde hareketsiz şekilde oyunumuz açılıyor.Paleti hareket ettirdiğimiz anda top fizik kurallarına uygun şekilde hareketine başlıyor.Ve oyun boyunca fizik kurallarına göre hareket edip tuğlaları kırıyor.


<img width="724" alt="Ekran Resmi 2024-04-21 22 19 48" src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/7cb9bf73-de53-407f-a87d-e390d9c89ebe">
<img width="514" alt="wokwi2" src="https://github.com/Melissportakall/Bricks_Breaker_Arduino_Game/assets/137406380/390009a1-4fa4-4565-a93f-96ca91ca2c32">

╰┈➤Kırdığımız bazı tuğlalardan isterlere göre parça düşürüyoruz ve eğer palet ile düşen parçayı tutabilirsek can kazanmış oluyoruz.yanan led sayımızı güncelleyerek kalan can sayılarımızı ekranda gösteriyoruz.

╰┈➤ Aynı şekilde kırdığımız tuğlalara göre skorumuz 2 digit seven segmnet displayde güncelleniyor ve skorumuzu görebiliyoruz.



╰┈➤ Eğer çıkış seçeneğini seçersek ise "Seçilen seçenek:Çıkış" ve ardından "Oyunumuza gösterdiğiniz ilgi için teşekkürler." ekranı geliyor ve oyunumuz kapanıyor.


╰┈➤Fotorezistör kullanımı sonucu oyunun görseli şu şekilde oluyor:


╰┈➤Oyunu oynadık ve canımız bittiyse en son karşımıza şu ekran geliyor ve oyunumuz kapanıyor:


