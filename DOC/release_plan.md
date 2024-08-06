# Release plan for Central Display

## Preliminary release

- [X] SW to test the motor movement by SPI (with csv)

## Internal release 2.5 (noi usiamo notazione umana)

- [X] Ripulire tutti le opzioni di compilazione per MCU2 MCU3
- [X] Inserire lettura e setting velocità per velocità < 225deg (3 wait su ogni passo)
- [X] Modificare short path con posizione assoluta
- [X] Ricerca zero
- [X] Correggere da fattore precisione 10 a fattore precisione 8

### Internal Release 2.6

- [ ] Abilitazione del secondo motore solo su MCU2 in base a messaggio
- [ ] Salvataggio offset ricevuto da STm32
- [ ] Aggiungere un comando di I2C da STm32 di N byte (8 potrebbero bastare ma potremmo fare anche 16).
- [ ] Scrittura:
  - MCU identifier (HHMM o SS)
  - Stato
  - A lot of dummy
- [ ] Lettura
  - SW Version e Boot version (cabliamo pure 0.1) al momento
  - A lot of dummy
- [ ] Rampe di accelerazione e decelerazione per:
  - Velocità maggiori di 223
  - Cambi velocità (immagino che se ora diamo un -200deg/s mentre fa +200deg/s ci siano problemi)
