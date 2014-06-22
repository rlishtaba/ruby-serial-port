require 'mkmf'
require 'rbconfig'

if ENV['DEBUG_C']
  $CFLAGS << ' -DDEBUG'
  $CFLAGS << ' -g -O'
  $stdout.puts "compiling in debug mode... flags: #{$CFLAGS}"
end

dir_config('rs_232')

$warnflags = '-Wall'

OS = case RbConfig::CONFIG['host_os'].downcase
       when /linux/
         'linux'
       when /darwin/
         'darwin'
       when /freebsd/
         'freebsd'
       when /openbsd/
         'openbsd'
       when /sunos|solaris/
         'solaris'
       when /mswin|mingw/
         'windows'
       else
         RbConfig::CONFIG['host_os'].downcase
     end

have_header('ruby.h')
have_header('stdio.h')

if OS == 'windows'
  $VPATH << '$(srcdir)/windows'
  $INCFLAGS += ' -I$(srcdir)/windows'
  have_header('windows.h')
  have_header('fcntl.h')
  have_header('io.h')
  have_header('ruby/io.h')
  have_header('rubyio.h')
elsif %w(linux darwin).include? OS
  $VPATH << ' $(srcdir)/posix'
  $INCFLAGS += ' -I$(srcdir)/posix'
  have_header('termios.h')
  have_header('unistd.h')
  have_header('string.h')
  have_header('fcntl.h')
  have_header('errno.h')
  have_header('sys/ioctl.h')
else
  raise "RS-233 implementation is not tested for this #{OS} platform."
end

$objs = %w(constants.o port.o initializer.o)

$CFLAGS += " -DOS_#{OS.upcase}"

$stdout.puts <<-MSG

Extending with: #{$CFLAGS}

MSG

create_makefile('rs_232')