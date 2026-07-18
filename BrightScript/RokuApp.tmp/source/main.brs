sub RunScreenSaver()
  RunScreenSaver_FractalTree()
end sub

sub RunScreenSaver_FractalTree()
  screen = CreateObject("roScreen", true)
  port = CreateObject("roMessagePort")
  screen.SetMessagePort(port)
  canvasWidth = screen.GetWidth()
  canvasHeight = screen.GetHeight()
  canvas = CreateObject("roBitmap", {width: canvasWidth, height: canvasHeight, ColorMode: "RGBA"})
  canvas.Clear(&h000000FF)

  startConfigs = [{
    x: screen.GetWidth()/2.,
    y: screen.GetHeight(),
    length: screen.GetHeight()/2.3,
    angle: 270
  }, {
    x: screen.GetWidth()/2.,
    y: 0,
    length: screen.GetHeight()/2.3,
    angle: 90
  }, {
    x: 0,
    y: screen.GetHeight()/2.,
    length: screen.GetWidth()/5.,
    angle: 0
  }, {
    x: screen.GetWidth(),
    y: screen.GetHeight()/2.,
    length: screen.GetWidth()/5.,
    angle: 180
  }]

  branches = []
  config = startConfigs[Rnd(startConfigs.Count())]
  branches.Push(CreateBranch(config.x, config.y, config.length, config.angle, 0))
  maxDepth = 10
  deltaAngle = 60
  lengthRatio = 0.6
  colors = [&hFF0000FF, &hFF7700FF, &hFFFF00FF, &h00FF00FF, &h00FFFFFF, &h0000FFFF, &h7700FFFF, &hFF00FFFF]
  numColors = colors.Count()

  coolDownTimer = -1
  coolDownMax = 400

  while true
    msg = port.GetMessage()
    if type(msg) = "roUniversalControlEvent" then exit while

    if branches.Count() > 0 then
      branch = branches.Shift()
      radians = DegToRad(branch.angle)
      endX = branch.x + branch.length*cos(radians)
      endY = branch.y + branch.length*sin(radians)
      newLength = branch.length * lengthRatio
      if branch.depth < maxDepth then
        branches.Push(CreateBranch(endX, endY, newLength, branch.angle - deltaAngle, branch.depth + 1))
        branches.Push(CreateBranch(endX, endY, newLength, branch.angle + deltaAngle, branch.depth + 1))
      end if
      color = colors[branch.depth mod numColors]
      canvas.DrawLine(branch.x, branch.y, endX, endY, color)
    else if coolDownTimer < 0 then
      coolDownTimer = coolDownMax
    else if coolDownTimer >= 0 then
      if coolDownTimer = 0 then
        canvas.Clear(&h000000FF)
        config = startConfigs[Rnd(startConfigs.Count())]
        branches.Push(CreateBranch(config.x, config.y, config.length, config.angle, 0))
      end if
      coolDownTimer = coolDownTimer - 1
    end if

    screen.Clear(&h000000FF)
    screen.DrawObject(0, 0, canvas)
    screen.SwapBuffers()
    Sleep(16)
  end while
end sub

function DegToRad(degrees as Float) as Float
  return degrees * 3.14159265356 / 180.
end function

function CreateBranch(x as Float, y as Float, length as Float, angle as Float, depth as Integer) as Object
  return {
    x: x,
    y: y,
    length: length,
    angle: angle,
    depth: depth
  }
end function
