**Dumitru Bianca Stefania**
**322CA**
 
# Tema #2 - Analiza Algorimilor - Octavian's Saga
  
## Task1 - trial:
 
- Pentru a rezolva k-set cover, am inceput prin a cauta un set de clauze pornind de
la cele oferite pentru vertex cover in enunt. Am folosit si eu variabila y(i,r) cu
semnificatia y(i,r) este adevarata daca setul i este al r-lea din acoperire.

- Primele 3 clauze sunt identice cu cele de la vertex cover, in schimb a 4-a difera:
pentru fiecare t (1 <= t <=N), y(i1, r) | y(i2, r) | ... | y(ih, r), unde 1 <= r <= K
si ik este al k-lea subset care contine elementul t.

- Aceasta clauza forteaza ca pentru fiecare intreg de la 1 la N, existain cel putin 
o submultime in acoperire care il contine.

- Am codificat variabila y(i,r) pentru formatul cnf ca fiind ((i - 1) * K + r) * mul,
unde "mul" poate fi 1 sau -1. Astfel y(1,1) -> 1, y(1,2) -> 2 etc.

- Dupa ce am transpus toate clauzele in cod si am creat fisierul sat.cnf, am intrebat "oracolul".

- Descifrarea a fost simpla: daca variabila x din sat.sol e pozitiva, atunci y(i,r) cu codul
r e true, deci setul i e al r-lea din acoperire.

- Complexitatea temporala a reducerii (formulate_oracle_question): O(K*M + K^2*M + K*M^2 + N*M) =
= O(K^2*M + K*M^2 + N*M), unde N, M, K au seminificatia din enunt.

## Task2 - rise:
 
- Se bazeaza mult pe rezolvarea de la taskul 1, doar ca aici nu mai primesc direct K,
ci trebuie sa aflu eu K minim (K = numarul de pachetele alese pentru a obtine toate cartile dorite)

- Setul final al cartilor dorite este creat la citire, prin eliminarea celor pe care
jucatorul le detine deja.

- Pentru a determina K minim, execut o cautare binara. Cand aesta e gasit, descifrez
si printez raspunsul.

- Complexitatea temporala a reducerii (formulate_oracle_question): O(logP * (K*P + K^2 * P + K * P^2 + P * M)),
unde N, M, P au seminificatia din enunt.

## Task3 - redemption:
 
- La citire, creez setul cartilor dorite la fel ca la task-ul 2.

- Pentru aproximarea unui K optim, folosesc un algoritm greedy, care alege la fiecare pas
pachetul de carti care contine cele mai multe carti dorite, pana la obtinerea tuturor
cartilor dorite, apoi printeaza indicii pachetelor alese.

- Complexitate temporala: O(M*(P*T + T)) = O(M*P*T), unde M, P au semnificatia din enunt, iar
T = max(|P|) - dimensiunea celui mai mare pachetel.

## Resurse
- https://en.wikipedia.org/wiki/Set_cover_problem -> am inceput tema prin a citi putin aici, asa ca la taskul 3 m-am dus imediat cu
    gandul la implementarea greedy
- chat.openai.com -> algorimul generic greedy pentru min set cover C++
