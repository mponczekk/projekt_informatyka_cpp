# projekt_informatyka_cpp
Projekt "Arkanoid" na przedmiot Informatyka II </br>
Autor: Mateusz Pączkowski 

Sterowanie w menu odbywa się poprzez wciskanie klawiszy strzałek góra i dół. Aktualnie wybrane pole podświetla się na pomarańczowo, a aby przejść do wybranej opcji, należy nacisnąć przycisk ENTER.

Po wybraniu opcji „Nowa gra” uruchamia się rozgrywka. Gra polega na odbijaniu piłki paletką, którą można poruszać w lewo i prawo za pomocą klawiszy A, D lub strzałek lewo/prawo. Celem gry jest zbijanie bloczków poprzez uderzanie w nie piłką. Cegły posiadają od 1 do 3 „żyć” i różnią się kolorem:

białe – 1 życie,

pomarańczowe – 2 życia,

zielone – 3 życia.

Po wciśnięciu ESC podczas gry, aktualny stan zostanie zapisany do pliku zapis.txt, a gracz zostanie przeniesiony z powrotem do menu, gdzie ponownie można dokonać wyboru.

Wybranie opcji „Wczytaj grę” powoduje wczytanie ostatniego zapisanego stanu gry z pliku zapis.txt.
Natomiast po wybraniu opcji „Wyjście” następuje zamknięcie graficznego menu.
