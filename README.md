# hm, hn, hmn

Generators of canvas for Petri net models of hypertorus (hypercube) grid with 
Moore's, von-Neumann's, and combined neighborhoods, respectively


Description:
------------

There is a d-dimensional grid of size n indexed with d-tuples having components' range from 0 to n-1.
A grid cell model is represented with a single Petri net place denoted as "p".
Neighboring cells are connected via pairs of dedicated transitions; 
transitions are denoted as input "ti" and output "to" with respect to a cell with lesser index.
A hypertorus is obtained from a hypercube via closing (connecting) opposite facets in each dimension. 
Indices are printed with '.' separator on dimensions; character 'v' separates two indices in a couple. 
More complicated cell models can be inserted but the canvas of connections does not change.

hm - Moore's neighborhood

In Moore's neighborhood, neighboring cells are situated at Chebyshev distance equal to 1.
Neighbors are connected via facets which are hypercubes having dimensions from d-1 to 0. 
For a hypertorus cell, there are 3^d-1 neighbors. For a hypercube cell
situated on k-cube bound which is not (k-1)-cube bound, there are 3^k*2^(d-k)-1 neighbors.

hn - von-Neumann's neighborhood

In von-Neumann's neighborhood, neighboring cells are situated at Manhattan distance equal to 1.
Neighbors are connected via facets which are (d-1)-dimension hypercubes.
For a hypertorus cell, there are 2*d neighbors. For a hypercube cell
situated on k-cube bound which is not (k-1)-cube bound, there are d+k neighbors.

hmn - combined neighborhood

In a combined neighborhood (Moore's with von-Neumann's), neighbors are situated at 
Chebyshev distance equal to 1 restricted by a given interval of Manhattan distance r, 
1<=r1<=r<=r2<=d.
Neighbors are connected via facets which are hypercubes having dimensions from d-r1 to d-r2.
Thus, r1=1, r2=1 gives von-Neumann's neighborhood and r1=1, r2=d gives Moore's neighborhood.


Command line formats:
--------------------

>hm d n [m] [e] > hm_model.net

>hn d n [m] [e] > hn_model.net

>hmn d n [m] [e] [r1] [r2] > hmn_model.net


Parameters:
-----------

d   number of dimensions (d>=1);

n   size of hypertorus or hypercube (n>=1; for hypertorus n>=3), 
    actually the size is (n x n x n x ... x n) d times;

m   number of tokens in each node (m>=0, default 1);

e   edge: 't' - hypertorus, 'c' - hypercube (default 't').

For hmn only:

r1  lower bound of Manhattan distance (default r1=1);

r2  upper bound of Manhattan distance (default r2=d), 1<=r1<=r2<=d,   


Output (file) format:
---------------------

.net  “Time Petri nets textual format” according to http://www.laas.fr/tina


Tools to display, edit, visualize, and analyze generated models:
----------------------------------------------------------------

Tina Toolbox for analysis of Petri nets and Time Petri nets http://www.laas.fr/tina

Exported from Tina, models are opened with other tools for Petri nets listed at 
http://www.informatik.uni-hamburg.de/TGI/PetriNets/tools/quick.html


An example:
-----------

>hm 2 3 > hm_d2n3.net

- Generate a model of a hypertorus for Moore's neighborhood 
  with 2 dimensions of size 3 having 1 token in each cell.

>nd hm_d2n3.net

- Load the model into graphical environment of Tina. 

Menue: "Edit - draw - nearto"

- Visualize the model. 

Menue: "Tools - stepper simulator - Rand"

- Watch the token game.


References:
-----------

Zaitsev D.A. Generators of Petri Net Models. Computer Communication & Collaboration, Vol. 2, Issue 2, 2014, 12-25. 
http://www.bapress.ca/ccc/ccc2014_2/2_14011024.pdf


Notes:
------

Chebyshev distance - maximum of modules of differences on coordinates.

Manhattan distance (special case of Minkowski distance) - sum of modules of differences on coordinates. 


---------------------------
http://member.acm.org/~daze
---------------------------

