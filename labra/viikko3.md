Löysin ja korjasin bugin joka tapahtui jos hashattava
tiedosto oli tarkalleen READBUFFERSIZE * N kokoinen.

Nyt ohjelmaa on myös testattu suuremmilla tiedostoilla,
ja kun tiedostot alkavat olla suurempia kuin muutaman
megan on vertailuna käytetty perl toteutus nopeampi.
Tämä johtuu todennäköisesti siitä että vertailu toteutus
käyttää hakutauluja. Tämä on mahdollinen, mutta kohtuullisen
hankala toteuttaa minun koodilleni, koska taulukko tarvitsee
luoda muistiin ensiksi, ja jokainen eri polynomi tarvitsee
eri hakutaulukon. Tutkin mahdollisuuksien mukaan tämän
toteuttamista.

Luin lisää ja tarkemmin [erinomaista artikkelia](http://zlib.net/crc_v3.txt)
CRCstä, ja minulla alkoi herää epäilys että koodin kanssa voi
olla ongelmia, mutta minulla ei ole mitään tapaa selvittää
toimiiko koodi oikein muulla kuin CRC32lla.

Tarkistin nyt myös CRC1 (eli even parity bit) ja se ainakin
toimii myös oikein.

Löysin, ja otin käyttöön pienen C kirjaston (4 riviä),
unit testaamista varten. Kirjoitin kaikille testitiedostoilleni
testit, nyt testit voi pyörittää kutsumalla `make test`.

Tein päätöksen hylätä mahdollisuuden käyttää samaa CRC
koodia usealle eri CRClle, ja aion pitää koodissa vain
CRC32sen. Tämä mahdollistaa koodin helpomman testaamisen,
sekä sen että pystyn etenemään muihin aiheisiin mahdollsimman
pian. Ajattelin nyt toteuttaa pariteetti bitin laskemisen
hakutauluilla, tämä antaa myös hyvää pohjaa CRC32 koodin
optimointiin hakutauluilla.
