#!/usr/bin/perl

# use GNU ld mapfile to resolve library dependencies.
# usage:
#   1. use make to compile everything.
#   2. remove the binaries (not the object files and libraries)
#   3. run this script. It will dump the expanded dependencies to stdout
#      (i.e. no libraries, only the object files)

opendir DIR,"." || die;
foreach $i (readdir DIR) {
  if ($i =~ m/mapfile\..*/) {
    unlink $i || die;
  }
}
closedir DIR;

(($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,$atime,$mtime,$ctime,$blksize,$blocks)=stat("load")) || die "can't stat load!\n";

open FILE,"load" || die;
$load = join '',<FILE>;
close FILE;

rename "load","load.old" || die "rename failed\n";

open FILE,">load" || die;
print FILE "main=\"\$1\"; shift\necho \${1+\"\$\@\"} > deps.\"\$main\"\n";
print FILE "exec gcc -Wl,-Map,mapfile.\"\$main\" -o \"\$main\" \"\$main\".o \${1+\"\$\@\"}\n";
close FILE;
chmod 0755,"load" || die;

utime $atime,$mtime,"load";

system "make";

unlink "load";
rename "load.old","load" || die;

opendir DIR,"." || die;
foreach $i (readdir DIR) {
  if ($i =~ m/mapfile\.(.*)/) {
    $deps="deps.$1";
    $doto="$1.o";
    print "$1: \\\n";
    open FILE,$i || die;
    $line="load ";
    while (<FILE>) {
      if (m/^(\w+\.a)\((\w+\.o)\) +/) {
	if (length("$line$2 ")>72) {
	  print "$line \\\n";
	  $line = "$2 ";
	} else {
	  $line .= "$2 ";
	}
      }
    }
    close FILE;
    open FILE,$deps;
    while (<FILE>) {
      chomp;
      foreach $j (split) {
	if (length("$line$j ")>72) {
	  print "$line \\\n";
	  $line = "$j ";
	} else {
	  $line .= "$j ";
	}
      }
    }
    close FILE;
    unlink "$deps";
    if (length("$line$doto ")>72) {
      print "$line \\\n$doto\n\n";
    } else {
      print "$line$doto\n\n";
    }
    unlink $i || die;
  }
}
closedir DIR;
