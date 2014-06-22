require 'rake'
require 'bundler/setup'
require 'bundler/gem_tasks'

Bundler::GemHelper.install_tasks

$:.unshift(File.dirname(__FILE__) + '/lib')

Dir['gem_tasks/**/*.rake'].each { |rake| load rake }

require 'bundler/gem_tasks'
require 'rake/extensiontask'

require 'rake/clean'

CLEAN.include %w(**/*.{log} doc coverage tmp)


def gem_spec
  @gem_spec ||= Gem::Specification.load('rs_232.gemspec')
end


Rake::ExtensionTask.new('rs_232', gem_spec) do |ext|
  # stub
end


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


task :default => [:clean, :compile]