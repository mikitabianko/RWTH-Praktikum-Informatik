In this project, all function outputs are written as comments at the end of the functions.

---

# Aufgabenblock 1

## Motivation

In diesem ersten Aufgabenblock werden Klassen für die zu simulierenden Fahrzeuge erstellt, PKWs und Fahrräder, die sich selbst fortbewegen können und simulierbar sind. Ein Mini-Eventhandler ruft eine entsprechende Simulationsschrittmethode aller Fahrzeuge mehrmals auf und gibt den aktuellen Stand der Fahrzeuge nach jedem Schritt auf dem Bildschirm aus.

In diesem Aufgabenblock werden folgende Punkte betrachtet:
- Deklaration und Definition von Klassen,
- Implementierung von Konstruktoren und Destruktoren,
- Kapselung von Daten und Zugriﬀ auf private Member,
- Elementare Verwendung von Smartpointern und static Variablen,
- Vererbung,
- Einsatz der STL (string, vector),
- Unterscheidung der Klassenbereiche public, private und protected,
- Unterscheidung einfache und virtuelle Vererbung,
- Überladen von Operatoren.

***Um sich einen Überblick zu verschaffen, lesen Sie den ersten Aufgabenblock zunächst komplett durch.***

## Fahrzeuge (Einfache Klassen)
- [x] 1. Starten Sie Eclipse und erstellen Sie in Ihrem Homebereich ein neues Projekt mit dem Namen Aufgabenblock_1.
- [x] 2. Andern Sie den C++-Dialekt Ihres Projektes auf C++-17. Dazu klicken Sie mit der rechten Maustaste auf Ihr Projekt und wählen ”Properties” aus. Hier wählen Sie nun ”C/C + + Build →Settings” aus. Auf der rechten Seite wählen Sie nun den Reiter ”Tool Settings”. Hier öﬀnen Sie nun ”GCC C + + Compiler → Dialect”. Im rechten Bereich wählen Sie nun unter ”Language standard” ”ISO C++ 17 (-std=c++17)”.
- [x] 3. Implementieren Sie eine Klasse *Fahrzeug* zur Verwaltung verschiedener Fahrzeuge. Die Klasse soll zunächst lediglich private Membervariablen haben, in denen der Name des Fahrzeugs (p_sName) und eine eindeutige ID (p_iID) zu jedem Objekt gespeichert wird. Benutzen Sie für den Namen den Datentyp string. Implementieren Sie einen Konstruktor, der einen string als Parameter hat und damit den Namen initialisiert. Weiterhin soll die Klasse mit einem Default-Konstruktor konstruierbar sein. Dann soll der Name leer (””) sein. Zum Initialisieren der Variablen können Sie diese direkt bei der Definition mit 0 bzw. ”” vorbesetzen. Die ID soll im Konstruktor anhand einer hochzählenden, Klassenvariablen p_iMaxID vergeben werden. Nutzen Sie im Konstruktor eine Initialisierungsliste, um die Konstanten einmalig mit einem Wert zu besetzen. Da sich die ID nach der Konstruktion nicht mehrändert, können Sie diese als constdefinieren. Wie Sie Klassenvariablen definieren, können Sie im Skript (Statische Klassenelemente) nachlesen. 
   Erzeugen Sie in den Konstruktoren und dem Destruktor eine Ausgabe, welche den Namen und die ID des erzeugten bzw. gelöschten Objekts mit einem entsprechenden Hinweis auf die Operation auf der Standardausgabe cout ausgibt. 
   Für das weitere Programm setzen Sie da, wo Sie können, Variablen und Funktionen bevorzugt const.
- [x] 4. Beim Programmieren ist es meist ratsam, schnell ein laufähiges Programm zu haben. Erzeugen Sie eine neue C++-Datei (main.cpp), die die Funktion vAufgabe_1() aufruft und implementieren Sie diese Funktion innerhalb der Datei main.cpp. Erzeugen Sie in dieser Funktion einige Elemente statisch (über Deklaration) und einige dynamisch (mit new). Löschen Sie zum Schluss die dynamisch erzeugten Elemente. Erzeugen und starten Sie das Programm und testen Sie das korrekte Erzeugen und Löschen der Objekte. Im Anschluss erzeugen Sie nun einige Smartpointer (siehe Skript). Benutzen Sie dazu `make_unique<Fahrzeug>` und `make_shared<Fahrzeug>`, um von beiden Typen je 2 Objekte vom Typ Fahrzeug zu erzeugen. Speichern Sie eines der als shared ptr erzeugten Objekte in einem weiteren shared_ptr. Lassen Sie sich vor und nach der Zuweisung mit use_count die Anzahl der Referenzen ausgeben. Versuchen Sie dasselbe mit unique_ptr. Erzeugen Sie zusätzlich einen `vector<unique_ptr<Fahrzeug>>`. Speichern Sie die oben erzeugten Fahrzeuge in diesem Vektor. Welche Fahrzeuge können Sie dort speichern? Wie müssen Sie den Besitzwechsel anzeigen? Löschen Sie danach den Vektor mit clear. Beobachten Sie mit dem Debugger, was dort passiert und wann die Objekte durch Aufruf des Destruktors gelöscht werden. 
   Erzeugen Sie nun zusätzlich auch einen `vector<shared_ptr<Fahrzeug>>`. Welche Fahrzeuge können Sie dort speichern? Fügen Sie dem Vektor zwei Fahrzeuge hinzu, eins mit und eins ohne move. Lassen Sie die Anzahl der Referenzen ausgeben. Beobachten Sie wieder mit dem Debugger, was dort passiert und wann die Objekte durch Aufruf des Destruktors gelöscht werden. Bitte notieren Sie beim Debuggen, in welchen Zeilen die jeweiligen Objekte gelöscht werden. Machen Sie sich in dieser Aufgabe mit den Grundfunktionen des Debuggers (Schrittmöglichkeiten, Haltepunkte) bekannt. Beobachten Sie im Fenster für die Variablenüberwachung den Inhalt der Variablen. Die Benutzung des Debuggers wird im Skript beschrieben. Die Funktionen des Debuggers müssen bei der Abnahme ggf. vorgeführt und erläutert werden.
