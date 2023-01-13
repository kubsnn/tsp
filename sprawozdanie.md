# Problem komiwojażera
Mateusz Chlebosz 151817\
Jakub Aszyk 1518

## Algorytm Wyżarzania Symulowanego

### 1. Inicjalizacja
[rysunek z instancją początkową]
### 2. Opis Algorytmu
Kilka zdań (max. pół strony)
### 3. Pseudokod
$S$ = instancja początkowa\
$T$ = $T_0$ = temperatura początkowa
$T_min$ = temperatura minimalna\
$alpha$ = współczynnik zmniejszania temperatury\
```python
while T > T_min
    S_New = losowy_sasiad_instancji(S)
    Delta = długość(2) - długość(S)
    if Delta < 0
        S = S_New
    else
        prawdopodobienstwo = e^(-Delta/T)
        if losowa_liczba_z_przedziału(0,1) < prawdopodobienstwo
            S = S_New
    T = T * alpha
return S
```

### 4. Przykład obrazujący działanie
Najlepiej 2, 3 rysunki przedstawiające obraz instancji po najważniejszych krokach algorytmu. UWAGA! Przykład z tą samą instancją jak w pkt.1
### 5. Finalizacja
[rysunek z wynikiem działania algorytmu]
## Wykresy

1.	Porównaj optymalizowaną wartość (wynik) Algorytmu z A. zachłannym.
(wykres pokaże czy Algorytm jest lepszy i o ile od A. zach.
Instancje wygenerowane losowe, 15 punktów pomiarowych)
2.	Korzystając z bibliotek instancji (benchmarków) pokaż na wykresie wartość błędu względnego Algorytmu w stosunku do wartości optymalnej.
(wykres pokaże jak dobry jest Algorytm,
minimum 10 instancji, wykres słupkowy)
3.	Zamieść odpowiednią do tematu część Tabelki z Rankingu instancje z Tabelki są w katalogu  http://www.cs.put.poznan.pl/mmachowiak/instances/


| Instancja | Wynik |
| --------- | ----- |
| 1         | 0.0   |
| 2         | 0.0   |
| 3         | 0.0   |
