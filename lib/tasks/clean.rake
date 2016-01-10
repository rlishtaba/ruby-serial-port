require 'rake/clean'

CLEAN.include %w(**/*.{log} doc coverage tmp pkg **/*.{o,so,bundle} Makefile)