- [x] 5. Erweitern Sie die Klasse um Membervariablen für die Maximalgeschwindigkeit des Fahrzeugs (p_dMaxGeschwindigkeit), die bisher zurückgelegte Gesamtstrecke (p_dGesamtStrecke), die gesamte Fahrzeit des Objektes (p_dGesamtZeit) und die Zeit, zu der das Fahrzeug zuletzt simuliert wurde (p_dZeit). Fügen Sie einen weiteren Konstruktor hinzu, der einen Namen und die maximale Geschwindigkeit als Parameter bekommt. Beachten Sie hier, dass die Geschwindigkeit immer positiv sein soll. Prüfen Sie dies in der Initialisierungsliste mit Hilfe des ?-Operators.
- [x] 6. Da dieses Programm noch nicht viel am Bildschirm ausgibt, schreiben Sie eine Memberfunktion vAusgeben(). Diese Memberfunktion soll spezifische Fahrzeugdaten ausgeben. Machen Sie innerhalb dieser Funktion keine Aufrufe von cout::endl, sondern programmieren Sie die Zeilenwechsel in der Hauptfunktion. Die Ausgabe soll so formatiert werden, dass unter einer Uberschrift die Daten tabellarisch aufgelistet werden, in etwa folgendermaßen:

   | ID  | Name  | MaxGeschwindigkeit | Gesamtstrecke |
   | --- | ----- | ------------------ | ------------- |
   | 1   | PKW1  | 40.00              | 0.00          |
   | 2   | AUTO3 | 30.00              | 0.00          | 

   Die Überschrift soll durch eine Klassenfunktion void vKopf() ausgegeben werden. Benutzen Sie für die Formatierung keine feste Anzahl von Leerzeichen, sondern die Input-Output-Manipulatoren der Standard C++ Bibliothek (`<iomanip>`). Schreiben Sie eine Klassenfunktion in Fahrzeug, um mit Fahrzeug::vKopf() die Überschrift ausgeben zu können. Beachte: Bei Verwendung von setiosflags() zum Setzen der Ausgabeausrichtung (rechts-/linksbündig) sollte zunächst die andere Ausrichtung mittels resetiosflags() zurückgesetzt werden.
- [x] 7. Bevor die Simulationsfunktion der Fahrzeuge geschrieben werden kann, muss erst noch eine globale Uhr programmiert werden, damit die Fahrzeuge wissen, wie viele Stunden sie simulieren sollen. Zur Realisierung dieser Uhr definieren Sie eine globale Variable dGlobaleZeit, die Sie mit 0.0 initialisieren. 
   **Beachte**: Zur Benutzung dieser Variablen innerhalb anderer Klassen muss sie der Klasse erst mittels der extern-Deklaration bekannt gemacht werden.
