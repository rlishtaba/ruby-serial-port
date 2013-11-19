#
# Copyright (c) 2013, Ingenico Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
# provided that the above copyright notice and this permission notice appear in all copies.
#                                                                                                                                                                                                          *
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#

require 'mkmf'
require 'rbconfig'

if ENV['DEBUG_C']
  $CFLAGS << " -DDEBUG"
  $CFLAGS << " -g -O"
  $stdout.puts "compiling in debug mode... flags: #{$CFLAGS}"
end

def root(path)
  File.expand_path("../#{path}/", __FILE__)
end

dir_config("rs_232")

$warnflags = '-Wall'

CPU = case RbConfig::CONFIG['host_cpu'].downcase
        when /i[3456]86/
          if RbConfig::CONFIG['host_os'] =~ /darwin/ && 0xfee1deadbeef.is_a?(Fixnum)
            "x86_64"
          else
            "i386"
          end

        when /amd64|x86_64/
          "x86_64"

        when /ppc64|powerpc64/
          "powerpc64"

        when /ppc|powerpc/
          "powerpc"

        when /^arm/
          "arm"

        else
          RbConfig::CONFIG['host_cpu']
      end

$stdout.puts "Detecting CPU... "
$stdout.puts "CPU: #{CPU}"

OS = case RbConfig::CONFIG['host_os'].downcase
       when /linux/
         "linux"
       when /darwin/
         "darwin"
       when /freebsd/
         "freebsd"
       when /openbsd/
         "openbsd"
       when /sunos|solaris/
         "solaris"
       when /mswin|mingw/
         "windows"
       else
         RbConfig::CONFIG['host_os'].downcase
     end

$stdout.puts "Detecting OS... "
$stdout.puts "OS: #{OS}"
$stdout.puts


have_header("ruby.h")
have_header("port.h")
have_header("stdio.h")

if OS == "windows"
  $VPATH << "$(srcdir)/windows"
  $INCFLAGS += " -I$(srcdir)/windows"
  have_header("windows.h")
  have_header("fcntl.h")
  have_header("io.h")
  have_header("ruby/io.h")
  have_header("rubyio.h")
elsif %w(linux darwin).include? OS
  $VPATH << " $(srcdir)/posix"
  $INCFLAGS += " -I$(srcdir)/posix"
  have_header("termios.h")
  have_header("unistd.h")
  have_header("string.h")
  have_header("fcntl.h")
  have_header("errno.h")
  have_header("sys/ioctl.h")
else
  raise "RS-233 implementation is not tested for this #{OS} palform."
end

$objs = %w(constants.o port.o initializer.o)

$CFLAGS += " -DOS_#{OS.upcase}"

$stdout.puts <<-MSG

Extending with: #{$CFLAGS}

MSG

create_makefile('rs_232')
