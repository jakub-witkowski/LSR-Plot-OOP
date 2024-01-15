# LSR-Plot-OOP

W kodzie są już zawarte instrukcje #include do plików nagłówkowych ROOT (https://root.cern/install/).

Dołączone do repozytorium pliki csv pozwalają przetestować różne warianty ładowania danych wejściowych:
1. zbiór danych w 1050.csv zawiera dwie luki, więc program próbuje utworzyć trzy obiekty klasy TSegment;
2. zbiór danych w pliku wrong.csv jest nieposortowany;
3. zbiór danych w pliku 1050nh.csv nie zawiera luk, więc w programie powstanie jeden obiekt klasy TSegment;

Ogólna logika programu - pseudokod:
1. Wczytaj zbiór danych do obiektu klasy TData.
2. Sprawdź czy zbiór danych jest posortowany. Jeśli nie, posortuj zbiór.
3. Jeśli zbiór danych jest posortowany, sprawdź czy występują w nim hiatusy.
4. Jeśli nie ma hiatusów, przekaż dane do jednego obiektu klasy TSegment.
5. Jeśli występuje n hiatusów, utwórz n+1 obiektów klasy TSegment i przekaż do nich dane z odpowiednich przedziałów głębokości i wieku.
6. W każdym obiekcie klasy TSegment znajdź wielomian o najkorzystniejszym dopasowaniu (wyrażonym przez chi2/ndf) i zwróć jego parametry, chi2, liczbę stopni swobody (ndf).
7. W każdym obiekcie klasy TSegment przelicz głębokości zgodnie ze znalezioną regresją wielomianową (wygładzanie zbioru danych).
8. W każdym obiekcie klasy TSegment oblicz wahania tempa akumulacji osadu w funkcji czasu dla surowego oraz wygładzonego zbioru danych. Zwróć tabelę surowych oraz wygładzonych wartości tempa akumulacji osadu dla odcinków pomiędzy poszczególnymi punktami węzłowymi zbioru danych.
9. Utwórz obiekt klasy TPlot przedstawiający wykres głębokości względem wieku (surowy i wygładzony zbiór danych) oraz wykres wahań tempa  akumulacji (surowy i wygładzony zbiór danych).

Przykład potencjalnego zastosowania z rzeczywistego projektu badawczego: https://cp.copernicus.org/articles/17/1937/2021/ (szczególnie suplement)