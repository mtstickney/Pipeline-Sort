#!/usr/bin/perl

# Feed "gcc -MM *.c" output

open PIPE,"gcc -MM *.c|" || die;
while (<PIPE>) {
  chomp;
  while (m/\\$/) {	# continuation line
    $_ .= <PIPE> || die "invalid continuation line";
    chomp;
  }
  s/\\ //g;
  if (!m/\.o: /) {
    die "no .o dependancy?!\n";
  }
  ($object,$deps) = (m/([^:]*): (.*)/);
  if (not $object =~ m/^try/) {
    print "$object: \\\n";
    print "compile $deps\n";
    $source=$object;
    $source =~ s/\.o/.c/;
    print "	./compile $source\n\n";
  }
}
