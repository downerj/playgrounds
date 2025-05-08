#!/usr/bin/env perl

# https://metacpan.org/pod/Term::ReadLine

$ENV{PERL_READLINE_NOWARN} = 1;

use Term::ReadLine;
my $term = Term::ReadLine->new('Simple Perl REPL');
my $prompt = "%> ";
my $OUT = $term->OUT || \*STDOUT;
while (defined ($_ = $term->readline($prompt))) {
  my $res = eval($_);
  warn $@ if $@;
  print $OUT $res, "\n" unless $@;
  $term->addhistory($_) if /\S/;
}
print("Bye.\n");
