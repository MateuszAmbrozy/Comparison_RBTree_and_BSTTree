# Porównanie drzewa czerwnono-czarnego i binarnego
## Wstęp
W realizowanym projekcie zbadano różnice jakie występują pomiędzy drzewem czerwono-
czarnym, a drzewem BST. W tym celu zbadano czas działania operacji takich jak: dodawanie,
wyszukiwanie, usuwanie. Każdy pomiar wykonywano 20 razy, a następnie wyliczano z tego
średnią. Eksperymenty zostały przeprowadzone dla dwóch przypadków:
• losowe zestawy danych o następujących rozmiarach: 50 000, 100 000, 300 000, 600 000,
1 000 000, 1 500 000, 2 000 000, 2 500 000,
• uporządkowane rosnąco zestawy danych o rozmiarach: 500, 1 000, 1 500, 2 000, 2 500

## Opis teoretyczny badanych struktur

### Drzewo BST
Binarne drzewo poszukiwań, to dynamiczna struktura danych będąca drzewem binarnym, w
którym lewe poddrzewo każdego węzła zawiera wyłącznie elementy o kluczach mniejszych niż
klucz węzła, a prawe poddrzewo zawiera wyłącznie elementy o kluczach nie mniejszych niż
klucz węzła. Węzły, oprócz klucza, przechowują wskaźniki na swojego lewego i prawego syna
oraz na swojego ojca. Dzięki tej własności wyszukiwanie i sortowanie danych w drzewie są
efektywne czasowo.
Binarne drzewa poszukiwań można skonstruować w oparciu o różne strategie wyboru węzła
do podziału. Jedną z popularnych strategii jest wybór środkowego elementu jako korzenia
drzewa. Ta strategia prowadzi do utworzenia zrównoważonego drzewa, w którym czas po-
trzebny na wykonanie operacji wyszukiwania, wstawiania lub usuwania jest proporcjonalny
do logarytmu dwójkowego liczby węzłów. Z drugiej strony drzewo skrajnie niezrównoważone
ma wysokość porównywalną z liczbą węzłów, z tego powodu czas pesymistyczny staje się
liniowy.
### Drzewo czerwono-czarne

To rodzaj samoorganizującego się binarnego drzewa poszukiwań. z każdym węzłem powiąza-
ny jest dodatkowy atrybut, kolor, który może być czerwony lub czarny. Oprócz podstawowych
własności drzew poszukiwań binarnych, wprowadzone zostały kolejne wymagania, które trze-
ba spełniać:
1. Każdy węzeł jest czerwony albo czarny.
2. Korzeń jest czarny.
3. Każdy liść jest czarny i nie przechowuje żadnego klucza ani wartości.
4. Jeśli węzeł jest czerwony, to jego synowie muszą być czarni.
5. Każda ścieżka z ustalonego węzła do każdego z jego potomków będących liśćmi liczy tyle
samo czarnych węzłów.
Dzięki tym właściwościom, drzewo czerwono-czarne utrzymuje względną równowagę, co prze-
kłada się na efektywność operacji. Wyszukiwanie, wstawianie i usuwanie w drzewie czerwono-
czarnym mają złożoność czasową O(log n), gdzie n to liczba węzłów w drzewie.
Drzewa czerwono-czarne wymagają nieco więcej pamięci niż proste drzewa BST ze względu
na konieczność przechowywania informacji o kolorze węzłów. Każdy węzeł drzewa czerwono-
czarnego musi przechowywać dodatkowy bit informacji o kolorze, co może prowadzić do
nieznacznego wzrostu zużycia pamięci w porównaniu do drzew BST.
Drzewa czerwono-czarne są powszechnie stosowane w implementacjach struktur danych, ta-
kich jak mapy i zestawy, ze względu na swoją wydajność i zrównoważoną strukturę

## Badania dla losowych zestawów danych
![BST_losowe](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/fd178cf1-b3a2-4222-b719-fa8d0cd68aad)
![RB_losowe](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/742f0ad2-554f-4782-9831-b9b3ce4a7e78)

## Badania dla uporządkowanych zestawów danych
![BST_kolejne](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/65e9fe7c-fc12-4cd7-ac1a-8e46106e16db)
![RB_kolejne](https://github.com/MateuszAmbrozy/Comparison_RBTree_and_BSTTree/assets/127397482/e09843c3-6a5f-4e68-a311-57cea5dbf755)

## Wnioski

Drzewa czerwono-czarne są bardziej wydajne niż proste drzewa BST...

---

## Spis rysunków

1. Drzewo BST - wartości losowe.
2. Drzewo czerwono-czarne - wartości losowe.
3. Drzewo BST - wartości uporządkowane.
4. Drzewo czerwono-czarne - wartości uporządkowane.
