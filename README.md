# Monitor dla środowisk rozproszonych (in Polish) #

## Wymagania ##

* MPI w wersji posiadającej wsparcie dla wielowątkowości na poziomie MPI_THREAD_MULTIPLE (np. MPICH 3.2 gwarantuje takie wsparcie)
* Biblioteka pthread

## Kompilacja i uruchamianie ##

By skompilować projekt należy wywołać polecenie `make`. Do uruchamiania programu można skorzystać z komendy `mpiexec` lub `mpirun`. 

Chcąc pokazać w jaki sposób można wykorzystać stworzony przeze mnie monitor zaimplementowałem bardzo proste rozwiązanie problemu producenta i konsumenta, dlatego najlepiej uruchamiać program dostępny w tym repozytorium dla co najmniej dwóch procesów.
Chciałbym też zaznaczyć, że w prezentowanym przykładzie moim celem było wyłącznie pokazanie jednego ze sposobów wykorzystania stworzonego przeze mnie monitora i zdaję sobie sprawę, że do tego przykładu można wprowadzić pewne optymalizacje.

## Komponenty projektu ##

### Monitor ###
Z punktu widzenia użytkownika stworzonej przeze mnie biblioteki, najważniejszą klasą jest `monitor`. Za jego pomocą programista może bezpośrednio usypiać proces lub budzić pozostałe oraz wykonywać akcje wymagające wyłączngo dostępu do zasobów. 

Aby utworzyć obiekt klasy `monitor`, należy przekazać do konstruktora wskaźniki na obiekty klasy `synchronizer` oraz `resources_synchronizer` (ich działanie jest wyjaśnione w dalszej częsći tego dokumentu). Należy także nadać identyfikator sekcji krytycznej chronionej nowo tworzonym monitorem. 

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact