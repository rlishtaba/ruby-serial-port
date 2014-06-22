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


