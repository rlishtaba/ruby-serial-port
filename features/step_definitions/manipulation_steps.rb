Given(/I open serial port/) do
  connection.open
  expect(connection.open).to be_truthy
end
