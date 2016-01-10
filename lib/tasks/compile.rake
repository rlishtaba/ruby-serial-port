require 'rake/extensiontask'

Rake::ExtensionTask.new('rs_232') do |ext|
  ext.tmp_dir = 'tmp'
  ext.source_pattern = '*.{c,cpp}'
end
