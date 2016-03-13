Ohjelma compileattu -O3 optimoinneilla ilman -g lippua.
Tämän lisäksi kaikki testit suoritettu binäärilipulla, eli luetaan tiedostot biäärimuodossa eikä tekstimuodossa.

# Zeroes
Ensimmäinen testitiedosto on 500 megatavun tiedosto jossa on pelkkiä nollia (`head -c 500M /dev/zero > zero`).

## Pariteetti
Yllättäen kyllä, pariteetin laskeminen vie erittäin vähän aikaa (170ms omalla koneellani). Tähän liittynee SSDn nopeus, käyttöjärjestelmän optimoinnit, sekä se että XOR operaatio on erittäin nopea.

## CRC32
7300ms, hidasta lähinnä siksi ettei koodia ole optimoitu käyttämään taulukkohakua.

## SHA1
Vaikka SHA1 ei annakkaan oikeita tuloksia tällä hetkellä, pitäisi sen nopeuden kuitenkin olla hyvinkin vertilukelpoinen. 5700ms, joka on huomattavasti enemmän kuin debianin sha1sum jolla kestää 1400ms, ja tämä vaikuttaa todella oudolta...

# Random Small
Yhden megatavun kokoinen tiedosto sattumanaraista dataa (`head -c 1M /dev/urandom > randoms`).

## Pariteetti
Kuka olisi uskonut(!!), mutta keskimäärin alle 1ms. Tiedosto on hyvin pieni, SSD on nopea ja XOR on helppoa koneelle.

## CRC32
15ms, tässä kohtaa C toteutus on vielä nopeampi kuin hyvin optimoitu Perl toteutus (en tiedä tarkalleen mitä vertailuun käyttämässäni Perl toteutuksessa on tehty koska se on erittäin nopea kun tiedostokoot kasvavat isoiksi, todennäköisesti pelkkä taulukkohaku nopeuttaa vain koodia niin paljon).

## SHA1
13ms vs sha1sum:n <4ms. Sen lienee koodannu joku taikuri.

# Random Large
500 megatavun kokoinen tiedosto sattumanaraista dataa (`head -c 500M /dev/urandom > randoml`).

## Pariteetti
Hieman kauemmin kuin vain puhtaiden nollien pariteetin laskeminen (175ms) ja merkittävästi isommalla varianssilla. Tämä selittynee sillä että täysin sattumanvaraisen datan lukeminen on saattaa olla välillä hitaampaa, ja sen lukemista on vaikeampaa optimoida (koska pakkaaminen on hyvin hankalaa).

## CRC32
7200ms, kuten voi odottaa niin CRCn laskemisessa tiedoston sisällollä ei ole merkittävää vaikutusta (vertailu toteutus on noin 10x nopeampi tämän kokoiselle tidostolle).

## SHA1
5700ms vs sha1sum:n 1400ms, eli sama tulos kuin täysin nolla datalla joka ei ole koin yllättävää.

# Kansiollinen musiikkia
Nimeltä mainitsemattoman tummaihoisen rap/hip hop artistin viimeisin levy. 18 kpl mp3 tiedostoja, yhteensä ~108 megatavua.

## Pariteetti
Ensimmäinen lukukerta kesti monta kertaa pidempää kuin seuraavat, johtunee cachingista. Keskimäärin 40ms.

## CRC32
1560ms, ei mitään yllättävää. Jotakuinkin odotettu tulos.

## SHA1
1250ms vs sha1sum:n 300ms, miten??

# Appendix
"Oikeat" ohjelmoijat on vähän niin kuin yksisarvisia, niitä ei ole olemassa, tai kukaan ei ole ainakaan ikinä nähnyt sellaista, mutta silti niistä kuulee vähän väliä.

## Optimoinnin tärkeys
Esimerkiksi CRC32 laskeminen -O0 optimoinnilla kestää reilut 5x pidempään, ja pariteetin laskeminen noin 2x pidempään (aka compiler on ihan kiva).
