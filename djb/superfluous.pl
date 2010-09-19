#!/usr/bin/perl

# This trivial maintenance utility parses the Makefile (including
# included Makefiles) and lists the files that are not referenced from
# any Makefile (i.e. man pages or somesuch).

# This parser is very crude and only works for libdjb style Makefiles.
# For example, "target1 target2: include1.h" is not supported yet.

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
$wanted{TARGETS}=1;
$wanted{FILES}=1;

sub dodep {
  my $target=shift (@_);
#  print "dodep $target -> $dep{$target}\n";
  if (defined $wanted{$target}) {
#    print "early exit $i\n";
    return;
  }
  if (defined $dep{$target}) {
    foreach $i (split /\s+/,$dep{$target}) {
      &dodep($i);
      $wanted{$i}=1;
    }
  }
}

&dodep($first);

opendir DIR,"." || die "could not opendir '.'!\n";
foreach $i (readdir DIR) {
  -f $i or next;
  if (not exists $wanted{$i}) {
    print "superfluous: $i\n";
  }
}
closedir DIR;
exit 0;
foreach $i (keys %wanted) {
  print "$i\n";
#  print "$i: ",join(' ',$dep{$i}),"\n";
}
