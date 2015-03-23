import re

f_r = open("trace",'r')
#f_r = open("filter_text",'r')
#f_w = open("trace_filted_text",'w')
f_w = open("trace_filted",'w')
lines = f_r.readlines()
f_r.close()

l_list = lines[6:]
for line in l_list:
   p = re.compile('\.isra\.[0-9]*')
   line = p.sub('',line)
   p = re.compile('\.part\.[0-9]*')
   line = p.sub('',line)
   p = re.compile('\.constprop\.[0-9]*')
   line = p.sub('',line)
   nPos = line.index(": ")
   f_w.write(line[(nPos+1):])
