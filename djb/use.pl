#!/usr/bin/perl

# trivial maintenance utility to hard-link a djb library into your
# project

if (exists $ENV{DJBROOT}) {
  $DJBROOT = $ENV{DJBROOT};
} else {
  $DJBROOT=$ENV{HOME} . "/projects/djb/";
  if (! -d $DJBROOT) {
    print STDERR "\$DJBROOT not found and ~/projects/djb/ is not it.\n";
    exit 0;
  }
}

if ($#ARGV<0) {
  print STDERR "Usage: use.pl byte [unix dns...]\n";
  print STDERR "libdjb is expected to be in \$DJBROOT or ~/projects/djb/\n";
  exit 0;
}

@wanted=();

open MAKEFILE,">>Makefile" || die "could not append to Makefile\n";
foreach $i (@ARGV) {
  $i =~ s,/+$,,;
  $target = $DJBROOT . $i;

  if (! -d $target) {
    print STDERR "$target not found\n";
    next;
  }

  print STDERR "$target/FILES\n";
  open FILE,"$target/FILES" || die "could not open $target/FILES\n";
  while (<FILE>) {
    chomp;
    push @wanted,"$target/$_" unless (m/FILES|TARGETS|Makefile/);
  }
  close FILE;
  print MAKEFILE "\ninclude $target/Makefile.$i\n";
}
close MAKEFILE;

foreach $i (@wanted) {
  $j = $i;
  $j =~ s@.*/@@;
  print "  $i => $j\n";
  link $i,$j;
}
