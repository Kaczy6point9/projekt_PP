#!/bin/perl -w
use Bio::DB::GenBank;	#baza danych genbanku
use Bio::SeqIO;	#rozne formaty plikow

$sekw = Bio::DB::GenBank->new();	#kontruktor

$seq = $sekw->get_Seq_by_acc('j01673');	#pobranie sekwencji z genbanku po jego numerze dostepu

$out1 = Bio::SeqIO->new(-file=> ">plik1.gb", -format =>'genbank');
$out2 = Bio::SeqIO->new(-file=> ">plik2.fasta", -format =>'fasta');
$out3 = Bio::SeqIO->new(-file=> ">plik3.embl", -format =>'embl');

#out'y tworza nowe pliki (1-3) w odpowiednich formatach (wyzej) i zapisuje do nich pobrana sekwecje (nizej) 

$out1->write_seq($seq);
$out2->write_seq($seq);
$out3->write_seq($seq);