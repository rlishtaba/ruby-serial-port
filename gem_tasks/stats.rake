# - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * -
#
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