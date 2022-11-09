# tsp-greedy

some traveling salesman has a problem....

## generate.py

Script that generates file with input data for main program.\
Usage: `py generate.py <filepath> <no_cities> <max_coord> `  
Alternate usage: `py generate.py < setttings.in`  
- `<filepath> ` - path to where to export file with input data
- `<no_cities> ` - number of cities (veritces) to generate
- `<max_coord>` - maximum value of coordinates at which cities can be

## tsp-greedy.exe

Main Program that finds and prints shortest path for TSP using selected methods\
Usage: `tsp-greedy.exe <filename>`  
Sugested usage: `tsp-greedy.exe <filename> > path.out`  
- `<filename>` - path for the file with input data (generated with `generate.py`)

## visualize.py

Program for visually showing path in the network\
PreRequirements: 
- [NetworkX](https://networkx.org/)
- [Matplotlib](matplotlib.org)  

Usage: `py visualize.py`  
**Remember to correctly setup settings.in file**

## settings.in

File with settings for Python scripts

