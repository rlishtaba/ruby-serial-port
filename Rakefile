lib = File.expand_path '../lib', __FILE__
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include? lib
require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rake'

load 'tasks/clean.rake'
load 'tasks/cov.rake'
load 'tasks/rspec.rake'
load 'tasks/cucumber.rake'
load 'tasks/compile.rake'

task default: [:rspec]
