#!/bin/perl -w
use Bio::DB::GenBank; #baza danych genbanku
use Bio::SeqIO;		#rozne formaty plikow

$sekw = Bio::DB::GenBank->new();	#tworzenie nowego obiektu

$seq = $sekw->get_Seq_by_acc('j01673');	#pobranie sekwencji z genbanku

$bialko = $seq->translate;	#zmienna w ktorej przechowywana jest pobrana sekwencja z jednoczesnym zamienieniem sekw. nukleotydowej na bialkowa (translate)

$out1 = Bio::SeqIO->new(-file=> ">plik11.gb", -format =>'genbank');
$out2 = Bio::SeqIO->new(-file=> ">plik22.fasta", -format =>'fasta');
$out3 = Bio::SeqIO->new(-file=> ">plik33.embl", -format =>'embl');

#utworzenie plikow z odpowiednimi rozszerzeniami

$out1->write_seq($bialko);
$out2->write_seq($bialko);
$out3->write_seq($bialko);

#i wpisanie do nich sekwencji bialkowej