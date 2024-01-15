# LSR-Plot-OOP

Na obecnym etapie pracy do kompilacji nie jest potrzebny framework ROOT.

Dołączone do repozytorium pliki csv pozwalają przetestować różne warianty ładowania danych wejściowych:
1. zbiór danych w 1050.csv zawiera dwie luki, więc program próbuje utworzyć trzy obiekty klasy TSegment;
2. zbiór danych w pliku wrong.csv jest nieposortowany;
3. zbiór danych w pliku 1050nh.csv nie zawiera luk, więc w programie powstanie jeden obiekt klasy TSegment;