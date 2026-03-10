# PmergeMe — C++ Module 09 (STL) — Ford–Johnson (Merge-Insert)

Projet 42 **C++ Module 09 — Exercice 02**.

Objectif : trier une séquence d’entiers positifs en arguments en utilisant **Ford–Johnson / Merge-Insertion sort** (TAOCP Vol.3, “Merge Insertion”), puis comparer le temps d’exécution sur **deux conteneurs STL**.

---

## Résumé du projet

Le programme :
- lit une séquence d’entiers **strictement positifs** depuis la ligne de commande
- affiche :
  - `Before:` la séquence initiale
  - `After:` la séquence triée
  - le temps de traitement sur `std::vector`
  - le temps de traitement sur `std::deque`
- implémente l’algorithme Ford–Johnson :
  - **pairing** (comparaison par paires)
  - **descente récursive** sur la chaîne des winners
  - **unwinding** : insertion des losers dans un ordre basé sur **Jacobsthal**
  - insertion bornée (binary search sur préfixe) avant le winner associé

---

## Détails d’implémentation

### 1) Pairing (création des paires)
On regroupe la séquence en paires `(a,b)` et on déduit :
- `winner = max(a,b)`
- `looser = min(a,b)`
Chaque paire reçoit un `id` stable (utile pour suivre les associations pendant l’unwinding).

### 2) Main chain (winners) + récursion
On trie récursivement la chaîne des winners (toujours en Ford–Johnson).

### 3) Insertion des losers (ordre Jacobsthal)
Les losers restants (et un éventuel orphelin) sont insérés dans un ordre **Jacobsthal**.
Pour chaque loser associé à un winner `x`, on effectue une recherche binaire **bornée** dans :
- `S[0 .. pos(x))`  
car on sait que `loser < x` donc il doit être placé avant `x`.

### Tables internes utiles
- `pendById[id]` : mapping `winnerId -> loserNode` (association winner/loser)
- `posById[id]` / `posHighById[id]` : mapping `id -> position actuelle dans la main chain`  
utile pour retrouver la borne du winner en O(1) sans rescanner `S`.

---

## Compilation

```bash
make
