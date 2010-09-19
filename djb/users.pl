#!/usr/bin/perl

# List files that depend on given file.

# Parser copied from target.pl ;)

local %dep;

$wanted={};

sub parse {
  my $file;
  my $makefile=shift (@_);
  my $target;
  my $deps;
  $wanted{$makefile}=1;
  open $file,$makefile || die "Couldn't open $makefile!\n";
  while (<$file>) {
    chomp;
    if (m/^include\s+([\w.]+)/) {
#      print "including $1\n";
      &parse($1);
    }
    if (m/^([\w.\/-]+):/) {
      $target = $1;
      $first = $target unless (defined $first);
#      print "Found: $1\n";
      s/[^:]*:\s*//;
      $deps=$_;
      while ($deps =~ m/\\$/) {
	$deps =~ s/\s*\\$/ /;
	$deps .= <$file>;
	chomp $deps;
      }
      $dep{$target} = $deps;
#      print " $target -> $deps\n";
    }
  }
  close $file;
}

&parse("Makefile");

foreach $i (@ARGV) {
  $wanted{$i}=1;
}

foreach $i (keys %dep) {
  foreach $j (split /\s+/,$dep{$i}) {
    if (exists $wanted{$j}) {
      $because{$i} .= "$j ";
    }
  }
}

foreach $i (keys %because) {
  print "$i: ",$because{$i},"\n";
}
