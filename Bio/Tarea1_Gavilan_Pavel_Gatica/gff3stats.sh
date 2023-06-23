#!/bin/bash
chmod +x mi_script.sh


cut -d '.' -f 1 eden.gff3

awk 'NR==2 {print $2}' eden.gff3

head -n 2 eden.gff3|tail -n 1|cut -d ' ' -f 2
grep "gene " archivo.txt |awk -F ';' '{print $2}' | awk -F '=' '{print $2}'

grep "gene " eden.gff3 | awk -F ';' '{print $2}'|cut -d '=' -f 2

grep "gene " eden.gff3 |cut -d '=' -f 3

grep -c "exon" eden.gff3

export PS1="\u@\h:"

#bastian Gavilan
#luciano Pavel
#Manu