- [x] 8. Schreiben Sie nun die Memberfunktion Fahrzeug::vSimulieren(), welche dafür sorgt, dass die Fahrzeuge sich fortbewegen. Dazu wird mit Hilfe der globalen Uhr ermittelt, wieviel Zeit seit dem letzten Simulationsschritt vergangen ist, und entsprechend dieser Information wird der Zustand des Fahrzeugs aktualisiert (u.a. Gesamtstrecke um die im ermittelten Zeitraum aufgrund der Geschwindigkeit fahrbare Strecke erhöhen). Lassen Sie das Fahrzeug mit maximaler Geschwindigkeit fahren. Sorgen Sie durch einen Zeitvergleich dafür, dass ein Fahrzeug in einem Zeitschritt nur einmal bearbeitet wird, auch wenn es versehentlich zweimal innerhalb eines Zeitschritts aufgerufen wird. Aktualisieren Sie auch die Gesamtfahrzeit und die letzte Abfertigungszeit des Objektes. Momentan sind diese Werte noch gleich. Das wird sich später ändern.
- [x] 9. Schreiben Sie eine neue Hauptfunktion vAufgabe_1a(). Lesen Sie Namen und Maximalgeschwindigkeit für 3 Fahrzeuge aus der Konsole ein, erzeugen Sie diese mit `make_unique<Fahrzeug>` und speichern sie diese in einem Vektor. Simulieren Sie Fahrzeuge über eine gewisse Zeitspanne. Erhöhen Sie dazu in einer Schleife die globale Uhr jeweils um einen Zeittakt und rufen Sie in der Schleife die Simulationsfunktion und die Ausgabefunktion der Fahrzeuge auf. Wählen Sie als Zeittakt auch Bruchteile von Stunden.
## 4.3 Fahrräder und PKW (Unterklassen)
- [x] 1. Implementieren Sie zwei neue Klassen PKW und Fahrrad, die jeweils von der Basisklasse Fahrzeug abgeleitet werden. Strukturieren Sie die Klasse Fahrzeug dementsprechend um. Überlegen Sie, welche Variablen private bleiben sollten und welche protected werden. Überlegen Sie weiterhin, welche Funktionen virtual werden. Benutzen sie synchron dazu das Schlüsselwort overridefür diese Funktionen in den abgeleiteten Klassen. Überlegen Sie zusätzlich welche Funktionen und/oder Variablen Sie const setzen können.
- [x] 2. Da Fahrräder mit Muskelkraft und PKWs mit Motoren betrieben werden, benötigt die Klasse PKW zusätzliche PKW-spezifische Variablen. Fügen Sie der Klasse PKW die Variablen p_dVerbrauch (Liter/100km), p dTankvolumen sowie p_dTankinhalt (Liter) hinzu. Ergänzen Sie die Klasse um einen entsprechenden Konstruktor, mit dem Sie zusätzlich zu den fahrzeugspezifischen Membervariablen auch Verbrauch und (optional, Default=55 l) Tankvolumen setzen können. Der Tankinhalt wird jeweils auf die Hälfte des Tankvolumens initialisiert. Nutzen Sie für die Einbeziehung der Konstruktoren der Basisklasse eine Initialisierungsliste.
   
   Des Weiteren schreiben Sie eine Funktion dTanken mit optionalem Parameter dMenge zum nachträglichen Betanken der PKWs. Wird kein Wert übergeben 154 Aufgabenblock 1: Grundlagen des Verkehrssystems (Defaultparameter) soll vollgetankt werden, ansonsten wird der gewünschte Wert getankt. Sie können die Konstante std::numeric `limits<double>::infinity()` aus dem Header`<limits>` als Default-Wert verwenden, die größer als alle (anderen) doubleWerte ist. Beachten Sie, dass maximal das Tankvolumen aufgefüllt werden kann. Geben Sie jeweils die tatsächlich getankte Menge zurück. Implementieren Sie die Funktion in der Klassenhierarchie so, dass sie für alle Fahrzeuge aufrufbar ist. Fahrräder und Fahrzeuge ohne Tank tanken bekanntlich nicht, d.h. die Funktion macht nichts und gibt immer 0 Liter zurück. 
   
   Bei jedem Simulationsschritt soll der Tankinhalt aktualisiert werden, bis der Tank leer ist. PKWs ohne Tankinhalt sollen liegenbleiben bis wieder nachgetankt wird. Danach sollen sie normal weiterfahren. Zur Vereinfachung soll die Reserve so groß sein, dass der PKW im letzten Schritt noch die komplette Teilstrecke fahren kann. Implementieren Sie dazu für PKW eine eigene Funktion vSimulieren(), die die zusätzliche Funktionalität von PKW implementiert. Für die allgemeine Simulation soll aber weiterhin Fahrzeug::vSimulieren() aufgerufen werden. Gesamtverbrauch (berechnet aus Gesamtstrecke) und aktueller Tankinhalt sollen außerdem noch in vAusgeben ergänzt werden. Beachte: Um Codeduplizierung in den abgeleiteten Klassen zu vermeiden, sollen die Daten, die zu Fahrzeuggehören, immer von Fahrzeug::vAusgeben ausgegeben werden. Rufen Sie diese Funktion also auch in den Ausgabefunktionen der abgeleiteten Klassen auf. Ergänzen Sie auch die Überschrift in Fahrzeug::vKopf() entsprechend.
- [x] 3. Da Fahrradfahrer nicht immer mit maximaler Geschwindigkeit fahren können, soll eine Memberfunktion dGeschwindigkeit() implementiert werden. Sie wird in Fahrzeug als virtuell deklariert und für Fahrrad überschrieben. PKWs sollen immer mit ihrer vollen Geschwindigkeit fahren, Fahrradfahrer dagegen werden langsamer. Jeweils ausgehend von der gefahrenen Gesamtstrecke soll die Geschwindigkeit pro 20km um 10% abnehmen, minimal jedoch 12km/h betragen. Während eines Berechnungsschritts ist die Geschwindigkeit als konstant anzusehen. Beispiel: Nach 50 gefahrenen Kilometern beträgt die Geschwindigkeit im nächsten Zeittakt noch 81% der Maximalgeschwindigkeit, falls diese noch mehr als 12km/h beträgt. Stellen Sie nun Fahrzeug::vSimulieren() auf diese Funktionalität um (statt Maximalgeschwindigkeit). Andern Sie die Methode vAusgeben, sodass für jedes Fahrzeug zusätzlich zu den Fahrzeugdaten die aktuelle Geschwindigkeit ausgegeben wird.
- [x] 4. Schreiben Sie eine neue Funktion vAufgabe_2(): Lesen Sie die Anzahl der zu erzeugenden PKWs und Fahrräder aus der Konsole ein, konstruieren Sie entsprechende Objekte der Klassen PKW und Fahrradund verwalten Sie sie in einem `vector<unique_ptr<Fahrzeug>>` Warum können/sollten Sie keine Fahrzeugobjekte speichern? Warum können Sie PKWs und Fahrräder in einem gemeinsamen Vektor speichern? Führen Sie für diese Objekte mehrere Simulationsschritte durch. Nach genau 3 Stunden tanken Sie die PKWs nochmals voll. Die Zeitabfrage dazu soll im Testprogramm erfolgen, nicht innerhalb von dTanken(). Testen Sie dies mit verschiedenen Zeittakten. Geben Sie die Ergebnisse (Daten aller Fahrzeuge) nach jedem Schritt aus.
   
   Beachte: Gleichheit von double-Werten kann immer nur gegen eine Toleranz ϵ getestet werden, da Fließkomma-Berechnungen nicht komplett genau sind. Berechnen Sie dazu z.B. den Absolutbetrag der Diﬀerenz bei Gleichheit oder reduzieren Sie eine der Seiten des Vergleichs um ϵ bei ≥oder ≤. Die Funktion für den Absolutbetrag `std::fabs()` finden Sie in der Bibliothek `<cmath>`. Beachten Sie dieses Rundungsproblem bei allen weiteren Vergleichen zwischen Fließkomma-Werten.
