require 'cucumber/rake/task'

# - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * -
#
Cucumber::Rake::Task.new do |t|
  t.fork = true
end
