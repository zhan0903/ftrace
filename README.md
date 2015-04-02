this is ftrace tool

usage:
1 run init1 to configure environment;
2 run ftrace2 to trace the command;
3 run generate_full_graph to generate a full.graph;
4 run dot to generate a full trace map;
5 run gengraph to filter the full map to get what you want. 


basic usage for dot:
dot -Tpng full.graph -o <photoname>
http://www.graphviz.org/Documentation.php

basic usage for gengraph:
gengraph --output-type "png" -f <functioname>
http://www.csn.ul.ie/~mel/projects/codeviz/
