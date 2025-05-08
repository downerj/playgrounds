my = {}

function my.displayTable(t)
  for k,v in pairs(t) do
    print(k, v)
    if k ~= '_G' and type(v) == 'table' then
      for k1,v1 in pairs(v) do
        if type(k1) == 'number' then
          print(k .. '[' .. k1 .. ']', v1)
        else
          print(k .. '["' .. k1 .. '"]', v1)
        end
      end
    end
  end
end

function my.clear()
  print("\x1bc\x1b[3J")
end

function my.list(t)
  return '{' .. table.concat(t, ', ') .. '}'
end

function my.range(m, n)
  local min
  local max
  if n == nil then
    min = 0
    max = m
  else
    min = m
    max = n
  end
  local t = {}
  local i = 1
  for k = min,(max - 1) do
    t[i] = k
    i = i + 1
  end
  return t
end

function my.map(t, cb)
  local result = {}
  for k,v in ipairs(t) do
    result[k] = cb(v, k, t)
  end
  return result
end

function my.foldl(t, cb, initVal)
  local result = initVal
  for _k,v in ipairs(t) do
    result = cb(result, v)
  end
  return result
end

function my.sum(t)
  local result = 0
  for _k,v in ipairs(t) do
    result = result + v
  end
  return result
end

function my.product(t)
  local result = 1
  for _k,v in ipairs(t) do
    result = result * v1
  end
  return result
end

function my.condition(expression, tValue, fValue)
  if expression then
    return tValue
  else
    return fValue
  end
end

my.Optional = {}

function my.Optional:new(value)
  local t = setmetatable({}, { __index = my.Optional })
  t.value = value
  return t
end

function my.Optional:set(value)
  self.value = value
end

function my.Optional:get()
  return self.value
end

function my.Optional:getOr(value)
  if self.value ~= nil then
    return self.value
  else
    return value
  end
end

function my.Optional:hasValue()
  return self.value ~= nil
end

function my.Optional:reset()
  self.value = nil
end
