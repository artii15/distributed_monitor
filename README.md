# Monitor dla środowisk rozproszonych (in Polish) #

## Wymagania ##

* MPI w wersji posiadającej wsparcie dla wielowątkowości na poziomie MPI_THREAD_MULTIPLE (np. MPICH 3.2 gwarantuje takie wsparcie)
* Biblioteka pthread

## Kompilacja i uruchamianie ##

By skompilować projekt należy wywołać polecenie `make`. Do uruchamiania programu można skorzystać z komendy `mpiexec` lub `mpirun`. 

Chcąc pokazać w jaki sposób można wykorzystać stworzony przeze mnie monitor zaimplementowałem bardzo proste rozwiązanie problemu producenta i konsumenta, dlatego najlepiej uruchamiać program dostępny w tym repozytorium dla co najmniej dwóch procesów.
Chciałbym też zaznaczyć, że w prezentowanym przykładzie moim celem było wyłącznie pokazanie jednego ze sposobów wykorzystania stworzonego przeze mnie monitora i zdaję sobie sprawę, że do tego przykładu można wprowadzić pewne optymalizacje.

## Komponenty projektu ##

### monitor ###
Z punktu widzenia użytkownika stworzonej przeze mnie biblioteki, najważniejszą klasą jest `monitor`. Za jego pomocą programista może bezpośrednio usypiać proces lub budzić pozostałe oraz wykonywać akcje wymagające wyłączngo dostępu do zasobów. 

Aby utworzyć obiekt klasy `monitor`, należy przekazać do konstruktora wskaźniki na obiekty klasy `synchronizer` oraz `resources_synchronizer` (ich działanie jest wyjaśnione w dalszej częsći tego dokumentu). Należy także nadać identyfikator sekcji krytycznej chronionej nowo tworzonym monitorem. 

Instrukcje, które ma wykonać monitor należy wywołać za pomocą metody `call`. Występuje ona w dwóch wersjach.
Najprostsza jako parametr przyjmuje wskaźnik na funkcję typu `void (*)(monitor*)`. Do tej funkcji zostaje przekazany wskaźnik na monitor wykonujący metodę `call`. 
Druga wersja przyjmuje wskaźnik na dowolny obiekt dziedziczący po klasie `Action`.

### synchronizer ###
Klasa ta jest odpowiedzialna za obsługę komunkatów zawierających żądania do sekcji krytycznych, informacje o przejściu procesu w stan uśpienia, czy komunikatów mających na celu obudzenie jednego z oczekujących procesów.
W programie powinien być utworzony jeden obiekt tej klasy, a następnie wskaźnik na ten obiekt powinien zostać przekazany do każdego z tworzonych w programie monitorów.


### resources_synchronizer ###
Klasa ta jest odpowiedzialna za obsługę komunkatów zawierających zaktualizowane wersje zasobów. Podobnie jak w przypadku klasy `synchronizer`, w programie powinna występować tylko jedna instancja obiektu tej klasy.

### communicator ###
Celem tej klasy jest odbieranie komunikatów od innych procesów. Odebrane komunikaty przekazywane są do obiektów takich jak `synchronizer`, czy `resources_synchronizer`. Pozwala ona także na wysyłanie komunikatów. Część metod tej klasy, to metody czysto wirtualne. Klasa ta pozwala także uniezależnić główne komponenty projektu od konkretnego mechanizmu dostarczającego wiadomości, pozostawiając ostateczny wybór użytkownikowi tej biblioteki. W źródłach projektu dostarczyłem klasę `mpi_communicator` implementującą metody czysto wirtualne za pomocą biblioteki MPI. Jednak nic nie stoi na przeszkodzie, by programista korzystający ze stworzonej przeze mnie biblioteki utworzył własną klasę dziedziczącą po klasie `communicator` i wykorzystał inny mechanizm niż MPI. 
W tym miejscu chciałbym jeszcze zaznaczyć, że do poprawnego działania poszczególnych klas odpowiedzialnych za synchronizację, konieczne jest, by mechanizm który chce wykorzystać programista zapewniał kanały FIFO.

### resources ###
Klasa ta służy do opakowania zasobów chronionych monitorem. Klasy dziedziczące po `resources` powinny implementować metody do serializacji własynch pól, dodanych przez programistę. Powinny one także ustawiać flagę `is_dirty` określającą, czy zasoby zostały zmodyfikowane. Na potstawie tej flage `resources_synchronizer` decyduje czy konieczne jest przesłanie zaktualizowanej wersji zasobów.