#!/usr/bin/perl

# list files in current directory that are not in FILES

open FILE,"FILES" || die;
while (<FILE>) {
  chomp;
  $FILES{$_}=1;
}
close FILE;

opendir DIR,"." || die;
foreach $i (readdir DIR) {
  if (-f $i) {
    print "$i\n" unless (exists $FILES{$i});
  }
}
closedir DIR;