## 4.4 Ausgabe der Objekte (Operatoren überladen)
- [x] 1. Am Ende dieser Aufgabe sollen Fahrzeuge mit dem Ausgabeoperator angezeigt werden können. Fahrzeug hat ja bereits eine Methode vAusgeben(). Diese Memberfunktion soll nun fahrzeugspezifische Daten auf dem übergebenen AusgabeStream ausgeben. Dazu ändern sie diese nun in eine virtuelle Methode vAusgeben(ostream&) const. Markieren Sie in allen Fahrzeug-Klassen die geerbte vAusgeben-Methode als override, falls noch nicht geschehen.
- [x] 2. Nun wollen wir Fahrzeug mit operator<<ausgeben können. Dazu müssen Sie den Ausgabeoperator überladen. Hier zur Erinnerung nochmal die Deklaration des Ausgabeoperators für eine Klasse X:
   ostream& operator<<(ostream& o, const X& x);
   Rufen Sie im Ausgabeoperator die vAusgeben-Methode mit dem übergebenen ostream auf.
   Beachte:
   Überladen Sie den Operator außerhalb der Klasse. Warum? Kommen Sie mit einer einzigen Definition für alle von Fahrzeug abgeleiteten Klassen aus? Verwenden Sie bitte keine friend-Deklaration.
- [x] 3. Testen Sie den Ausgabeoperator, indem Sie Fahrzeuge, PKWs und Fahrräder damit auf cout ausgeben: 
   Beispiel:
   std::cout << *aPKW << std::endl << *aFahrrad << std::endl;
   Verwenden Sie ab jetzt zur Ausgabe von Daten nur noch den <<-Operator.
- [x] 4. Überladen Sie in der Klasse Fahrzeug den Vergleichsoperator operator<(). Dieser soll den Wert true liefern, falls die bisher zurückgelegte Gesamtstrecke vom aktuellen Objekt kleiner als die vom Vergleichsobjekt ist.
- [x] 5. Verbieten Sie den Copy-Konstruktor, benutzen Sie hierzu delete. Überdenken Sie, wieso dies sinnvoll ist. Wo wird er implizit aufgerufen? Was bedeutet dies in diesem Szenario? Definieren Sie den Zuweisungsoperator (operator=()), so dass nur die Stammdaten (Daten die bei der Erstellung festgelegt werden) kopiert werden. Können Sie alle Daten kopieren? Was müssen Sie bei der ID beachten? Was würde passieren, wenn Sie keine eigene Definition des Operators erstellen würden? Was passiert, wenn Sie Elemente der Unterklasse zuweisen? Machen Sie sich den Unterschied zwischen Copy-Konstruktor und Zuweisungsoperator klar. Es geht hier nur um das prinzipielle Verständnis der Funktion des Zuweisungsoperators. Die genaue Implementierung des Zuweisungsoperators spielt für die weitere Aufgabe keine Rolle.
- [x] 6. Testen Sie alle in dieser Aufgabe neu erstellten Operatoren in einer Funktion vAufgabe_3().

# Aufgabenblock 2
## 5.1 Motivation

In diesem Aufgabenblock werden folgende Punkte betrachtet:

- Erweiterung einer Klassenhierarchie,
- abstrakte Klassen und rein virtuelle Methoden,
- Aufzählungsklasse,
- Unterscheidung und Nutzung `unique_ptr`, `shared_ptr`, `weak_ptr`,
- Templateklassen nutzen und erstellen,
- Exception handling und eigene Exceptionklassen,
- Nutzung einer externen Bibliothek,
- Erzeugung gleichverteilter Zufallszahlen.

In diesem zweiten Aufgabenblock wird die Klassenhierarchie um eine Klasse _Weg_ erweitert. Da diese Klasse einige Eigenschaften mit Fahrzeugen gemeinsam hat (Name, Simulationszeit, Simulationsfunktion, Ausgabefunktion usw.), ist es sinnvoll, die Klassenhierarchie um eine abstrakte Oberklasse zu erweitern und sowohl _Weg_, als auch _Fahrzeug_ von dieser Klasse abzuleiten. Die gemeinsamen Dienste werden dann in diese abstrakte Oberklasse verlagert. Beim letzten Aufgabenpunkt wird noch eine Klasse _Kreuzung_ eingeführt, die ebenfalls von der abstrakten Oberklasse abzuleiten ist. Dies ist eine bei objektorientierten Programmierung häufig auftretende Situation.

Ein Weg verwaltet eine Liste von Fahrzeugen und kann simuliert werden, indem alle auf dem Weg befindlichen Fahrzeuge simuliert werden.

