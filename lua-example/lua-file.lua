-- Create a table 't' and add a value
t = { x=1 }
a = 0

function f (string, value, integer)
  print(
    string.format("Lua: f called with args: %s %d %d", string, value, integer)
  )

  return integer
end
