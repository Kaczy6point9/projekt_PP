#!/bin/perl -w
use Bio::Structure::IO; #rozne formaty strukturalne

$wejscie= Bio::Structure::IO->new(-file => "3bp5.pdb", -format => 'pdb');		#wczytanie pliku pdb do wejscia(konstruktor new tworzy nowy obiekt bio structure io)

$struc = $wejscie->next_structure;	#pobiera nastepna strukture z wejscia

for $chain ($struc->get_chains){		#odczyt ze struktury lancucha
	$chain1 = $chain->id;		# i odczyt jego id (litera)
	for $res ($struc->get_residues($chain)){	#odczyt ze struktury residue number
		$res1=$res->id;
		$atom = $struc->get_atoms($res); #oraz liczba atomow
print join "\t", $chain1, $res1, $atom, "\n";	#wyswietl odpowiednie zmienne
}}