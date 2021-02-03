DefaultBehaviour = {
  HydraFront = {
    ip = "192.168.1.1"
  },
  main = "entry"
}

ret = print("Lua says: Hello World")
print("Return value is: ", ret)

ret = hello("string", 1, 1.0)
print("User data Return value is: ", ret)

ret2 = hello2(ret)

function entry(arg)
  print("Function test called with arg: ", arg)
end