Für die Berechnung der Strecke, die ein Fahrzeug in einem Simulationsschritt zurücklegt, wird eine neue Klasse erstellt, die ein Verhaltensmuster implementiert. Ein Verhaltensmuster ist ein Beispiel von einem Entwurfsmuster (_design pattern_). Jedes Fahrzeug besitzt eine Instanz dieser Klasse und kann in seinem Simulationsschritt diese Instanz fragen, wie weit es fahren darf. Auftretende Sondersituationen (parkendes Fahrzeug fährt los, fahrendes Fahrzeug kommt am Ende des Weges an) werden durch Ausnahmebehandlung (Exceptions) abgehandelt. Um die Simulation etwas anschaulicher zu machen, wird eine Bibliothek mit Funktionen zur grafischen Darstellung verwendet.

Oft wiederkehrende Datenstrukturen und Algorithmen können durch Templates allgemein beschrieben werden. Die _STL_ stellt eine Fülle solcher vorgefertigten Strukturen bereit. Einige davon sollen hier benutzt werden. Schließlich soll für eine spezielle Listenart (verzögerte Aktualisierung) ein eigenes Template erstellt werden.

**Um sich einen Überblick zu verschaffen, lesen Sie den zweiten Aufgabenblock zunächst komplett durch.**

## 5.2 Kopieren des Projektes

- [x] 1. Erzeugen Sie ein neues leeres Projekt mit dem Namen Aufgabenblock_2. Kopieren Sie alle Sourcen (nur *.h und *.cpp Dateien) aus Aufgabenblock_1 und machen Sie diese Dateien dem neuen Projekt bekannt (s. Kapitel 3.2.3).
- [x] 2. Ändern Sie den C++-Dialekt Ihres Projektes auf C++17. Dazu klicken Sie mit der rechten Maustaste auf Ihr Projekt und wählen "Properties" aus. Hier wählen Sie nun "_C/C++ Build -> Settings_" aus. Auf der rechten Seite wählen Sie nun den Reiter "Tool Settings". Hier öffnen Sie nun "_GCC C++ Compiler -> Dialect_". Im rechten Bereich wählen Sie nun unter "Language standard" "ISO C++ 17 (-std=c++17)".

## 5.3 Simulationsobjekte und Wege

- [x] 1. Als erstes soll eine neue abstrakte Oberklasse _Simulationsobjekt_ geschaffen werden, welche die gemeinsamen Eigenschaften von _Fahrzeug_ und einer neuen Klasse _Weg_ zusammenfasst. Fahrzeuge und Wege sind Simulationsobjekte, die einen Namen, eine ID und eine lokale Zeit besitzen. Sie können simuliert und ausgegeben werden. Integrieren Sie _Fahrzeug_ in diese neue Klassenhierarchie, indem Sie die Variablen für Name, ID und Simulationszeit sowie alle Funktionen zur gemeinsamen Nutzung von _Fahrzeug_ und _Weg_ aus der Klasse _Fahrzeug_ in die Klasse _Simulationsobjekt_ übertragen. Verschieben Sie die Ausgabe im Destruktor in die neue Klasse, um weiterhin das richtige Löschen der Objekte kontrollieren zu können. Löschen Sie die jetzt überflüssigen Variablen und Funktionen in _Fahrzeug_.
   
   Beachten Sie, dass die Variablen und Methoden in _Fahrzeug_ angepasst bzw. gelöscht werden müssen. _Simulationsobjekt_ ist eine abstrakte Klasse, besitzt also mindestens eine rein virtuelle Methode. Überlegen Sie, welche Funktion hierzu am besten geeignet ist. Welche Methoden/Variablen müssen _private_, _protected_ oder _public_ deklariert werden? Gibt es weitere Methoden, die virtuell oder rein virtuell deklariert werden können oder müssen? Verbieten Sie auch hier den Copy-Konstruktor, um fehlerhafte Elemente durch Kopien zu vermeiden. Wie müssen Sie den Zuweisungsoperator anpassen? Implementieren Sie einen Vergleichsoperator (`operator==()`), der genau dann _true_ liefert, wenn die IDs übereinstimmen.
   
   Um Codeduplizierung zu vermeiden, sollen bei der Ausgabe die entsprechenden vAusgeben-Methoden der übergeordneten Klassen mitbenutzt werden. So soll etwa vAusgeben in _Fahrrad_ zunächst die Methode von _Fahrzeug_ aufrufen, diese zunächst die Methode von _Simulationsobjekt_. `Simulationsobjekt::vAusgeben` soll nur die ID und den Namen des Objekts ausgeben. Aufgrund dieses Aufbaus reicht es für den Ausgabeoperator aus, diesen nur in der Klasse _Simulationsobjekt_ zu definieren. Dieses Prinzip gilt auch für die Konstruktoren: Die Konstruktoren sollten jeweils die passenden Konstruktoren der Oberklasse aufrufen und nur die eigenen Variablen der Klasse setzen. Der Aufruf des Konstruktors der Oberklasse erfolgt in einer Initialisierungsliste.
   
