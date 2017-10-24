# LAB1
First laboratory exercise in OS class

# Objašnjenje
Ovo je prvi labos iz predmeta Operacijski sustavi na FERu. 
- Prvi program u pozadini računa prim brojeve te ih ispisuje svakih nekoliko sekundi. Na signal SIGINT staje s računom, ali nastavlja ispisivati zadnji izračunati prim broj. Na signal SIGTERM program ispisuje posljednji izračunati prim broj te završava s radom.
- Drugi zadatak sastoji se od dva programa. Jedan program generira jedan od 4 proizvoljna signala, te koristeći početni argument koji je ID programa kojemu se signali šalju, svakih [3, 5] sekundi šalje nasumično odabran signal.
- Drugi program simulira unutarno stanje programa, tj. simulira odnose glavnog procesa i viših prioriteta. SIGINT koristi se kao signal za najveći prioritet; 5. Svaki prekid se obrađuje na način da pseudodretva troši 5 sekundi, a svake sekunde ispisuje trenutni progres.
- Kada u generatoru prekida pošaljemo SIGINT, on se gasi, ali se prekida i obrada prekida, tj. šalje se SIGKILL.

# ToS
Dopušteno je koristiti kod u edukacijske svrhe, ali nikako nije dopušteno:
- prepisati kod ili cijele dijelove koda za svoju laboratorijsku vježbu
- prepisati kod ili cijele dijelove koda za komercijalne svrhe bez kontaktiranja autora
- koristiti kod za bilo kakvu drugu potencijalno nemoralnu i akademski nečasnu radnju (ako ste u dilemi, kontaktirajte autora)
- za svaki prijestup gore naveden ovaj se README file može koristiti kao dokaz za nevinost autora.
- samim korištenjem bilo koje komponente ovog koda pristajete na gore navedene uvjete bez ikakvih drugih uvjeta, makar koristili kod BEZ ovog READMEa. Ovo je jedini original, te autor ne odgovara ni za kakvu štetu prouzrokovanu drugim releasovima istog koda.
