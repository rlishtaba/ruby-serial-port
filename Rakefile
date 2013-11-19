require "rake"
require "bundler/gem_tasks"
require 'rake/extensiontask'

def gem_spec
  @gem_spec ||= Gem::Specification.load('rs_232.gemspec')
end

Rake::ExtensionTask.new('rs_232', gem_spec) do |ext|
  # stub
end

desc 'clean out build files'
task :clean do
  rm_rf File.expand_path('../tmp', __FILE__)
end

task :default => [:clean, :compile]

desc 'code statistics'
task :stats do

  def count(glob)
    Dir[glob].inject(0) do |count, fi|
      next unless File.file?(fi)
      count + File.read(fi).lines.to_a.length
    end
  end

  rb_lines = count 'lib/**/*.rb'
  c_lines  = count 'ext/**/*.{c,cpp,h,hpp}'

  puts "Lines of Ruby: #{rb_lines}"
  puts "Lines of C*:   #{c_lines}"
end

desc "reload"
task :reload do
    sh "rake clean"
    sh "rake compile"
    sh "rake clean"
    system "ruby bin/env.rb"
end

desc "rebuild"
task :rebuild do
  sh "rake clean"
  sh "rake compile"
  sh "rake clean"
end

desc "Cucumber tests execution"
task :cucumber do
  sh "bundle exec cucumber"
end  