- [x] 2. Richten Sie die Klasse _Weg_ als Unterklasse von _Simulationsobjekt_ ein. Wege haben zusätzlich zu den geerbten Eigenschaften eine Länge in km (`p_dLaenge`), eine Liste von Fahrzeugen (`p_pFahrzeuge`), welche sich aktuell auf dem Weg befinden, und eine maximal zulässige Geschwindigkeit (`p_eTempolimit`). Die Liste beinhaltet `unique_ptr` auf Fahrzeuge. Zur Implementierung der Liste benutzen Sie den Container _list_ aus der _STL_.
   
   Es soll für Wege drei unterschiedliche Kategorien (Innerorts, Landstraße und Autobahn) mit unterschiedlichem Tempolimit ($50 km/h$, $100 km/h$ und Unbegrenzt) geben. Für die Autobahngeschwindigkeit können Sie die Konstante `std::numeric_limits<int>::max()` verwenden. Definieren Sie dazu in Tempolimit.h einen eigenen Datentyp _Tempolimit_ als Aufzählungsklasse (_enum class_) und eine Konvertierungsfunktion `getTempolimit` in _Weg_, die für `p_eTempolimit` die entsprechende Geschwindigkeit als _double_ zurückgibt.
   
   _Weg_ soll einen Standardkonstruktor und einen Konstruktor mit Namen und Länge des Weges, sowie optionalem Tempolimit (default unbegrenzt) als Parameter haben. Außerdem soll die Funktion `vSimulieren()` so implementiert werden, dass beim Aufruf alle auf dem Weg befindlichen Fahrzeuge simuliert werden. Setzen Sie hierzu eine Range-basierte Schleife ein, die über die gesamte _list_ iteriert.
   
   **Beachte:** Wenn zwei Klassen jeweils Variablen der anderen als Element enthalten (hier enthält ein Weg Instanzen der Klasse Fahrzeug), können Sie nicht in beiden Headerdateien jeweils die andere Headerdatei inkludieren, da dies zu einer Rekursion führen würde. Es reicht, in den Headerdateien jeweils die andere Klasse zu deklarieren, also einfach `class Fahrzeug;` bzw. `class Weg;` einzufügen. In den cpp-Dateien müssen aber dann die entsprechenden Headerdateien eingebunden werden, da dort die Methoden benötigt werden. Um allgemein Probleme mit zirkulären Abhängigkeiten (circular dependencies) in Headerdateien zu vermeiden, kann man meistens folgende Faustregel anwenden: Nur, wenn von einer Klasse geerbt wird, ist es notwendig die andere Header-Datei in der Header-Datei einzubinden. Bei allen anderen Klassen reicht in der Headerdatei eine Deklaration. Für cpp-Dateien gilt das nicht: Dort müssen alle benutzten Headerdateien eingebunden werden, um die Schnittstellen der Funktionen bereitzustellen.
   
   Implementieren Sie eine Funktion `vAusgeben` für _Weg_, damit der überladene Ausgabeoperator verwendet werden kann. Die Funktion soll die Implementierung von _Simulationsobjekt_ für ID und Name verwenden und selbst die Länge des Weges und in Klammern die Namen der auf dem Weg befindlichen Fahrzeuge ausgeben. Definieren Sie auch hier eine Klassenfunktion `vKopf()` zur Ausgabe einer Überschrift für Wege wie folgt:
    ```
    ID | Name           | Laenge  | Fahrzeuge
    -------------------------------------------
     0 weg              :    100  ( )
    ```
    
- [x] 3. Testen Sie Ihr altes Hauptprogramm. Es sollte noch unverändert funktionieren. In `vAufgabe_4()` testen Sie zusätzlich die neue Klasse _Weg_, indem Sie einen Weg erzeugen und ihn mit dem `<<`-Operator auf die Standardausgabe ausgeben.

## 5.4 Parkende und fahrende Fahrzeuge

