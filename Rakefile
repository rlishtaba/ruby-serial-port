$:.unshift(File.expand_path '../', __FILE__)
require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rake'
require 'rake/clean'
require 'fileutils'
require 'rake/extensiontask'

Dir['gem_tasks/**/*.rake'].each { |rake| load rake }

CLEAN.include %w(**/*.{log} doc coverage tmp)

Rake::ExtensionTask.new('rs_232', Gem::Specification.load('rs_232.gemspec'))

task :default => [:clean, :compile, :spec]