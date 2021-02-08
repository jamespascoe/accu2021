-- Create a global table 't'
t = { x=1, y=2 }

function f (str, val, int)
  print(
    string.format(
      "Lua: f called with args: %s %d %d", str, val, int
    )
  )

  -- Call a C++ function
  local rc = cppFunc(str, t.y, int)

  return rc
end
