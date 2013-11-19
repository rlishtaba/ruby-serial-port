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

When /^connection instance "(should|should not)" be available$/ do |matcher|

  action = matcher == 'should' ? :should : :should_not

  if respond_to? :should
    adapter.open?.send(action, be_true)
  else
    assert_equal(adapter.open?, action == :should)
  end

end

Given /^I "(open|close)" connection$/ do |action|

  adapter.send(action)

  if action == 'close'
    if respond_to? :should
      adapter.open?.should be_false
    else
      assert_equal(connection.open?, false)
    end
  else
    if respond_to? :should
      adapter.open?.should be_true
    else
      assert_equal(connection.open?, true)
    end
  end

end


