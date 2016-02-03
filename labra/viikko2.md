Käytännössä suuri osa viikon työstä kului reilun kymmenen rivin koodaamiseen.
CRC aiheutti suurta päänvaivaa lähinnä koska eri kokoisten numeroiden XOR
tapahtuu LSB järjestyksessä, ja perinteisesti CRC tehdään MSB järjestyksessä.
Eli koodissa tarvitsee siis käyttää reverse polynomia jotta se toimii.
Ainakin CRC32 ja CRC1 (aka parity) tiomivat ongelmitta nyt. Ja naiivi ratkaisu
on vertailuna käyttämääni koodia monta kymmentä kertaa tehokkaampi (kuka olisi
uskonut että C on nopeampi kuin Perl).

Tällä hetkellä ohjelma ottaa inputtia vain tiedostoista, mutta se tukee koodissa
helposti stdin inputtia. Tämän tukeminen vaatii vain komentorivi käskyjen
parsimisen. Tämän, sekä testaamis ympäristön koodaus on seuraavan viikon
päätavoitteena. Myös MD5 olisi tarkoitus aloittaa.
