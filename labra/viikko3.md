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