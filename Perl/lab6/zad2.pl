@slowa = (<>);

@slowa = map {$_->[1]} sort {$a->[0] cmp $b->[0]} map{[lc($_), $_]} @slowa;

print @slowa;

close($file);