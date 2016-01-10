require 'cucumber/rake/task'
Cucumber::Rake::Task.new(:features) do |t|
  t.fork = true
  t.profile = :default
end
