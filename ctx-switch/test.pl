#!/usr/bin/env perl

use v5.32;
use IPC::Run qw(run);

my $log = 'ctx-switch.log';
run ["./A"], '>>', $log, '&', ["./B"], '>>', $log;
