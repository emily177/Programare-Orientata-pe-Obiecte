# Proiect POO (Cerința 1)

<br>Nume proiect: Aplicatie biblioteca
<br>Tema: Biblioteca
<br> Clasele implementate:
<ol>
	<li> Data: este o clasa folosita doar pentru a ne usura memorarea datelor calendaristice din celelate clase </li>
	<li> Perioada: foloseste elemente de tip Data si le transforma in perioada inceput si perioada sfarsit. Tot pentru usurinta memorarii datelor din celelate clase </li>
	<li> Vector_carti: este o clasa ce contine un vector de string-uri alocat dinamic.In clasa avem un destructor netrivial, o metoda pentru afisare,un constructor de copiere si o metoda pentru supraincarcarea operatorului = </li>
	<li> Autor: in aceasta clasa folosim un obiect de tip Vector_carti pentru a memora cartile scrise de un anumit autor care se afla in biblioteca</li>
	<li> Editura: in ea avem implementat un constructor de copiere impreuna cu supraincarcarea operatorului =,plus metoda de afisare</li>
	<li> Carte: foloseste un obiect de tip Data, sunt implementati setteri si getteri corespunzatori si se face afisarea prin supraincarcarea operatorului "<<" </li>
	<li>Abonamente: foloseste un obiect de tip Perioada pe langa altele. Avem in ea un constructor cu parametrii si unul fara parametrii. Este implementata o metoda de tip "logica business" care calculeaza o anumita reducere pentru abonametul platit </li>
	<li>Imprumuturi: Aceasta clasa este afisata prin supraincarcarea operatorului "<<".Are metode de tip set si get si contine o metoda de tip "logica business". Aceasta consta in verificarea returnarii unei carti de catre un anumit abonat.Daca a fost returnata se afiseaza un mesaj sugestiv si se calculeaza daca a fost returnata la timp sau nu. In cazul in care nu a fost, se afiseaza cate zile a avut intarziere. Daca nu a fost returnata deloc, se afiseaza cate zile,luni sau ani au trecut de cand a fost imprumutata pana in data curenta rularii programului.</li>
	
</ol>
<br>Functionalitati:
<ul>
	<li>Capabila sa afiseze clasele initializate </li>
	<li>Contine un meniu interactiv in partea de main prin care se pot verifica toate functiile claselor</li>
	<li>are o metoda pentru aplicarea reducerilor la abonamente si una pentru verificarea cartilor returnate dupa imprumut</li>
	<li>sunt implementate toate functiile cerute in cerinta< /li>
</ul>