- [x] 1. Damit man für ein Fahrzeug verschiedene Verhaltensweisen realisieren kann, wird die Klasse **Fahrzeug** um eine Membervariable `p_pVerhalten` erweitert, die eine Instanz der im Folgenden noch zu implementierenden Klasse **Verhalten** verwaltet. Durch Austausch dieses Objektes kann das Verhalten des Fahrzeugs verändert werden, ohne ein neues Fahrzeug erstellen zu müssen. Überlegen Sie, welche Art von Smartpointer für `p_pVerhalten` gewählt werden sollte.
   
   Unter Verhalten verstehen wir, dass zwischen fahrenden und parkenden Fahrzeugen unterschieden werden kann.
   
   Da das Verhalten u.a. vom jeweiligen Weg abhängt, bekommt die Klasse **Verhalten** einen Konstruktor, der eine Referenz auf einen **Weg** als Parameter bekommt und speichert. Weiterhin soll eine Funktion `double dStrecke(Fahrzeug& aFzg, double dZeitIntervall)` angeboten werden, die ermittelt, wie weit ein Fahrzeug innerhalb des übergebenen Zeitintervalls fahren kann, ohne das Wegende zu überschreiten. Die bisherige Berechnung der aktuellen Teilstrecke in `Fahrzeug::vSimulieren` wird durch den Aufruf der Funktion `dStrecke` ersetzt. Zum lesenden Zugriff auf private Variablen von Weg und Fahrzeug müssen ggf. neue Getter-Funktionen geschrieben werden. Beachten Sie, dass `dStrecke` in jedem Simulationsschritt nur einmal aufgerufen und das Zwischenergebnis lokal zwischengespeichert wird.
   
   Bei jedem Start eines Fahrzeugs auf einem neuen Weg soll nun eine Instanz von **Verhalten** erzeugt und in **Fahrzeug** gespeichert werden. Dies geschieht am besten durch eine neue Memberfunktion `Fahrzeug::vNeueStrecke(Weg&)`, die ein geeignetes Objekt erzeugt und in `p_pVerhalten` speichert. Was passiert mit der alten Instanz, wenn das Fahrzeug auf einen neuen Weg gesetzt wird? 
   
   ![image](https://github.com/mikitabianko/RWTH-Praktikum-Informatik/blob/master/assets/image1.png?raw=true)
   
   Da Fahrzeuge jetzt nacheinander auf verschiedenen Wegen fahren sollen, führen wir hier eine zusätzliche Membervariable `p_dAbschnittStrecke` in Fahrzeug ein. Diese speichert immer nur die auf dem aktuellen Weg zurückgelegte Strecke. Sie wird in gleicher Weise wie bisher `p_dGesamtStrecke` aktualisiert und beim Betreten des Weges auf 0 gesetzt. Fügen Sie diese Variable Ihren Berechnungen und Ausgaben für **Fahrzeug** hinzu. Die Variable `p_dGesamtStrecke` soll weiterhin gepflegt werden. 
   
   Da es zurzeit noch keine Einschränkungen für die Fahrzeuge gibt, soll die Funktion `dStrecke`, wie in Figure 5.1 gezeigt, die auf Grundlage der übergebenen Zeitspanne fahrbare Strecke zurückliefern, falls dadurch die Weglänge noch nicht überschritten wird ($dT_1 \dots dT_{n-1}$). Im Zeittakt $dT_n$ soll nur die bis zum Wegende verbleibende Strecke zurückgegeben werden, womit das Fahrzeug genau am Ende des Weges ankommt. Im letzten Zeittakt $dT_{n+1}$ wird dann erkannt, dass das Fahrzeug am Ende des Weges steht. Zunächst soll das Programm hier nur eine entsprechende Meldung ausgeben, dass es am Ende des Weges angekommen ist.

- [x] 2. Schreiben Sie nun eine Funktion `Weg::vAnnahme(unique_ptr<Fahrzeug>)`, die ein Fahrzeug auf dem Weg annimmt. Dazu muss es in die Liste der Fahrzeuge eingetragen werden. Da ein `unique_ptr` nicht kopiert werden kann, muss der Pointer auf das Fahrzeug mit `move` verschoben werden. Damit man die eingetragenen Fahrzeuge auch sehen kann, werden diese in Klammern an die Ausgabe des Weges angehängt. Weiterhin muss dem Fahrzeug signalisiert werden, dass es sich auf einer neuen Strecke befindet.
   **Beispiel:**
   ```
   ID | Name      | Laenge | Fahrzeuge
    -------------------------------------------------
    0 | weg       :    100 | ( BMW Audi BMX )
   ```
   
- [x] 3. Testen Sie Ihre neue Klasse in `vAufgabe_5()`, indem Sie einen Weg und drei Fahrzeuge erzeugen, diese auf den Weg setzen und den Weg simulieren.
   
- [x] 4. Der Simulation sollen nun parkende Fahrzeuge hinzugefügt werden. Parkende Fahrzeuge benötigen ein anderes Verhaltensmuster, da diese sich nicht fortbewegen. Erweitern Sie dazu die Klasse **Verhalten** zu einer Klassenhierarchie, wobei Sie zwei Klassen **Fahren** und **Parken** von **Verhalten** ableiten. 
   
   **Verhalten** soll als _abstrakte Oberklasse_ implementiert werden. **Fahren** soll funktionieren wie vorher **Verhalten**. Implementieren Sie daher für **Fahren** den Code nicht doppelt, sondern übernehmen diesen. Die Klasse **Parken** hat einen Konstruktor, der zusätzlich zum Weg den Startzeitpunkt des Fahrzeugs übergeben bekommt. `Parken::dStrecke()` liefert bis zum Erreichen des Startzeitpunktes den Wert 0.0 zurück. Wenn die Startzeit erreicht wurde, soll das Programm auch hier zunächst eine entsprechende Meldung ausgeben.
   
   Auf einem Weg sollen sich sowohl parkende als auch fahrende Fahrzeuge befinden können. Um beide zu unterscheiden, soll die Funktion `vAnnahme(unique_ptr<Fahrzeug>)` durch eine weitere Funktion `vAnnahme(unique_ptr<Fahrzeug>, double)` überladen werden. Bekommt sie nur einen Zeiger auf Fahrzeug als Argument, dann nimmt sie wie bisher ein fahrendes Fahrzeug an. Wird jedoch ein Zeiger auf Fahrzeug und eine Startzeit übergeben, nimmt sie ein parkendes Fahrzeug an. Alle Fahrzeuge sollen weiterhin zusammen in der vorhandenen Liste verwaltet werden. 
   
   Überladen Sie entsprechend auch die Funktion `Fahrzeug::vNeueStrecke`. Fügen Sie fahrende Fahrzeuge hinten in die Liste an, parkende Fahrzeuge vorne. Diese Eigenschaft werden wir später noch benötigen.
   
- [x] 5. Modifizieren Sie `vAufgabe_5` mehrfach so, dass das Programm beim Starten bzw. am Streckenende entsprechende Meldungen ausgibt. Alternativ können Sie dies auch mit Hilfe des Debuggers testen.
## 5.6 Grafische Ausgabe

- [ ] 1. Um die Simulation anschaulicher zu machen, soll sie nun grafisch dargestellt werden. Dazu wurde ein Client/Server-Modell entwickelt, bei dem der Server vom Client über TCP/IP Kommandos empfängt und diese dann in eine grafische Darstellung umsetzt.
   
   Die Grafikschnittstelle wird Ihnen durch die Klassen `SimuClient` und `SimuClientSocket` zur Verfügung gestellt. Der grafische Server wird über die Java-Datei `SimuServer.jar` zur Verfügung gestellt. Um die Grafikschnittstelle nutzen zu können, kopieren Sie zunächst die erforderlichen Dateien (`SimuClient.h`, `SimuClient.cpp`, `SimuClientSocket.h`, `SimuClientSocket.cpp`, `SimuServer.jar`) in Ihr Projektverzeichnis (Verzeichnis mit cpp/h-Dateien, z.B. _Aufgabenblock_2_) in Ihrem Eclipse-Workspace. Die Dateien finden Sie in den Vorgabedateien in Moodle.
   
   **Grafikschnittstelle**
   
   Die Funktionen der Grafikbibliothek arbeiten nur mit den übergebenen Werten, kennen also keine anderen Daten Ihres Projektes. Die Werte werden beim Aufruf aber auf syntaktische und semantische Plausibilität geprüft. Das bedeutet:
   
   - a) Zahlenwerte müssen in einem sinnvollen Wertebereich liegen.
   - b) Die Namen dürfen nur Buchstaben, Ziffern und _ enthalten, insbesondere keine Leerzeichen.
   - c) Fahrzeuge können nur auf Straßen gezeichnet werden, die vorher durch zwei Wege definiert wurden.
   
   Die Grafikschnittstelle stellt folgende Funktionen zur Verfügung:
   - **`bInitialisiereGrafik(int GroesseX, int GroesseY);`** Mit dieser Funktion stellen Sie eine Verbindung zum Grafikserver her und initialisieren die Größe des Fensters. Die Variablen _GroesseX_ und _GroesseY_ bestimmen die Größe der Grafikdarstellung. Verwenden Sie hier z.B. folgende Werte: `GroesseX=800; GroesseY=500`. `bInitialisiereGrafik(800, 500);`
   - **`vSetzeZeit(double Zeit)`** Mit dieser Funktion können Sie die globale Zeit in der Titelzeile des Ausgabefensters anzeigen lassen.
   - **`bZeichneStrasse(string NameHin, string NameRueck, int Laenge, int AnzahlKoord, int[] Koordinaten)`** Diese Funktion zeichnet eine Straße, die aus den beiden durch ihren Namen identifizierten Wegen besteht. Die Straße soll mit einer Reihe von Koordinaten dargestellt werden. Der Verlauf der Straße wird durch einen Polygonzug mit mindestens 2 Punkten (Gerade) skizziert. Die Koordinaten der Polygonpunkte werden im Array _Koordinaten_ übergeben. Das Array enthält _AnzahlKoord_ X/Y-Paare. Für eine gerade Straße benutzen Sie für Koordinaten z.B. die Werte `{ 700, 250, 100, 250 }`.
   **Beachte:**
	   - a) Achten Sie darauf, dass die X-/Y-Koordinatenwerte innerhalb der vorher definierten (`bInitialisiereGrafik()`) Grenzen liegen.
	- b) Das Array muss genau (2 x AnzahlKoord) int-Elemente enthalten.
	- c) Diese Funktion darf für jede Straße nur einmal aufgerufen werden.
	- **`bZeichnePKW(string PKWName, string WegName, double RelPosition, double KmH, double Tank)`**
	- **`bZeichneFahrrad(string FahrradName, string WegName, double RelPosition, double KmH)`** Diese Funktionen zeichnen jeweils eine symbolische Darstellung des PKW/Fahrrads auf dem durch seinen Namen identifizierten Weg. Die relativ zur Weglänge zurückgelegte Strecke (Wert zwischen 0 und 1) wird mit _RelPosition_ angegeben. Dem Parameter _KmH_ wird der Wert aus der Funktion `dGeschwindigkeit()` und dem Parameter _Tank_ der aktuelle Tankinhalt übergeben.
	- **`BeendeGrafik()`** Mit dieser Funktion wird die Verbindung zum Grafikserver getrennt, das Fenster wird automatisch geschlossen.
	- **`void vSleep(int zeit_ms);`** Mit dieser Funktion wird die weitere Programmausführung um _zeit_ms_ Millisekunden verzögert.

- [ ] 2. Erweitern Sie `vAufgabe_6()` so, dass die Grafikausgabe getestet werden kann. Fügen Sie den Header `SimuClient.h` in Ihrer `main.cpp` ein. Wählen Sie als Länge der beiden Wege jeweils 500km und fassen Sie diese grafisch zu einer Straße zusammen (Hin- und Rückweg).
   
- [ ] 3. Um beim Zeichnen, abhängig vom Fahrzeugobjekt-Typ, die korrekte Zeichenfunktion aufzurufen, soll für PKW und Fahrrad eine Funktion `vZeichnen(const Weg&)` implementiert werden. Dazu wird in **Fahrzeug** die Funktion virtuell deklariert und in der jeweiligen Unterklasse überschrieben. Die Funktion bekommt den Weg, auf dem das Fahrzeug gezeichnet werden soll, als Referenz übergeben und ruft dann die passende Zeichenfunktion (s.o.) auf.
   
- [ ] 4. Lassen Sie die Fahrzeuge nach jeder Simulation in Weg zeichnen.
   
- [ ] 5. Führen Sie Ihre Simulation aus. Um die Simulation besser verfolgen zu können, rufen Sie die Funktion `vSleep` in Ihrer Schleife auf. Je nach Rechenleistung des verwendeten Computers können Sie die Verzögerung anpassen (100ms).