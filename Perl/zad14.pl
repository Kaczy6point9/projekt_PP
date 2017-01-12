#open(FILE, '<', '/home/inf414723/Desktop/Perl/3l5q.pdb') || die "Nie można otworzyc pliku";

%sekwencja = ('ALA' => 'A',
'ARG' => 'R',
'ASN' => 'N',
'ASP' => 'D',
'CYS' => 'C',
'GLN' => 'Q',
'GLU' => 'E',
'GLY' => 'G',
'HIS' => 'H',
'HSD' => 'H',
'ILE' => 'I',
'LEU' => 'L',
'LYS' => 'K',
'MET' => 'M',
'PHE' => 'F',
'PRO' => 'P',
'SER' => 'S',
'THR' => 'T',
'TRP' => 'W',
'TYR' => 'Y',
'VAL' => 'V');

while(<>){	

if(/^ATOM/ && /CA/)
	{
		print $sekwencja{substr($_, 17, 3)};
		print '-';
	}
	
}

close($file);