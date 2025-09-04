Kontomitros Christos, 1798, ckontomitros@inf.uth.gr
Athanasiadis Ioannis, 1844, iathanasiadis@inf.uth.gr
Axelos Christos,  1814, caxelos@inf.uth.gr 

Για την μεταγλώττιση του module κάνουμε απλά make στο project1_module

Για την μεταγλώττιση της βιβλιοθήκης κάναμε:

gcc -c free_total.c -o free_total.o
ar  rcs libfree_total.a   free_total.o
gcc -static check_mem.c -L.   -lfree_total  -o ektelesimo
