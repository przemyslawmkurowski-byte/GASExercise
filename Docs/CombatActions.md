# Akcje Podstawowe w Fabuli Ultimie i plan ich implementacji za pomocą GAS

## Akcje pomniejsze

Zignorować. Takie drobiazgi muszą być ujęte w mechanikę ttrpg, ale w jrpg nie mają znaczenia.

## Atak

1. Wybierz akcję Ataku
2. Wybierz jedną z wyekwipowanych broni, albo walkę oburącz.
3. Wybierz cele spośród obecnych w walce przeciwników. Musisz wybrać co najmniej jeden cel, ale nie więcej niż 2(dla walki oburącz), x (dla broni z tagiem Wieloataka(x)) lub 1 (w pozostalych przypadkach).
4. Rozlicz Accuracy check i obrażenia, w oparciu o dane wyciągnięte z broni

### Dlaczego nie obsłużyć każdej broni jako oddzielnej ability?

Bo wiele skillów (a te z konieczności będą Ability) korzysta z accuracy i damage signature broni. Innymi słowy, i tak musimy mieć krotkę broni, która będzie te dane przechowywała.

### Jak zaimplementować broń?

W pierwszej iteracji jako DataAsset. W drugiej iteracji jako struktura przechowująca DataAsset i modyfikacje, np. z zaklęcia Zaklęta Broń.

Każda postać może mieć do dwóch broni. W pierwszej iteracji ignorujemy pancerz, tarczę i możliwość walki gołymi pięściami.

## Cel

Na razie zignorować.

## Ekwipunek

Na razie będzie to grupa trzech Abilities (eliksir, mikstura, tonik). Ich Kosztem jest nowy Atrybut (Punkty Ekwipunku)

1. Wybierz akcję Ekwipunku
2. Wybierz z submenu konkretny przedmiot
3. Wybierz cel
4. Rozlicz efekty (bez rzutu).

## Obrona

Zaimplementowana. Na razie zostawić, jak jest.

## Wyposażenie

Na razie zignorować. To bardzo nietypowa akcja, afaik bez precedensu w jrpg. Wymagająca stworzenia całego systemu wyposażenia.

## Zwód

Zignorować. To nietypowa umiejętność, mocno pokywająca się ze Skillami i Zaklęciami. W ttrpg ma sens, bo w ttrpg trzeba mechanicznie wyrazić wszystkie potencjalne sposoby na utrudnenie przeciwnikowi życia, w jrpg jest to raczej niepotrzebne.

## umiejętność

Złożone. Na razie przyjąć, że Skill == Ability

## Zaklęcie

Złożone. Na razie przyjąć, że Spell = Ability.