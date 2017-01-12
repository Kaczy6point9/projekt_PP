@slowa = (<>);

#print @slowa;

@slowa = sort { lc $a cmp lc $b }  @slowa;

print @slowa;

close($file);