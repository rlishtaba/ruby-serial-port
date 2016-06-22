lib = File.expand_path '../lib', __FILE__
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include? lib

require 'bundler/setup'
require 'bundler/gem_tasks'

require 'rake/extensiontask'
Rake::ExtensionTask.new('rs_232') do |ext|
  ext.name = 'rs_232_native'
  ext.source_pattern = '*.{c,cpp}'
end

require 'rake/clean'
CLEAN.include %w(**/*.{log} doc coverage tmp pkg **/*.{o,so,bundle} Makefile)

require 'simplecov'
task :cov do
  ENV['SIMPLECOV'] = 'features'
  Rake::Task['default'].invoke
end

require 'cucumber/rake/task'
Cucumber::Rake::Task.new(:features) do |t|
  t.fork = true
  t.profile = :default
end

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new do |t|
  t.fail_on_error = false
  t.verbose = true
  t.rspec_opts = '--format RspecJunitFormatter  --out rspec.xml --tag ~wip'
end

task default: [:clobber, :compile, :spec]
