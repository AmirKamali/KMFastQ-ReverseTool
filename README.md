KMFastQ-ReverseTool
===============
This command line tool helps generating reverse comlepment of reads.

it supports both FASTA and FASTQ file formats.

HOW TO USE ?

./KMFastQ-ReverseTool -fastq input.fq -o output.fq -rename 1

-fastq: fastq format input file address. (required)
	reference file should be in a FASTA format.
or

-fasta: fasta format input file address.(required)

-rename: output file format[default =1] (optional)
	arguments : [0,1]
	
	
	
Sample Input :
@R-Read_1.0.100
GtTGGattatataataaaatGTAGACCAGTCCTATAAACTATTCAAGCAAATAGCCAAATTTTAAAAGCTATTGAAAATATAAATTTATGCTAGTAGTTT
+
ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
@R-Read_2.9.200
ttaaatattGtTGGattatataataaaatGTAGACCAGTCCTATAAACTATTCAAGCAAATAGCCAAATTTTAAAAGCTATTGAAAATATAAATTTATGC
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhc
@R-Read_3.18.300
TAAATGttattaaatattGtTGGattatataataaaatGTAGACCAGTCCTATAAACTATTCAAGCAAATAGCCAAATTTTAAAAGCTATTGAAAATATA
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
@R-Read_4.27.400
ACTTATTGATAAATGttattaaatattGtTGGattatataataaaatGTAGACCAGTCCTATAAACTATTCAAGCAAATAGCCAAATTTTAAAAGCTATT
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
@R-Read_5.36.500
TATCATGTGACTTATTGATAAATGttattaaatattGtTGGattatataataaaatGTAGACCAGTCCTATAAACTATTCAAGCAAATAGCCAAATTTTA
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
@R-Read_6.45.600
TTATTAGAATATCATGTGACTTATTGATAAATGttattaaatattGtTGGattatataataaaatGTAGACCAGTCCTATAAACTATTCAAGCAAATAGC
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh	
	
Sample Output :

@Read_1.0.100
AAACTACTAGCATAAATTTATATTTTCAATAGCTTTTAAAATTTGGCTATTTGCTTGAATAGTTTATAGGACTGGTCTACattttattatataatCCAaC
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhha
@Read_2.9.200
GCATAAATTTATATTTTCAATAGCTTTTAAAATTTGGCTATTTGCTTGAATAGTTTATAGGACTGGTCTACattttattatataatCCAaCaatatttaa
+
chhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
@Read_3.18.300
TATATTTTCAATAGCTTTTAAAATTTGGCTATTTGCTTGAATAGTTTATAGGACTGGTCTACattttattatataatCCAaCaatatttaataaCATTTA
+
hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
@Read_4.27.400
AATAGCTTTTAAAATTTGGCTATTTGCTTGAATAGTTTATAGGACTGGTCTACattttattatataatCCAaCaatatttaataaCATTTATCAATAAGT


Example:
./KMReadGenerator -r "/hg19/chr21.ucsc.hg19.fa" -o "output.fa" -l 30 -vp 100  -n 10 -vpt s1-b5-d1-b1-s2
 
