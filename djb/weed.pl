#!/usr/bin/perl

# Print all targets from Makefile that are not in TARGETS
# This is a trivial maintenance utility to help you keep TARGETS up to
# date.

open FILE,"TARGETS" || die "Could not open \"TARGETS\"\n";
while (<FILE>) {
  chomp; $da{$_}=1;
}
close FILE;

open FILE,"Makefile" || die "Could not open \"Makefile\"\n";
$skip=0;
while (<FILE>) {
  if (m/^([ a-zA-Z0-9\._-]*):/) {
    my @tmp=split(/\s/,$1);
    my @wanted=();
    foreach $i (@tmp) {
      if (exists $da{$i}) {
	push @wanted,$i;
#      } else {
#	print STDERR "ignoring $i\n";
      }
    }
    if ($#wanted==-1) {
      chomp;
#      print STDERR "skipping $_\n";
      $skip=1;
    } else {
      $skip=0;
      print join(' ',@wanted);
      s/^[^:]*:/:/;
      print;
    }
  } else {
    if (m/:/) {
      chomp;
      print STDERR "mismatch: %_\n";
    }
    print unless ($skip==1);
  }
}
