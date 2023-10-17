#!/usr/bin/env perl

use v5.32;
use IPC::Run qw(run);

run ["./A"], '&', ["./B"];
