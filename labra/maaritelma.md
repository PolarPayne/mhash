Toteutan hajautusalgoritmeja.
Ajatuksena olisi toteuttaa ainakin CRC, sekä mahdollisesti MD5 ja SHA1.
Jos vaikuttaa että algoritmien oikein toteuttaminen ei vie paljoa aikaa
(jolta vaikuttaa hieman lisää aiheesta luettuani), laajennan projektia
jonkun näköisellä salauksella/allekirjoittamisella. Todennäköisesti RSAlla.

Hajautusalgoritmien aikavaativuudet ovat O(n) luokkaa, ja oletettavasti
saan myös toteutettua ne siinä. Niiden nopeuksilla eri toteutuksilla voi
kuitenkin olla suuriakin eroja, ja aion verrata omien toteutuksieni nopeuksia
tunnettuihin ja laajasti käytettyihin open source versioihin. Tavoite on
että toteutukseni käytännön käytössä yhtä nopeita (erot millisekunneissa, ei
sekunneissa). Aion myös käyttää tunnettuja toteutuksia minun toteutusten
oikeellisuuden testaamiseen.

Tietorakenteina tuskin tarvitsee muuta kuin taulukon, ja mahdollisesti linkitetyn
listan. Sama pätee salausten ja allekirjoitusten kanssa.

Ohjelma tulee toimimaan komentorivillä, ja pyrin tekemään siitä korvaavan
työkalun muille vastaaville linux ohjelmille. Syötteen voi antaa joko
stdio kautta tai tiedostoina.

Ajatuksena olisi myös toteuttaa kaikki käyttäen pelkkää Cn standardi kirjastoa.

