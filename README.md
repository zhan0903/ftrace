this is ftrace tool

usage:
1 run init1 to configure environment;/*init1*/
2 run ftrace2 to trace the command;/*ftrace2 <command>*/
3 run generate_full_graph3 to generate a full.graph;/*generate_full_graph3*/
4 run dot to generate a full trace map;
5 run gengraph_shell(or use gengraph directly) to filter the full map to get what you want. 


basic usage for dot:
dot -Tpng full.graph -o <photoname>
http://www.graphviz.org/Documentation.php

before use gengraph,you should download and install codeviz first
basic usage for gengraph:
gengraph --output-type "png" -f <functioname> -s "<functionname>;<...>" -i "<functionname>;<....>" -t -d <level>
http://www.csn.ul.ie/~mel/projects/codeviz/
