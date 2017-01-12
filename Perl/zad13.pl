#open(FILE, '<', '/home/inf414723/Desktop/Perl/3l5q.pdb') || die "Nie można otworzyc pliku";


while(<>){	

if(/^ATOM/ && /CA/)
	{
		print substr $_, 17, 3;
		print '-';
	}
	
}

close($file);