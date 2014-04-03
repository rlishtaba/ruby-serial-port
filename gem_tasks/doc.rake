require 'rdoc/task'

desc "builds documentation for the 'rs_232' gem"
Rake::RDocTask.new :doc do |rd|

  base = File.expand_path("../", File.dirname(__FILE__))
  base.sub!(/^#{Regexp::escape FileUtils.pwd}\/?/, './')

  rd.main = File.join(base, "README.md")
  rd.rdoc_files.include(File.join(base, "README.md"), File.join(base, "lib/**/*.rb"))
  rd.rdoc_dir = "./doc/rs_232"
end
