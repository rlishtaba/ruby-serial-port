lib = File.expand_path '../lib', __FILE__
$:.unshift(lib) unless $:.include? lib
require 'bundler/setup'
require 'bundler/gem_tasks'
require 'rake'
require 'rake/clean'
require 'rake/extensiontask'

Dir['gem_tasks/**/*.rake'].each { |rake| load rake }

CLEAN.include %w(**/*.{log} doc coverage tmp pkg **/*.{o,so,bundle} Makefile)

Rake::ExtensionTask.new('rs_232') do |ext|
  ext.tmp_dir        = 'tmp'
  ext.source_pattern = "*.{c,cpp}"
end

task :default => [:clean, :compile]